function isLeap(y)
{
    if((y%4 == 0 && y%100 != 0)|| y%400==0)
        return true;
    return false;
}
var months = [31,28,31,30,31,30,31,31,30,31,30,31];
var monthsName = [ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
var now = new Date();
var today = now.getDate();
var today_month = now.getMonth()+1;
var today_year = now.getFullYear();
var today_day = now.getDay() + 1;
var display_month = today_month-1;
var display_year = today_year;

//Hàm này trình bày ra tháng m và năm y
function displayMonth(m, y){
    if(isLeap(y))
        months[1] = 29;
    else
        months[1] = 28;
    var d = new Date();
    d.setFullYear(y,m,1);
    var dow = d.getDay(); //1
    var last_month = (m-1) >= 0 ? m-1:11;
    var begin = months[last_month] - (dow - 1);
    var list = document.getElementsByClassName("date");
    var dem = begin - 1;
    var present = false;
    document.getElementById("month").innerHTML= monthsName[m] + " " + y;
    for(var i = 0; i < 42; i++)
    {
        dem = dem + 1;
        if(dem > months[last_month] && present == false)
        {
            dem = 1;
            present = true;
        }
        else if(dem > months[m] && present == true)
        {
            dem = 1;
            present = false;
        }
        if(dem === today && m+1 === today_month && today_year===y)
        {
           list[i].style.color = "red";
        }
        else
        {
            list[i].style.color = "black";
        }
        if(!present)
        {
            list[i].style.color = "#898989";
        }
        list[i].innerHTML = dem;
    }
}

function decreaseMonth()
{
    if(display_month > 0)
        display_month--;
    else
    {
        display_month =11;
        display_year--;
    }
    displayMonth(display_month,display_year);
}
function increaseMonth() {
    if(display_month < 11)
        display_month++;
    else
    {
        display_month = 0;
        display_year++;
    }
    displayMonth(display_month,display_year);
}

function backToPresent() {
    display_month = today_month-1;
    display_year = today_year;
    displayMonth(display_month,display_year);
}

displayMonth(display_month,display_year);