import './App.css';
import React, { useState, useEffect, useReducer  } from 'react';
import FormNote from './components/FormNote/FormNote'
import Notes from './components/Notes/Notes'
import Note from './components/Note/Note';

const defaultState = {
	myNotes: [],
	isOpenForm: false,
	isEditting: false,
	noteToEdit: null,
}

const store = (thing) =>{
	localStorage.setItem('notes',  JSON.stringify(thing));
}

const reducer = (state, action) => {
	if(action.type === 'GET_DATA'){
		let newList = JSON.parse(localStorage.getItem('notes'));
		if(!newList){
			newList = [];
		}
		return{
			...state,
			myNotes: newList,
		}
	}
	if (action.type === 'ADD_NOTE') {
		const note = action.payload;
		if(note.id){
			let newList = state.myNotes;
			let i = -1;
			newList.forEach((item, index) => {
				if(item.id === note.id){
					i = index;
				}
			})
			newList.splice(i, 1, note)
			store(newList);
			return {
				...state,
				myNotes: newList,
				noteToEdit: null,
			};
		}
		else{
			note.id = new Date().getTime().toString();
			let newList = [...state.myNotes, note];
			store(newList);
			return {
				...state,
				myNotes: newList,
			};
		}
	}
	if (action.type === 'EDIT_NOTE') {
		const id = action.payload;
		let noteEdit;
		state.myNotes.forEach((note)=>{
			if(note.id === id){
				noteEdit = note;
			}
		})
		return { 
			...state, 
			isOpenForm: true, 
			isEditting: true,
			noteToEdit: noteEdit 
		};
	}
	if (action.type === 'DELETE_NOTE') {
		const id = action.payload;
		const newList = state.myNotes.filter((note) => note.id !== id)
		store(newList);
		return { ...state, myNotes: newList,  };
	}
	if (action.type === 'OPEN_FORM') {
		return { ...state, isOpenForm: true };
	}
	if(action.type === 'CLOSE_FORM'){
		return { ...state, isOpenForm: false, noteToEdit: null };
	}
	throw new Error('no matching action type');
};

function App() {

	const [state, dispatch] = useReducer(reducer, defaultState)
	const openForm = () =>{
		dispatch({type: 'OPEN_FORM'});
	}

	const closeForm = () =>{
		dispatch({type: 'CLOSE_FORM'});
	}

	const addNewNote = (note) =>{
		if(note){
			dispatch({type: "ADD_NOTE", payload: note})
		}
	}

	const deleteNote = (id) =>{
		if(id){
			dispatch({type:"DELETE_NOTE", payload: id});
		}
	}

	const getNoteToEdit = (id) =>{
		if(id){
			dispatch({type: "EDIT_NOTE", payload: id});
			
		}
	}

	useEffect(() => {
		dispatch({type: 'GET_DATA'})
	}, [])
	
	return (
		<div className="App">
			<div className="container">
				<div className="header">
					<h1>
						My Notes
         			 </h1>
					<button className="new-note" onClick={openForm}>+</button>
				</div>
				
				<Notes 
					myNotes={state.myNotes}
					openForm={openForm}
					deleteNote={deleteNote}
					getNoteToEdit={getNoteToEdit}
				></Notes>
				{state.isOpenForm && 
					<FormNote
						addNewNote={addNewNote}
						closeForm={closeForm}
						noteToEdit={state.isEditting ? state.noteToEdit : ""}
					></FormNote>
				}
				
			</div>
		</div>
	);
}

export default App;
