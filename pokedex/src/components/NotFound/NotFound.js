import React from 'react'
import './NotFound.scss';
import pokeball from '../../assets/pokeballOpen.png';

const NotFound = () => {
    return (
        <div className="err">
            <div className="err__content">
                <div className="err__img">
                    <img src={pokeball} alt='Pokeball'></img>
                </div>
                <div className="err__text">
                    <h2>POKEMON NOT FOUND!</h2>
                </div>
            </div>
        </div>
    )
}

export default NotFound
