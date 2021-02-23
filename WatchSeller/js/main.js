$(window).on('load', function(){
    setTimeout(function(){
        $('.preloader').fadeOut('slow');
    }, 600)
})


$(document).ready(function(){
    $('body').scrollspy({target: ".navbar", offset: 50});   
    $(".navbar-collapse").collapse("hide");
    
    
    $(".nav-item").click(function(){
        $(".collapse").collapse("hide");
    })
    
    $('#products-carousel').owlCarousel({
        loop:true,
        margin:0,
        nav:true,
        dots:false,
        autoplay:true,
        smartSpeed:1000,
        responsive:{
            0:{
                items:1
            },
            600:{
                items:2
            },
            1000:{
                items:4
            }
        }
    })

    $('#testimonial-carousel').owlCarousel({
        loop:true,
        margin:0,
        nav:true,
        dots:false,
        autoplay:true,
        smartSpeed:1000,
        responsive:{
            0:{
                items:1
            },
            600:{
                items:1
            },
            1000:{
                items:2
            }
        }
    })
})