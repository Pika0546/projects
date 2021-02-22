import './FormNote.css'
import React, { useState, useEffect, useContext } from 'react';
const FormNote = ({closeForm, addNewNote, noteToEdit}) => {
    const [note, setNote] = useState({subject: "", content: "", id:""})
    const [isValid, setIsValid] = useState(0)

    useEffect(() => {
        if(noteToEdit){
            setNote(noteToEdit);
        }
    }, [])

    const closeFormNote = () => {
        closeForm();
    }

    const handleChange = (e) =>{
        const name = e.target.name;
        const value = e.target.value;
        setNote({...note, [name]: value})
    }

    const handleSubmit = (e) =>{
        e.preventDefault();
        const {subject, content} = note;
        if(subject === "" && content === ""){
            setIsValid(3);
        }
        else if(subject === ""){
            setIsValid(1);
        }
        else if(content === ""){
            setIsValid(2);
        }
        else{
            
            addNewNote({...note, id: noteToEdit ? noteToEdit.id : ""});
            closeFormNote();

        }
        
    }

    return (
        <div className="form-note-container">
            <div className="form-note">
                <h3>Note</h3>
                <button 
                    type="button" 
                    className="close-form"
                    onClick={closeFormNote}
                >
                    ×
                </button>
                <form onSubmit={handleSubmit}>
                    <div className="form-control">
                        <label htmlFor="subject">Subject</label>
                        <input 
                            type="text" 
                            name="subject" 
                            autoComplete="off"
                            value={note.subject}
                            onChange={handleChange}
                        />
                        {isValid === 1 || isValid === 3 ? <p className="invalid-form">Subject can not be empty</p> : ""}
                    </div>
                    <div className="form-control">
                        <label htmlFor="content">Content</label>
                        <textarea 
                            name="content" 
                            id="note-content" 
                            cols={25} rows={7}
                            value={note.content}
                            onChange={handleChange}
                        />
                        {isValid === 2 || isValid === 3 ? <p className="invalid-form">Content can not be empty</p> : ""}
                    </div>
                    <button type="submit">OK</button>
                </form>
            </div>
        </div>
    )
}

export default FormNote
