import React from 'react'
import Menu from './Menu'
import { useState, useEffect} from 'react';
const Header = ({tracks, index, onChangeTrack, isPlay}) => {
    const [isOpenMenu, setIsOpenMenu] = useState(false);

    const closeMenu = (e)=>{
        if(!e.target.closest(".menu__audio") && !e.target.closest(".header__button")){
            setIsOpenMenu(false);
        }
    }

    useEffect(() => {
        document.addEventListener( "click", closeMenu, false);
        return () => {
            document.removeEventListener("click", closeMenu, false);
        }
    }, [])

    const changeIndex = (index) => {
        setIsOpenMenu(false);
        onChangeTrack(index);
    }

    return (
        <div className="header">
            <span className="place-holder"></span>
            <h3 className="header__title">Now Playing</h3>
            <button 
                className="header__button open-playlist"
                onClick={()=>{setIsOpenMenu(!isOpenMenu)}}
            >
                <span></span>
                <span></span>
                <span></span>
            </button>
			{isOpenMenu && <Menu tracks={tracks} isPlay={isPlay} index = {index} changeIndex={changeIndex}></Menu>}

        </div>
    )
}

export default Header
