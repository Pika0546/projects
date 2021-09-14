import './App.css';
import { useEffect, useReducer} from 'react'
import { reducer } from './reducer';
import axios from 'axios';
import Dictionary from './components/Dictionary/Dictionary';
import Header from './components/Header/Header';
import './App.css';
import Search from './components/Search/Search';
import Loading from './components/Loading/Loading';
import NotFound from './components/NotFound/NotFound';
// import PokeDetail from './components/PokeDetail/PokeDetail';

const pokemonlUrl = "https://pokeapi.co/api/v2/pokemon/";
const typesUrl = "https://pokeapi.co/api/v2/type/";
const initialState = {
	filterResult: null,
	isLoading: true,
	data: [],
	types: [],
	nextUrl: pokemonlUrl,
	isOver: false,
	isSearching: false,
	isLoadMore: true,
	isError: false,
	isOpenPokedex: false,
	pokeDetail: null,
}

function App() {
		
	const [state, dispatch] = useReducer(reducer, initialState);

	const fetchData = () =>{
		if(!state.filterResult){
			dispatch({type:"START_LOAD"});
			axios.get(state.nextUrl)
			.then(res=>{
				const data = res.data;
				const axiosList = data.results.map((item)=>{
					return axios.get(item.url);
				});

				Promise.all(axiosList)
				.then((results)=>{
					let pokeList = results.map((item)=>{
						let typeList = item.data.types.map((type)=>{
							return type.type.name;
						});
						return{
							id: item.data.id,
							name: item.data.name,
							types: typeList,
							img: item.data.sprites.front_default,
						}
					});
					if(state.types.length === 0){
						axios.get(typesUrl)
						.then(res=>{
							const data1 = res.data;
							const axiosList1 = data1.results.map((item)=>{
								return axios.get(item.url);
							});
							
							Promise.all(axiosList1)
							.then((result)=>{
								let types = result.map((item)=>{
									let dis = [];
									let ad = [];
									item.data.damage_relations.double_damage_from.forEach(type=>{
										dis.push(type.name);
									});
									item.data.damage_relations.no_damage_to.forEach(type=>{
										dis.push(type.name);
									});
									item.data.damage_relations.double_damage_to.forEach(type=>{
										ad.push(type.name);
									});
									item.data.damage_relations.no_damage_from.forEach(type=>{
										ad.push(type.name);
									});
									return{
										name: item.data.name,
										dis: dis,
										ad: ad
									}
								});
								dispatch({type:'FETCH_DATA', payload: {pokemons: pokeList, nextUrl: data.next, typeList: types}});
							})
						})
					}
					else{
						dispatch({type:'FETCH_DATA', payload: {pokemons: pokeList, nextUrl: data.next, typeList: state.types}});
					}
				})
				.catch(err=>console.log(err));
			}).catch(err=>console.log(err));
		}
	}

	useEffect(() => {
		fetchData();
		return()=>{
			//do not thing
		}
	}, []);

	const getFilter =(filter)=>{
		dispatch({type:'SEARCHING'});
		setTimeout(() => {
			if(filter.length === 0){
				dispatch({type:'RESET_POKEMONS'});
			}
			else{
				axios.get(pokemonlUrl + filter)
				.then(res => {
					const data = res.data;
					let typeList = data.types.map((type)=>{
						return type.type.name;
					});
					const pokemon = {
						id: data.id,
						name: data.name,
						types: typeList,
						img: data.sprites.front_default,
					}
					dispatch({type:'FILTERING', payload: pokemon});
		
				})
				.catch(err=>{
					dispatch({type:"NOT_FOUND"})
				})
			}
		}, 1000);
	}

	const showDetail = (pokemon)=>{
		dispatch({type: "SET_DETAIL", payload: pokemon});
	}

	// const renderDetail = () =>{
	// 	let pokeTypes = [];
	// 	state.pokeDetail.types.forEach(item=>{
	// 		state.types.forEach((type)=>{
	// 			if(type.name === item){
	// 				pokeTypes.push(type);
	// 			}
	// 		});
	// 	});
	// 	return <PokeDetail pokemon={state.pokeDetail} types={pokeTypes}></PokeDetail>
	// }

	return (
		<div className="app">
			
			{state.isLoading ? 
				<Loading className="big"></Loading> :
				<>
					<Header></Header>
					<Search getFilter={getFilter}></Search>
					<main>
						<div className="main">
							{state.isSearching ?                     
								<Loading className="small"></Loading> :
								state.isError ?
								<NotFound></NotFound> : 
								<Dictionary
									isOver={state.filterResult ? true : state.isOver} 
									pokeList={state.filterResult ? state.filterResult : state.data} 
									fetchData={fetchData}
									isLoadMore={state.isLoadMore}
									showDetail={showDetail}
								></Dictionary>
							}
						</div>
					</main>
					{/* {
						state.isOpenPokedex ?
						renderDetail() :
						""
					} */}
				</>
			}
		</div>
	);
}

export default App;
