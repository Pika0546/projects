import React from 'react'
import './Note.css'
const Note = ({subject, content, id, deleteNote, getNoteToEdit}) => {
   
    return (
        <div className="note">
            <div className="navbar">
                <h4>{subject}</h4>
                <div className="button-group">
                    <button 
                        className="edit-note"
                        onClick={() => {
                            getNoteToEdit(id);
                        }}
                    >
                        <i className="fas fa-edit" />
                    </button>
                    <button 
                        className="delete-note" 
                        onClick={() => {
                            deleteNote(id);
                        }}
                    >
                        <i className="fas fa-trash-alt" />
                    </button>
                </div>
            </div>
            <div className="note-content">
                <p>
                    {content}
                </p>
            </div>
        </div>
    )
}

export default Note
