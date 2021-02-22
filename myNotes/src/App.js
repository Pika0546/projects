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

// function App() {

// 	const [isOpenForm, setIsOpenForm] = useState(false)
// 	const [myNotes, setMyNotes] = useState([])
// 	const [isEditting, setIsEditting] = useState(false);
// 	const [noteToEdit, setNoteToEdit] = useState(null);



// 	const openForm = () =>{
// 		setIsOpenForm(true);
// 	}

// 	const closeForm = () =>{
// 		setIsOpenForm(false);
// 	}

// 	const addNewNote = (note) =>{
// 		if(note){
			
// 			if(note.id){
// 				let temp = myNotes;
// 				let i = -1;
// 				temp.forEach((item, index) => {
// 					if(item.id === note.id){
// 						i = index;
// 					}
// 				})
// 				temp.splice(i, 1, note)
// 				store(temp);
// 				setMyNotes(temp);
// 			}
// 			else{
				
// 				note.id = new Date().getTime().toString();
// 				store([...myNotes, note]);
// 				setMyNotes([...myNotes, note]);
// 			}
		
// 		}
// 	}

// 	const deleteNote = (id) =>{
// 		if(id){
// 			store(myNotes.filter((note) => note.id !== id))
// 			setMyNotes(myNotes.filter((note) => note.id !== id));
			
// 		}
// 	}

// 	const getNoteToEdit = (id) =>{
// 		if(id){
// 			let noteEdit;
// 			myNotes.forEach((note)=>{
// 				if(note.id === id){
// 					noteEdit = note;
// 				}
// 			})
// 			setIsOpenForm(true)
// 			setIsEditting(true);
// 			setNoteToEdit(noteEdit);
			
// 		}
// 	}

// 	const store = (thing) =>{
// 		localStorage.setItem('notes',  JSON.stringify(thing));
// 	}

// 	useEffect(() => {
// 		const notes = JSON.parse(localStorage.getItem('notes'));
// 		console.log(notes);
// 		setMyNotes(notes)
		
// 	}, [])

// 	return (
// 		<div className="App">
// 			<div className="container">
// 				<div className="header">
// 					<h1>
// 						My Notes
//          			 </h1>
// 					<button className="new-note" onClick={openForm}>+</button>
// 				</div>
				
// 				<Notes 
// 					myNotes={myNotes}
// 					addNewNote={addNewNote}
// 					deleteNote={deleteNote}
// 					getNoteToEdit={getNoteToEdit}
// 				></Notes>
// 				{isOpenForm && 
// 					<FormNote
// 						addNewNote={addNewNote}
// 						closeForm={closeForm}
// 						noteToEdit={isEditting ? noteToEdit : ""}
// 					></FormNote>
// 				}
// 			</div>
// 		</div>
// 	);
// }

// export default App;

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
		return { ...state, isOpenForm: false };
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
					addNewNote={addNewNote}
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
