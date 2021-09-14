export const reducer = (state, action) =>{
    
    if(action.type === 'FETCH_DATA'){
        let isOver = false;
        if(!action.payload.nextUrl){
            isOver = true;
        }
        const newData = [...state.data, ...action.payload.pokemons]
        return{
            ...state,
            data: newData,
            isLoading: false,
            nextUrl: action.payload.nextUrl,
            isOver: isOver,
            isError: false,
            isLoadMore: false,
            types: action.payload.typeList
        }
    }
    else if(action.type === 'RESET_POKEMONS'){
        return{
            ...state,
            filterResult: null,
            isLoading: false,
            isSearching: false,
            isError: false,
            isLoadMore: false,
        }
    }
    else if (action.type === 'FILTERING'){
        return{
            ...state,
            filterResult: [action.payload],
            isSearching: false,
            isError: false,
        }
    }
    else if (action.type === 'SEARCHING'){
        return{
            ...state,
            filterResult: [],
            isSearching: true,
        }
    }
    else if (action.type === 'START_LOAD'){
        return{
            ...state,
            isLoadMore: true,
        }
    }
    else if(action.type === 'NOT_FOUND'){
        return{
            ...state,
            filterResult: [],
            isSearching: false,
            isError: true,
        }
    }
    else if(action.type === 'SET_DETAIL'){
        return{
            ...state,
            isOpenPokedex: true,
            pokeDetail: action.payload
        }
    }
    else{
        return {
            ...state
        }
    }
}