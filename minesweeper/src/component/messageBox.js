import trophy from '../img/trophy.png';
import explosion from '../img/explosion.png';
import hourglass from '../img/hourglass.png';


import React, {Component} from 'react';

class MessageBox extends Component {
    restart=()=>{
        this.props.restart();
    }

	render(){
        let mainImage = "";
        let subImage = "";
        let mess = this.props.message;
        let subMess = "";
        if(mess === "win"){
            mainImage = <img src={trophy} alt="trophy"></img>
            subMess = this.props.playTime;
            subImage = <img src={hourglass} alt="time"></img>
        }
        else if(mess === "lose"){
            mainImage = <img src={explosion} alt="boom"></img>
        }

		return (
           <div className="message-container">
               <div className="message-content">
                    <div className="main-message">
                        {mainImage}
                        <p>{mess}</p>
                        <div className="sub-message">
                            {subImage}
                            <p>{subMess}</p>
                        </div>
                    </div>
                    
                    <button className="restart-message" onClick={this.restart}>
                        <i className="fas fa-undo"></i>
                    </button>
               </div>
           </div>
		)
	}
  	
}

export default MessageBox;
