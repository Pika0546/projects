import React from 'react'
import './Loading.scss'
const Loading = ({className}) => {
    return (
        <div className={`loading loading--${className}`}>
            <div className="pokeball">
                <div className="pokeball__top"></div>
                <div className="pokeball__bottom"></div>
                <div className="pokeball__line"></div>
                <div className="pokeball__middle"></div>

            </div>
        </div>
    )
}

export default Loading
