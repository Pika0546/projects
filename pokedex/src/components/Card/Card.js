import React from 'react'
import './Card.scss'
import Badge from '../Badge/Badge'
const Card = ({pokemon, showDetail}) => {
    const renderType = pokemon.types.map((type, index)=>{      
        return <Badge key={index} type={type}></Badge>
    })

    return (
        <div className="card" onClick={()=>{
            showDetail(pokemon);
        }}>
            <div className="card__img">
                <img src={pokemon.img} alt={pokemon.name}></img>
            </div>
            <span className="card__id">{`#${pokemon.id}`}</span>
            <h3 className="card__title">
               {pokemon.name}
            </h3>
            <div className="card__types">
                {renderType}
            </div>
        </div>
    )
}

export default Card
