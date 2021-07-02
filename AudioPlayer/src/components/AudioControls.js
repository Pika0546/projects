import React from 'react'

const AudioControls = ({
    isPlaying,
    playMode,
    onPlayPauseClick,
    onPrevClick,
    onNextClick,
    onRandClick,
    onReClick
  }) => {
    return (
        <div className="control">
           
            <button 
                className={"control__button --level-1" + ((playMode === -1) ? " active" : "")}
                onClick = {onRandClick}
            >
                <i className="fas fa-random"></i>            
            </button>

            <button 
                className="control__button --level-2"
                onClick = {onPrevClick}
            >
                <i className="fas fa-backward"></i>
            </button>

            {isPlaying ? (
                <button 
                    className="control__button --level-3"
                    onClick={()=>{onPlayPauseClick(false)}}
                >
                    <i className="fas fa-pause"></i>
                </button>

            ):(
                <button 
                    className="control__button --level-3"
                    onClick={()=>{onPlayPauseClick(true)}}
                >
                    <i className="fas fa-play"></i>
                </button>

            )}

             <button 
                className="control__button --level-2"
                onClick = {onNextClick}
            >
                <i className="fas fa-forward"></i>
            </button>

            <button 
                className={"control__button --level-1" + ((playMode === 1) ? " active" : "")}
                onClick = {onReClick}
            >
                <i className="fas fa-redo-alt"></i>     
            </button>
        </div>
    )
}

export default AudioControls
