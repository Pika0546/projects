var navBtn = document.getElementById("navigation-button");
var navIcon = document.querySelector("#navigation-icon");
var navFlag = false;

var activeColor = "pink";

navBtn.addEventListener("click", function (e) {
    navFlag = !navFlag;
    if (navFlag) {
        document.getElementById("nav").style.width = "100%";
        navIcon.className += " navigation__close-btn";
    }
    else {
        document.getElementById("nav").style.width = "0%";
        navIcon.className = navIcon.className.replace(" navigation__close-btn", "");

    }
})

var portBtns = document.getElementsByClassName("port-btn");
for (var i = 0; i < portBtns.length; i++) {
    portBtns[i].addEventListener("click", function () {
        for (var j = 0; j < portBtns.length; j++) {
            portBtns[j].className = portBtns[j].className.replace(" btn-tab--active", "");
            portBtns[j].className = portBtns[j].className.replace("pink-text", "transparent-text" );
            portBtns[j].className = portBtns[j].className.replace("blue-text", "transparent-text");
            portBtns[j].className = portBtns[j].className.replace("red-text","transparent-text");
            portBtns[j].className = portBtns[j].className.replace("yellow-text", "transparent-text");
            portBtns[j].className = portBtns[j].className.replace("green-text","transparent-text");
            portBtns[j].className = portBtns[j].className.replace("cyan-text","transparent-text");

        }
        this.className += " btn-tab--active";
        this.className = this.className.replace("pink-text", activeColor + "-text");
        this.className = this.className.replace("transparent", activeColor);
        this.className = this.className.replace("blue-text", activeColor + "-text");
        this.className = this.className.replace("red-text", activeColor + "-text");
        this.className = this.className.replace("yellow-text", activeColor + "-text");
        this.className = this.className.replace("green-text", activeColor + "-text");
        this.className = this.className.replace("cyan-text", activeColor + "-text");
    })
}




function replaceDefaultStyle(curr, next){
    var elements = document.querySelectorAll("[class*=" +curr + "]");
    for(var i = 0; i < elements.length; i++){
        elements[i].className = elements[i].className.replaceAll(curr, next);
    }

}

function validateEmail(email) {
    const re = /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(String(email).toLowerCase());
}

validateForm =()=>{
    let name = document.forms["myForm"]["name"].value;
    let email = document.forms["myForm"]["mail"].value;
    let sub = document.forms["myForm"]["subject"].value;
    let mess = document.forms["myForm"]["message"].value;
    let flag = true;
    if(name === ""){
        flag = false;
        document.getElementById("invalid-name").style.display="block";
    }
    else{
        document.getElementById("invalid-name").style.display="none";
    }

    if(!validateEmail(email)){
        flag = false;
        document.getElementById("invalid-mail").style.display="block";
    }
    else{
        document.getElementById("invalid-mail").style.display="none";
    }

    if(sub === ""){
        flag = false;
        document.getElementById("invalid-subject").style.display="block";
    }
    else{
        document.getElementById("invalid-subject").style.display="none";
    }

    if(mess === ""){
        flag = false;
        document.getElementById("invalid-message").style.display="block";
    }
    else{
        document.getElementById("invalid-message").style.display="none";
    }
    
    if(flag){
        document.getElementById("invalid-mail").style.display="none";
        document.getElementById("invalid-subject").style.display="none";
        document.getElementById("invalid-message").style.display="none";
        document.getElementById("invalid-name").style.display="none";
    }
    return flag;
}

function setActiveStyle(colorName){
    replaceDefaultStyle("pink", colorName);
    replaceDefaultStyle("blue", colorName);
    replaceDefaultStyle("green", colorName);
    replaceDefaultStyle("red", colorName);
    replaceDefaultStyle("yellow", colorName);
    replaceDefaultStyle("cyan", colorName);
    activeColor = colorName;
}

function showProjectType(type) {
 
    if (type == " all-project")
        type = "";
    var cells = $(".port-fillter__cell");
    for (var i = 0; i < cells.length; i++) {
        if ($(cells[i]).attr("class").indexOf(type) <= -1) {
            $(cells[i]).addClass("hide-ele");

           
        }
    }
    for (var i = 0; i < cells.length; i++) {
        if ($(cells[i]).attr("class").indexOf(type) > -1) {
            $(cells[i]).removeClass("hide-ele");
            if(type !== ""){
                
            }
           
        }
    }
}



