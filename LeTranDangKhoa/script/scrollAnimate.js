setTimeout(()=>{
    let scrollObject = document.querySelectorAll(".js-scroll");
    const SCROLL_OFFSET = 100;
    
    let throttleTimer = false;
 
    const throttle = (callback, time) => {
        //don't run the function while throttle timer is true
        if (throttleTimer) return;
        
        //first set throttle timer to true so the function doesn't run
        throttleTimer = true;
        
        setTimeout(() => {
            //call the callback function in the setTimeout and set the throttle timer to false after the indicated time has passed 
            callback();
            throttleTimer = false;
        }, time);
    }
    const elementInView = (el, scrollOffset = 0) => {
        const elementTop = el.getBoundingClientRect().top;
        
        return (
          elementTop <= 
          ((window.innerHeight || document.documentElement.clientHeight) - scrollOffset)
        );
    
    };
    
    const displayScrollElement = (element) => {
        element.classList.add("scrolled");
    };
    
    const hideScrollElement = (element) => {
        element.classList.remove('scrolled');
    }
    
    const handleScrollAnimation = () => {
        scrollObject.forEach((el) => {
            if (elementInView(el, SCROLL_OFFSET)) {
                displayScrollElement(el);
            } else {
                hideScrollElement(el);
            }
        })
    }
    
    window.addEventListener('scroll', () => {
        throttle(handleScrollAnimation, 250);
    })
}, 200)