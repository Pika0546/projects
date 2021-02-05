import React, {Component} from 'react';
import Cell from './cell';



class Board extends Component {

    constructor(props){
        super(props);
        
        this.state={
            board: [],
            boardSize: 0,
            matrix: [],
            flagStatus: [],
        }
    }

    clearRestart=()=>{
        this.props.clearRestart();
    }

    static getDerivedStateFromProps(props, state) {
       
        if(props.matrix != state.matrix){
            let temp1 = [];
            let temp2 = [];
            let n = props.boardSize;
        
            for(let i = 0 ; i < n ; i++){
                let m1 = [];
                let m2 = []
                for(let j = 0 ; j < n ; j++){
                    m1.push(0);
                    m2.push(0)
                }
                temp1.push(m1);
                temp2.push(m2);
            }
            
            return {
                    matrix: props.matrix,
                    board: temp1,
                    boardSize: n,
                    flagStatus: temp2,
                    };
        }else{
            return null
        }
        
    }

    checkWin=()=>{
        let board = this.state.board;
        let matrix = this.state.matrix;
        let n = this.state.boardSize;
        let result = true;
        for(let i = 0 ; i < n; i ++){
            for(let j = 0 ; j < n ; j ++){
                if(matrix[i][j] !== -1 && board[i][j] === 0){
                    result = false;
                }
            }
        }
        if(result){
           this.props.handleWin();
        }
    }

    dig =(row,col, board, matrix, boardSize, flagMatrix)=>{
        board[row][col] = 1;
        if(flagMatrix[row][col]){
            flagMatrix[row][col] = 0;
            this.props.handleFlag(row,col, 1);
        }
        if(matrix[row][col]===0){
           
            let blocks = [
                [row + 1, col],
                [row + 1, col - 1],
                [row + 1, col + 1],
                [row, col + 1],
                [row, col - 1],
                [row - 1, col],
                [row - 1, col + 1],
                [row - 1, col - 1]
            ]
            blocks.forEach((item)=>{
                
                if(item[0] >= 0 && item[0] < boardSize && item[1] >= 0 && item[1] < boardSize  && board[item[0]][item[1]] === 0){
                  
                    this.dig(item[0], item[1], board, matrix, boardSize, flagMatrix);
                }
            })
        }
        
    }

    handleBoom=()=>{
        let temp = this.state.board;
        for(let i = 0 ; i < this.state.boardSize ; i++){
            for(let j = 0; j < this.state.boardSize; j++){
                temp[i][j] = 1;
            }
        }
        this.setState({
            board: temp,
        })
        this.props.handleLose();
        return 1;
    }

    onDig=(row,col)=>{
      
        let matrix = this.props.matrix;
        let boardSize = this.props.boardSize;
        let board = this.state.board;
        let flagMatrix = this.state.flagStatus;
        board[row][col] = 1;
        let isLose = 0;
        if(matrix[row][col] === -1){
            isLose = this.handleBoom();
        }
        else{
            this.dig(row, col, board, matrix, boardSize, flagMatrix);
            this.setState({
                board: board,
            })
            
        }
        
        if(!isLose){
            this.checkWin();
        }
    }

    handleFlag=(row, col, n)=>{
        let temp = this.state.flagStatus;
       
        temp[row][col] = (n === -1) ? 1 : 0;
        this.setState({
            flagStatus: temp,
        })
        this.props.handleFlag(row,col,n);
    }

    renderMatrix=(matrix)=>{
        let total = 0;
        let statusBoard = this.state.board;
        let n = this.state.boardSize;
        let isFlagable = 1;
        if(this.props.nFlag === 0){
            isFlagable = 0;
        }
        let board = matrix.map((row,nrow)=>{
            let count = nrow%2;
            
            
            return row.map((item,col)=>{
                count++;
                total++;
                let left= 0;
                let right= 0;
                let bottom= 0;
                let top= 0;
                if(statusBoard[nrow][col] === 0){
                    if(nrow > 0){
                        if(statusBoard[nrow-1][col] === 1){
                            top = 1;
                        }
                    }
                    if(nrow < n - 1){
                        if(statusBoard[nrow+1][col] === 1){
                            bottom = 1;
                        }
                    }
                    if(col > 0){
                        if(statusBoard[nrow][col - 1] === 1){
                            left = 1;
                        }
                    }
                    if(col < n - 1){
                        if(statusBoard[nrow][col + 1] === 1){
                            right = 1;
                        }
                    }
                }

                return <Cell 
                            cTyle={count%2} 
                            key={total} 
                            size={this.props.gameMode} 
                            cellValue={item}
                            onDig={this.onDig}
                            row={nrow}
                            col={col}
                            id={total}
                            status={this.state.board[nrow][col]}
                            leftOpened={left}
                            rightOpened={right}
                            topOpened={top}
                            bottomOpened={bottom}
                            handleFlag={this.handleFlag}
                            isFlagable={isFlagable}
                            isFlagOn={this.state.flagStatus[nrow][col]}
                        ></Cell>
                    
            })
            
        })
        return board;
    }


	render(){
        let matrix = this.props.matrix;
        let gameMode = this.props.gameMode;
        let board = this.renderMatrix(matrix);

		return (
            <div className={"game-board board"+ gameMode}>
                {board}
            </div>
		
		)
	}
  	
}

export default Board;
