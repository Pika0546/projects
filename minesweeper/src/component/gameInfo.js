import hourglass from '../img/hourglass.png';
import flag from '../img/flag.png';

import React, {Component} from 'react';

class GameInfo extends Component {
	render(){
		return (
            <div className="game-info">
                <div className="mine-number">
                    <img src={flag} alt="flag" />
                    <span>{this.props.flag}</span>
                </div>
                <div className="time-container">
                    <img src={hourglass} alt="" />
                    <span>{this.props.time}</span>
                </div>
            </div>
		)
	}
  	
}

export default GameInfo;
