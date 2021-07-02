import React from 'react'

const Menu = ({tracks, index, changeIndex, isPlay}) => {

    const playlist = tracks.map((audio, pos)=>{
        return(
            <div 
                key={pos} 
                className={
                        "menu__audio" + 
                        (pos === index ? " menu__audio--current": "") +
                        ((pos === index && isPlay === true) ? " menu__audio--play": "")
                    } 
                onClick={()=>{
                    changeIndex(pos);
                }}
            >
                <div className="menu__audio__img">
                    <img src={audio.img.default} alt={audio.title}></img>
                    <div className="menu__audio__img--overlay">
                        <i className="fas fa-play"></i>
                    </div>
                </div>
                <div className="menu__audio__info">
                    <span>{audio.title}</span>
                    <span>{audio.artist}</span>
                </div>
                <button
                    onClick={(e)=>{
                        e.stopPropagation();
                    }}
                >
                    <a href={audio.src} download={audio.title}>
                        <i className="fas fa-download"></i>
                    </a>
                </button>
            </div>
        )
    })

    return (
        <div className="menu">
            <h3>Playlist</h3>
            {playlist}
        </div>
    )
}

export default Menu
