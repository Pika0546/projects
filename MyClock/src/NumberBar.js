import React from 'react'
import './NumberBar.css'
const NumberBar = ({number,type}) => {
   
    let column = [];
    for(let i = 0 ; i <= type ; i++){
        column.push(<span 
                        key={i}
                        className={i === number ? "current-time" : ""}
                    >{i}</span>)
    }

    let nbClass = "number-bar " + "number-" + number;

    return (
        <div 
            className={nbClass}
        >
            {column}
        </div>
    )
}

export default NumberBar
