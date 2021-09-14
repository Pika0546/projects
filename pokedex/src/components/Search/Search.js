import React, { useRef} from 'react'
import './Search.scss';
const Search = ({getFilter}) => {
    const refContainer = useRef(null);
    const handleSubmit = (e) => {
        e.preventDefault();
        getFilter(refContainer.current.value.toLowerCase());
    };

    return (
        <div className="search">
            <form onSubmit={handleSubmit}>
                <input className="search__input"
                    type="text" 
                    placeholder="Id or name"
                    ref={refContainer}
                ></input>
                <button className="search__button" type='submit' ><i className="fas fa-search"></i></button>
            </form>
        </div>
    )
}

export default Search
