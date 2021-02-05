import React, {Component} from 'react';
import GameInfo from './gameInfo';
import GameMode from './gameMode';
import Restart from './restart';

class Toolbar extends Component {

	render(){
		return (

            <div className="toolbar">
                <GameMode changeMode={this.props.changeMode}/>
                <GameInfo 
                    flag={this.props.flag}
                    time={this.props.time}
                />
                <Restart restart={this.props.restart}/>
            </div>
			
		)
	}
  	
}

export default Toolbar;