$(document).ready(function () {



    $('#fmessage').val(" ")
    $(".toggle-style").click(function(){
        $(".style-switcher").toggleClass("open")
    })

    let introString = "Hello, I'm Le Tran Dang Khoa1I'm a Front-end Developer"
    for(let i = 0 ; i< introString.length ; i++){
       
        let c = introString[i];
        if(c === '1'){
            $('#header-intro').append("<br/>");
            continue;
        }
        if(c === ' '){
            c = '&nbsp;';
        }
        $('#header-intro').append("<span class='header__text'>"+c+"</span>")
    }

    let headerBtnString = "More about me"
    for(let i = 0 ; i < headerBtnString.length ; i++){
        let c = headerBtnString[i];
        if(c === ' '){
            c = '&nbsp;';
        }
        $('#header-button').append("<span class='header__text pink-border'>"+c+"</span>")

    }

    let myProjects = null;
    $.ajax({
        'async': false,
        'global': false,
        'url': "script/project.json",
        'dataType': "json",
        'success': function (data) {
            myProjects = data;
        }
    });

    let projectsContainer = $("#project-container");
    const projectNum = myProjects.length;
    for(let i = 0 ; i < projectNum; i++){
        let img = '<img src="'+myProjects[i].src1+'" alt="" class="pic portfolio__picture">'
        let name = '<h3 class="pic__title ">'+myProjects[i].name+'</h3>'
        $(projectsContainer).append('<div class="port-fillter__cell '+ myProjects[i].type +'-project floating-block floating-block-hover" onclick="slideShow('+i+')">'+img+name+'</div>')
    }
   
    let slides = $("#slide");
    for(let i = 0 ; i < projectNum ; i++){
        let srcCode = myProjects[i].srcCode === "" ? "#" : myProjects[i].srcCode;
        let slide = `
        <div class="slide__container">
            <div class="slide__content">
                <div class="slide__header">
                    <h3 class="slide__name pink-text">`+myProjects[i].name+`</h3>
                    <h4 class="slide__category"><span>Category</span> - `+myProjects[i].type+`</h4>
                    <p class="slide__number">`+(i+1) +"/"+projectNum+`</p>
                </div>
                <div class="slide__detail">
                    <div class="slide__brief">
                        <h4 class="slide__brief__header">
                            Project Brief
                        </h4>
                        <p class="paragraph paragraph__justify">
                            `+myProjects[i].brief+`
                        </p>
                    </div>
                    <div class="slide__info">
                        <h4 class="slide__brief__header">
                            Project Info
                        </h4>
                        <p class="paragraph"> <span>Date - </span>`+myProjects[i].date+`</p>
                        <p class="paragraph"> <span>Author - </span>`+myProjects[i].author+`</p>
                        <p class="paragraph"> <span>Tools - </span>`+myProjects[i].tool.join(", ")+`</p>
                        <p class="paragraph"><span>Source Code - </span> <a target="_blank" href="`+ srcCode+ `">Link</a> </p>
                    </div>
                </div>
                <div class="slide__project">
                    <div class="slide__project__picture">
                        <img src="`+myProjects[i].src2+`" alt="">
                        <div class="slide__link">
                            <i class="fas fa-hand-point-right slide__pointer pink-text"></i>
                            <a class="pink-text" href="`+myProjects[i].link+`"
                            target="_blank">See now</a>
                        </div>
                    </div>
                </div>
            </div>
        </div>
       `
       $(slides).append(slide);
      
    }

    document.getElementById("all-btn").click();
    $("#loader").fadeOut(1000);

    $(".navigation__link").click(function () {
        navBtn.click();
    })

   scrollToTop=()=>{
        window.scrollTo(0, 0);
   }
   $(".scrolltop").fadeOut(00);
   $(window).scroll(()=>{
      
       if($(window).scrollTop() > 20){
          
           $(".scrolltop").fadeIn(200);
       }
       else{
           
            $(".scrolltop").fadeOut(200);
       }
   })
})

