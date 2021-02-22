import React from 'react'
import Note from '../Note/Note'
import './Notes.css'

const Notes = ({myNotes, addNewNote, deleteNote, getNoteToEdit}) => {
    
    return (
        <div className="notes">
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
