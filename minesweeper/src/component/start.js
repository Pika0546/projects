import leftMouse from '../img/leftMouse.png'
import rightMouse from '../img/rightMouse.png'
import flag from '../img/flag.png'
import spade from '../img/spade.png'

import React, {Component} from 'react';

class Start extends Component {

    closeStart=()=>{
        this.props.closeStart();
    }

	render(){
		return (
            <div className="start-screen">
                <div className="intro">
                    <div 
                        className="close-intro"
                        onClick={this.closeStart}
                    >
                        <i className="fas fa-times"></i>
                    </div>
                    <div className="row row1">
                        <img src={leftMouse} alt="left"></img>
                        
                        <img src={spade} alt="dig"></img>
                    </div>
                    <div className="row">
                        <img src={rightMouse} alt="left"></img>
                        <img src={flag} alt="dig"></img>
                    </div>
                </div>
            </div>
		)
	}
  	
}

export default Start;
