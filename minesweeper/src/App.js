import React, {Component} from 'react';
import Toolbar from './component/toolbar';
import Board from './component/board';
import Start from './component/start';
import MessageBox from './component/messageBox';

import './App.css';

function getRndInteger(min, max) {
	return Math.floor(Math.random() * (max - min + 1) ) + min;
}

document.addEventListener("contextmenu",(event)=>{
	event.preventDefault();
})

class App extends Component {

	constructor(props){
		super(props);
		this.state={
			gameMode: 0,
			nRow: [10, 15, 20],
			nBomb: [10, 30, 40],
			matrix: [],
			isRestart: 0,
			flags:[10, 30, 40],
			nFlag: 0,
			startGame: 0,
			time: 0,
			idTimer: null,
			isWin: 0,
			isLose: 0,
		}
	}

	init=(mode=0)=>{
		this.setState({
			time: 0,
			isLose: 0,
			isWin: 0,
		})
		this.createMatrix(mode)
		this.timeHandle()
	}

	closeStart=()=>{
		this.init();
		
		this.setState({
			startGame: 1,
		})
		
	}

	timeHandle=()=>{
       
			
			if(this.state.idTimer){
				
				clearInterval(this.state.idTimer)
			}
			
			let idInter = setInterval(()=>{
				let temp = this.state.time + 1;
				
				this.setState({
					time: temp,
				})
			}, 1000)
			this.setState({
				idTimer: idInter,
			})
			
    }

	countBombArround=(i,j, matrix)=>{
		let count = 0;
		let size = matrix.length;
		let top =  i - 1;
		let bottom = i + 1;
		let left = j - 1;
		let right = j + 1;
		if(top >= 0 && left >= 0){
			if(matrix[top][left] === -1){
				count ++;
			}
		}
		if(top >= 0){
			if(matrix[top][j] === -1){
				count ++;
			}
		}
		if(top >= 0 && right < size){
			if(matrix[top][right] === -1){
				count ++;
			}
		}
		if(left >= 0){
			if(matrix[i][left] === -1){
				count ++;
			}
		}
		if(right < size){
			if(matrix[i][right] === -1){
				count ++;
			}
		}
		if(bottom < size && left >= 0){
			if(matrix[bottom][left] === -1){
				count ++;
			}
		}
		if(bottom < size){
			if(matrix[bottom][j] === -1){
				count ++;
			}
		}
		if(bottom < size && right < size){
			if(matrix[bottom][right] === -1){
				count ++;
			}
		}
		return count;
	}

	createMatrix =(gameMode)=>{
		
		let bomb = this.state.nBomb[gameMode];
		let matrixSize = this.state.nRow[gameMode];
		let result = [];

		for(let i = 0 ; i < matrixSize ; i++){
			let temp = [];
			for(let j = 0 ; j < matrixSize; j++){
				temp.push(0)
			}
			result.push(temp)
		}

		for(let count = 0 ; count < bomb; count++){
			let i = getRndInteger(0, matrixSize - 1);
			let j = getRndInteger(0, matrixSize - 1);
			while(result[i][j] !== 0){
				i = getRndInteger(0, matrixSize - 1);
				j = getRndInteger(0, matrixSize - 1);
			}
			result[i][j] = -1;
		}

		for(let i = 0; i < matrixSize ; i ++){
			for(let j = 0 ; j < matrixSize ; j++){
				if(result[i][j] !== -1)
				result[i][j] = this.countBombArround(i,j,result);
			}
		}
		
		
		this.setState({
			matrix: result,
			nFlag: this.state.flags[gameMode],
		})

	}

	componentDidMount(){
		this.createMatrix(this.state.gameMode);
	}

	changeMode=(mode)=>{
		
		
		this.setState({
			gameMode: mode,
			
		})
		this.init(mode);
		
		
	}

	restart=()=>{
		this.changeMode(this.state.gameMode);
		
		this.setState({
			isRestart: 1,
			
		})
	}



	cleartRestart=()=>{
		
		this.setState({
			isRestart: 0,
		})
	}

	handleFlag=(row,col, n)=>{
		this.setState({
			nFlag: this.state.nFlag + n,
		})
	}

	handleWin=()=>{
		this.setState({
			isWin: 1,
		})
		clearInterval(this.state.idTimer)
		

	}

	handleLose=()=>{
		this.setState({
			isLose: 1,
		})
		clearInterval(this.state.idTimer)
	
	}

	render(){
		return (
			<div className="container">

				{!this.state.startGame ? <Start closeStart={this.closeStart}></Start> : ""}
				{this.state.isWin ? 
					<MessageBox 
						message="win"
						playTime={this.state.time}
						restart={this.restart}
					/> : 
					this.state.isLose ?
						<MessageBox 
							message="lose"
							playTime={this.state.time}
							restart={this.restart}
						/> : 
						""
					}
				<h1 className="game-title">
					Minesweeper Game by Dang Khoa
				</h1>

				

				<Toolbar 
					changeMode={this.changeMode}
					restart={this.restart}
					flag={this.state.nFlag}
					time={this.state.time}
				/>
				<Board 
					matrix={this.state.matrix} 
					gameMode={this.state.gameMode}
					boardSize={this.state.nRow[this.state.gameMode]}
					isRestart={this.state.isRestart}
					cleartRestart={this.cleartRestart}
					handleFlag={this.handleFlag}
					nFlag={this.state.nFlag}
					handleWin={this.handleWin}
					handleLose={this.handleLose}
				/>
			</div>
		)
	}

  	
}

export default App;
