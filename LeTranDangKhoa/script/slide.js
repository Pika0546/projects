var slideIndex = 0;

function plusSlide(n) {
    slideIndex += n;
    showSlide(slideIndex);
}

let nextSlideBtn = document.getElementById("next-slide");
let prevSlideBtn = document.getElementById("prev-slide");

nextSlideBtn.addEventListener("click",function(){
    plusSlide(1);
    
})

prevSlideBtn.addEventListener("click",function(){
    plusSlide(-1);
})


var w = window.innerWidth;
    if (w <= 600) {
        
        nextSlideBtn.innerHTML = '<i class="fas fa-angle-down"></i>';
        prevSlideBtn.innerHTML = '<i class="fas fa-angle-up"></i>';
    } else {
       
        nextSlideBtn.innerHTML = '<i class="fas fa-angle-right">';
        prevSlideBtn.innerHTML = '<i class="fas fa-angle-left">';
    }
window.addEventListener("resize", function () {
    let slides = document.getElementsByClassName("slide__container");
    let nextSlideBtn = document.getElementById("next-slide");
    let prevSlideBtn = document.getElementById("prev-slide");
    var w = window.innerWidth;
    if (w <= 600) {
        for (var i = 0; i < slides.length; i++) {
            slides[i].style.left = 0;
        }
        nextSlideBtn.innerHTML = '<i class="fas fa-angle-down"></i>';
        prevSlideBtn.innerHTML = '<i class="fas fa-angle-up"></i>';
    } else {
        for (var i = 0; i < slides.length; i++) {
            slides[i].style.top = 0;
        }
        nextSlideBtn.innerHTML = '<i class="fas fa-angle-right">';
        prevSlideBtn.innerHTML = '<i class="fas fa-angle-left">';
    }
    showSlide(slideIndex);
})

function showSlide(n) {
    let slides = document.getElementsByClassName("slide__container");
    let nextSlideBtn = document.getElementById("next-slide");
    let prevSlideBtn = document.getElementById("prev-slide");
    if (n >= slides.length) {
        n = slides.length - 1;
    }
    if (n < 0) {
        n = 0;
    }
    slideIndex = n;
    var w = window.innerWidth;
   
    for (var i = 0; i < slides.length; i++) {
        slides[i].style.top = 0;
        slides[i].style.left = "75%";
        slides[i].className = slides[i].className.replace(" slide--active", "");
    }
    if (w < 600) {
        for (var i = 0; i < slides.length; i++) {
            slides[i].style.left = 0;
            slides[i].style.top =  (slides.length - 1)*35 -70 * (slideIndex ) + "%";
        }
    }
    else {
        for (var i = 0; i < slides.length; i++) {
            slides[i].style.left = (slides.length - 1)*25 + -50 * (slideIndex) + "%";
        }
    }
 
    slides[slideIndex].className += " slide--active";
    if(slideIndex == 0){
        prevSlideBtn.style.display = "none";
    }else{
        prevSlideBtn.style.display = "block";
    }
    if(slideIndex == slides.length - 1){
        nextSlideBtn.style.display = "none";
    }else{
        nextSlideBtn.style.display = "block";
    }



}

function slideShow(n){
    slideIndex = n;
    $("#project-details-section").fadeIn(200);
    showSlide(slideIndex);
}

function closeSlideShow () {
    $("#project-details-section").fadeOut(0);

}