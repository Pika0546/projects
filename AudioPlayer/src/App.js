import React from 'react'

import Header from './components/Header'
import AudioPlayer from './components/AudioPlayer'

import './App.scss';
import tracks from './tracks'
import { useState} from 'react';

const App = () => {
	const [index, setIndex] = useState(0);
	const [isPlay, setIsPlay] = useState(false);

	const onChangeTrack = (newIndex) =>{
		setIndex(newIndex);
	}

	const onChangePlay = (newIsPlay) => {
		setIsPlay(newIsPlay);
	}

	return (
		<div className="app">
			<Header tracks={tracks} index = {index} onChangeTrack={onChangeTrack} isPlay={isPlay}></Header>
			<AudioPlayer tracks={tracks} index = {index} onChangePlay={onChangePlay}></AudioPlayer>
		</div>
	)
}

export default App

