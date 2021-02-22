import React from 'react'
import './Note.css'
const Note = ({subject, content, id, deleteNote, getNoteToEdit}) => {
    let temp = content.split('\n');
    let temp2 = [];
    // temp.forEach((element) => {
    //     temp2.push(element);
    //     temp2.push(<br/>);
    // });
    for(let i = 0 ; i < temp.length ; i++){
        temp2.push(temp[i]);
        temp2.push(<br key={i}/>);
    }

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
                    {/* {content} */}
                    {temp2}
                </p>
            </div>
        </div>
    )
}

export default Note
