import { useState, useEffect } from 'react';

const useInfiniteScroll = (callback) => {
    const [isFetching, setIsFetching] = useState(false);

    const handleScroll = () => {
        if (window.innerHeight + document.documentElement.scrollTop === document.documentElement.offsetHeight){
            setIsFetching(true);
        }
    }

    useEffect(() => {
        document.addEventListener("scroll", handleScroll)        
        return () => {
            document.removeEventListener("scroll", handleScroll);
        }
    }, [])

    useEffect(() => {
        if(isFetching){
            callback();
        }
    }, [isFetching]);

    return [isFetching, setIsFetching];
}

export default useInfiniteScroll;