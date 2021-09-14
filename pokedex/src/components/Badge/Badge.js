import React from 'react'
import './Badge.scss'
const Badge = ({type}) => {

   
    return (
        <div className={`badge badge--${type}`}>
            {type}
        </div>
    )
}

export default Badge
