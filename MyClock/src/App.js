import React, {useEffect, useState} from 'react'
import "./App.css"

import NumberBar from './NumberBar'

const App = () => {

    const [time, setTime] = useState({hour: 0, minute: 0, second: 0})

    useEffect(()=>{
        let theTime = new Date();
        setTime({
            hour: theTime.getHours(),
            minute: theTime.getMinutes(),
            second: theTime.getSeconds(),
        })
    },[])

    setInterval(()=>{
        let theTime = new Date();
        setTime({
            hour: theTime.getHours(),
            minute: theTime.getMinutes(),
            second: theTime.getSeconds(),
        })
    }, 1000)

    return (
        <div className="container">
            <NumberBar
                number={Math.floor(time.hour/10)}
                type={2}
            />
            <NumberBar
                number={time.hour%10}
                type={9}
            />
            <span className="colon">:</span>
            <NumberBar
                number={Math.floor(time.minute/10)}
                type={5}
            />
            <NumberBar
                number={time.minute%10}
                type={9}
            />
            <span className="colon">:</span>
            <NumberBar
                number={Math.floor(time.second/10)}
                type={5}
            />
            <NumberBar
                number={time.second%10}
                type={9}
            />
        </div>
    )
}

export default App
