import pikachu from '../img/pikachu.png';
import React, {Component} from 'react';

class Restart extends Component {

    restart=()=>{
        this.props.restart();
    }

	render(){
		return (
            <div className="emoji-container">
                <button 
                    className="emoji"
                    onClick={this.restart}
                >
                    <img src={pikachu} alt="" />
                </button>
            </div>
		)
	}
  	
}

export default Restart;
