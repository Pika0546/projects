import React from 'react'
import { useState, useEffect, useRef } from 'react';
import AudioControls from './AudioControls'

const AudioPlayer = ({tracks, index, onChangePlay}) => {
    const [trackIndex, settrackIndex] = useState(0);
    const [trackProgress, setTrackProgress] = useState(0);
    const [isPlaying, setIsPlaying] = useState(false);
    const [playMode, setPlayMode] = useState(0);
    const [duration, setDuration] = useState(0);

    const audioRef = useRef(null);
    const intervalRef = useRef(null);
    // const isReady = useRef(false);
    const  getRndInteger = (min, max) => {
        return Math.floor(Math.random() * (max - min + 1) ) + min;
    }

    const startTimer = () => {
        clearInterval(intervalRef.current);
        intervalRef.current = setInterval(() => {
            if (audioRef.current.ended) {
                
            } else {
                setTrackProgress(audioRef.current.currentTime || 0);
                // console.log(audioRef.current.currentTime);
            }
            
        }, 1000);
    }

    useEffect(() => {
        console.log("playing");
        if (isPlaying) {
            audioRef.current.play();
            startTimer();
        } else {
            clearInterval(intervalRef.current);
            audioRef.current.pause();
        }
    }, [isPlaying]);

    // useEffect(() => {
    //     console.log(trackProgress);
    //     console.log(("00" + Math.floor(Math.floor(trackProgress)/60)).substr(-2) + ":" + ("00" + (Math.floor(trackProgress)%60)).substr(-2));

    //     // console.log((Math.floor(trackProgress)%60));
    //     // console.log(getSecond(trackProgress));
    // }, [trackProgress])

    useEffect(() => {
        if (isPlaying) {
            audioRef.current.play();
            startTimer();
        } else {
            clearInterval(intervalRef.current);
            audioRef.current.pause();
        }
      
        setTrackProgress(0);
    }, [trackIndex])
   
    useEffect(()=>{
        settrackIndex(index);
    }, [index])

    useEffect(() => {
       
        return () => {
            clearInterval(intervalRef.current);
            audioRef.current.pause();
        }
    }, [])

    useEffect(() => {
        console.log("rerendered");
    })

    const onLoaded = () => {
        setDuration(audioRef.current.duration);
    }

    const onPlayPauseClick = (status) =>{
        setIsPlaying(status);
        onChangePlay(status);
    };

    const onPrevClick = () => {
        if(trackIndex === 0){
            settrackIndex(tracks.length - 1);
        }
        else{
            settrackIndex(trackIndex - 1);
        }
    };

    const onNextClick = () => {
        if(playMode === -1){
            let nextIndex = trackIndex;
            while(nextIndex === trackIndex){
                nextIndex = getRndInteger(0, tracks.length - 1);
            };
            settrackIndex(nextIndex);
        }
        else{
            if(trackIndex === tracks.length - 1){
                settrackIndex(0); 
                setIsPlaying(false);
                onChangePlay(false);
            }
            else{
                settrackIndex(trackIndex + 1);
            }
        }
        
    };

    const onRandClick = () => {
        if(playMode === -1){
            setPlayMode(0);
        }else{
            setPlayMode(-1);
        }
        audioRef.current.loop = false;
      
    };

    const onReClick = () => {
        if(playMode === 1){
            audioRef.current.loop = false;
            setPlayMode(0);
        }else{
            setPlayMode(1);
            audioRef.current.loop = true;
        }
        
    };

    const onEndedAudio = () => {
        onNextClick();
    };

    const onScrub = (value) => {
            // Clear any timers already running
        clearInterval(intervalRef.current);
        
        setTrackProgress(value);
    }
    
    const onScrubEnd = () => {
        // If not already playing, start
        audioRef.current.currentTime = trackProgress;
        //   if (!isPlaying) {
        //     setIsPlaying(true);
        //   }
        if(isPlaying){
            startTimer();

        }
    }

    return (
        <main>
             <audio
                ref={audioRef}
                src={tracks[trackIndex].src}
                loop={false}
                onEnded={onEndedAudio}
                onLoadedData={onLoaded}
            />
           
            <div className="audio">
                <div className="audio__img--wrapper">
                    <img src={tracks[trackIndex].img.default} alt={tracks[trackIndex].title}></img>
                </div>
                <div className="audio__info">
                    <h1>{ "#" + (trackIndex + 1) + " - " + tracks[trackIndex].title}</h1>
                    <h3>{tracks[trackIndex].artist}</h3>
                </div>
            </div>

            <div className="progress__wrapper">
                <span>{
                    ("00" + Math.floor(Math.floor(trackProgress)/60)).substr(-2) + ":"
                     + ("00" + (Math.floor(trackProgress)%60)).substr(-2)
                }</span>
                <input
                    type="range"
                    value={trackProgress}
                    step="1"
                    min="0"
                    max={duration}
                    className="progress"
                    onChange={(e) => onScrub(e.target.value)}
                    onMouseUp={onScrubEnd}
                    onKeyUp={onScrubEnd}
                />
                  <span>{
                    ("00" + Math.floor(Math.floor(duration)/60)).substr(-2) + ":"
                    + ("00" + (Math.floor((duration)%60))).substr(-2)              
                }</span>
            </div>
  

            <AudioControls 
                isPlaying={isPlaying} 
                playMode = {playMode}
                onPlayPauseClick = {onPlayPauseClick}
                onPrevClick = {onPrevClick}
                onNextClick = {onNextClick}
                onRandClick = {onRandClick}
                onReClick = {onReClick}
            ></AudioControls>
           
        </main>
    )
}

export default AudioPlayer
