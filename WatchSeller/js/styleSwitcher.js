
function setActiveStyle(colorName){
   
    $('.alternative-style').attr("disabled", "true");
    $(".alternative-style[title = "+ colorName +"]").removeAttr("disabled");
}
$(".toggle-style").click(function(){
    $(".style-switcher").toggleClass("open")
})