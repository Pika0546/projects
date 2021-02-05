import React, {Component} from 'react';

class GameMode extends Component {

    changeMode=(event)=>{
        let value = event.target.value;
        
        this.props.changeMode(value);
    }

	render(){
		return (
            <div className="game-mode">
                <select 
                    name="mode" 
                    id="mode"
                    onChange={this.changeMode}
                >
                    <option value={0}>
                        Easy
                    </option>
                    <option value={1}>
                        Medium
                    </option>
                    <option value={2}>
                        Hard
                    </option>
                </select>
            </div>
		)
	}
  	
}

export default GameMode;
