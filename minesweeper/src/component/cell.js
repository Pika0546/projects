import bomb from '../img/bomb.png';
import flag from '../img/flag.png';

import React, {Component} from 'react';

class Cell extends Component {

    constructor(props){
        super(props);

        this.state={
            isOpened: 0,
            value: 0,
            isFlagOn: 0,
            row: 0,
            col: 0,
            isFlagable: 1,
        }


    }

    static getDerivedStateFromProps(props, state) {
        return {
                    value: props.cellValue,
                    row: props.row,
                    col: props.col,
                    isOpened: props.status,
                    isFlagable: props.isFlagable,
                    isFlagOn: props.isFlagOn,

                };
    }

    
    showContent=()=>{
        if(this.state.value === -1){
            return <img src={bomb} alt="bomb"></img>
        }
        else if(this.state.value > 0){
            return this.state.value;
        }
        else{
            return ""
        }
        
    }

    clicked=()=>{
        
        if(!this.state.isOpened && !this.state.isFlagOn){
            
            this.props.onDig(this.state.row, this.state.col)
        }
    }

    toggleFlag=()=>{
        if(this.state.isFlagOn){
            this.props.handleFlag(this.state.row, this.state.col, 1)
            
        }
        else if(this.state.isFlagable){
            this.props.handleFlag(this.state.row, this.state.col, -1)
            
        }
       
      
        
    }

	render(){
        let content = this.showContent();
        let cClass = "cell ";
        if(this.props.cTyle === 0){
            cClass += "cell-even "
        }else{
            cClass += "cell-odd "
        }

        cClass += ("cell" + this.props.size + " ")

        if(!this.state.isOpened){
            cClass += "not-open ";
            if(this.props.leftOpened){
                cClass += "border-left ";
            }
            if(this.props.rightOpened){
                cClass += "border-right ";
            }
            if(this.props.topOpened){
                cClass += "border-top ";
            }
            if(this.props.bottomOpened){
                cClass += "border-bottom ";
            }
        }
       

        
       

		return (
            <div 
                className={cClass}
                onClick={this.clicked}
                id={this.props.id}
                onContextMenu={this.toggleFlag}
            >
                {this.state.isOpened ? 
                    <span className={"number"+content}> {content} </span> : 
                    this.state.isFlagOn ? 
                        <img src={flag} alt="flag"></img> : ""    
                }
                
            </div>
		)
	}
  	
}

export default Cell;
