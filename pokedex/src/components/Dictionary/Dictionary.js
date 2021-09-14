import React from 'react';
import Card from '../Card/Card';
import useInfiniteScroll from '../../hook/useInfiniteScroll';
import './Dictionary.scss';
import Loading from '../Loading/Loading';
const Dictionary = ({pokeList, fetchData, isOver, isLoadMore, showDetail}) => {

    const fetchMore = () => {
        if(!isOver){
            fetchData();
        }
        setIsFetching(false);
    }
    
    const [isFetching, setIsFetching]  = useInfiniteScroll(fetchMore);

    const list = pokeList.map((pokemon)=>{
        return <Card key={pokemon.id} showDetail={showDetail} pokemon={pokemon}></Card>
    });
    return (
        <div className="dictionary">
            <div className="dictionary__content">
                {list}
            </div>
            <div className="dictionary__row">
                {(isLoadMore && !isOver) ? 
                    <Loading className="small"></Loading> : ""
                }
            </div>

        </div>

    )
}

export default Dictionary
