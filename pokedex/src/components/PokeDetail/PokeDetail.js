import React from 'react'
import './PokeDetail.scss';
import Badge from '../Badge/Badge';
const PokeDetail = ({pokemon, types}) => {

    const renderDis = () => {
        let badge = []
        types.forEach((type)=>{
            type.dis.forEach((dis, index)=>{
                badge.push (<Badge key={index} type={dis}></Badge>);
            });
        });
       return badge;
    }

    const renderAd = () => {
        let badge = []
        types.forEach((type)=>{
            type.ad.forEach((ad, index)=>{
                badge.push (<Badge key={index} type={ad}></Badge>);
            });
        });
        return badge;
    }

    const renderType = () =>{
        return types.map((type, index)=>{
            return <Badge key={index} type={type.name}></Badge>
        });
    }

    return (
        <div className="pokedex">
            <div className="pokedex__screen">
                <div className="left">
                    <div className="id">
                        <h1>
                            {pokemon.id}
                        </h1>
                    </div>
                    <div className="name">
                        <h1>
                            {pokemon.name}
                        </h1>
                    </div>
                    <div className="type">
                        {renderType()}
                    </div>
                </div>
                <div className="mid">
                    <img src={pokemon.img} alt={pokemon.name}></img>
                </div>
                <div className="right">
                    <div className="type-relate">
                        <h3>
                            Advantage
                        </h3>
                        <div className="type-relate__list">
                            {renderDis()}
                        </div>
                    </div>
                    <div className="type-relate">
                        <h3>
                            Disadvantage
                        </h3>
                        <div className="type-relate__list">
                            {renderAd()}
                        </div>
                    </div>
                </div>
                <button>
                    &times;
                </button>
            </div>
            
        </div>
    )
}

export default PokeDetail
