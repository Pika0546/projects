import React from 'react'
import Note from '../Note/Note'
import './Notes.css'

const Notes = ({myNotes, openForm, deleteNote, getNoteToEdit}) => {
    
    return (
        <div className="notes">

            {!myNotes.length ? 
                <div className="first-intro">
                    <i className="fas fa-edit"></i>
                    <h3>You haven't created any note !</h3>
                    <span onClick={openForm}>Create one !</span>
                </div> : ""
            }
            {
                myNotes.map((note, index) => {
                    return <Note
                        key={note.id}
                        {...note}
                        deleteNote={deleteNote}
                        getNoteToEdit={getNoteToEdit}
                    />
                })
            }
        </div>
    )
}

export default Notes
