import React from 'react';  
import './Header.scss';
import pokemonBrand from '../../assets/pokemon.png';

const Header = () => {
    return (
        <div className="header">
                <img 
                    src={pokemonBrand} 
                    alt="Pokemon"
                    onClick={()=>{
                        window.location.reload(false);
                    }}
                ></img>
        </div>
    )
}

export default Header
