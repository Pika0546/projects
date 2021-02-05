const nCol = 4
const nRow = 4
const nCell = nCol*nRow


var  board = document.getElementById("game")
console.log(board);
function cell(sc){
    this.score = sc;
    this.content = 0;
    this.square = document.createElement("div");
    this.square.setAttribute("class", 'cell');
    this.draw = function(){
      
        this.square.innerHTML = "<p>"+ this.score + "</p>";
        board.appendChild(this.square);
        switch (this.score) {
            case 0:
                this.square.style.backgroundColor = "#ffffff";
                break;
            case 2:
                this.square.style.backgroundColor = "#fcc5df";
                break;
            case 4:
                this.square.style.backgroundColor = "#fc95be";
                break;    
            case 8:
                this.square.style.backgroundColor = "#fa78ac";
                break;
            case 16:
                this.square.style.backgroundColor = "#fa619e";
                break;
            case 32:
                this.square.style.backgroundColor = "#fa4b91";
                break;
            case 64:
                this.square.style.backgroundColor = "#fa3282";
                break;
            case 128:
                this.square.style.backgroundColor = "#ff1f78";
                break;
            case 256:
                this.square.style.backgroundColor = "#fa0a69";
                break;            
            case 512:
                this.square.style.backgroundColor = "#ff1c5c";
                break;
            case 1024:
                this.square.style.backgroundColor = "#ff0d51"
            default:
                this.square.style.backgroundColor = "#ff0000";
                break;
        }
    }
}


var cells = [];
var gameScore = 0;
function init() {
    gameScore = 0;
    document.getElementById("victory").style.display = "none"
    document.getElementById("restart").style.display = "none";
    document.getElementById("game-over").style.display = "none";
    var cellsRemove = document.getElementsByClassName("cell");
    for( var i = cellsRemove.length - 1 ; i >= 0; i--){
        cellsRemove[i].remove();
    }
    for(var i = 0; i < nCell; i++){
        cells[i] = new cell(0);
    }
    createRandomCell();
    createRandomCell();
    
}
function draw() {
    for(var i = 0; i < nCell; i++){
        cells[i].draw();
    }
}
function createRandomCell() {
    var index = Math.floor((Math.random()*nCell));
    if(cells[index].score == 0)
        cells[index].score = (Math.floor((Math.random()*2)) + 1) * 2;
    else
        createRandomCell();
    console.log("1123 ");
}


function arrayCmp(a,b) {
    for(var i = 0 ; i < nRow; i ++)
        if(a[i] !== b[i])
            return false;
    return true;
}

function displayScore() {
    document.getElementById("score").innerHTML = "score: <br> "+gameScore;
}

function moveLeft(){
        var flag = true;
        for(var i = 0 ; i < nRow; i++){
            var oldRow = [cells[i*4].score, cells[i*4 + 1].score, cells[i*4 + 2].score, cells[i*4 +3].score];
            var emptyRow = oldRow.filter(v => v == 0);
            var scoreRow = oldRow.filter(v => v!=0);
            var newRow = scoreRow.concat(emptyRow);
            if(!arrayCmp(newRow,oldRow))
                flag = false;
            for(var j = 0 ; j < nCol; j++){
                cells[i*4+j].score = newRow[j];
            }
       }
    return flag;
}

function moveRight(){
    var flag = true;
       for(var i = 0 ; i < nRow; i++){
            var oldRow = [cells[i*4].score, cells[i*4 + 1].score, cells[i*4 + 2].score, cells[i*4 +3].score];
            var emptyRow = oldRow.filter(v => v == 0);
            var scoreRow = oldRow.filter(v => v!=0);

            var newRow = emptyRow.concat(scoreRow);
            if(!arrayCmp(newRow,oldRow))
            flag = false;
          
            for(var j = nCol -1 ; j >= 0; j--){
                cells[i*4+j].score = newRow[j];
            }
       }
       return flag;
}

function moveUp(){
    var flag = true;
       for(var i = 0 ; i < nRow; i++){
            var oldRow = [cells[i].score, cells[i + 4].score, cells[i + 2*4].score, cells[i + 3*4].score];
            var emptyRow = oldRow.filter(v => v == 0);
            var scoreRow = oldRow.filter(v => v!=0);

            var newRow = scoreRow.concat(emptyRow);
            if(!arrayCmp(newRow,oldRow))
            flag = false;
            for(var j = 0 ; j < nCol; j++){
                cells[i+j*4].score = newRow[j];
            }
       }
       return flag;
}

function moveDown(){
    var flag = true;
       for(var i = 0 ; i < nRow; i++){
            var oldRow = [cells[i].score, cells[i + 4].score, cells[i + 2*4].score, cells[i + 3*4].score];
            var emptyRow = oldRow.filter(v => v == 0);
            var scoreRow = oldRow.filter(v => v!=0);

            var newRow = emptyRow.concat(scoreRow);
            if(!arrayCmp(newRow,oldRow))
            flag = false;
            for(var j = nCol -1 ; j >= 0; j--){
                cells[i+j*4].score = newRow[j];
            }
       }
       return flag;
}

function combineLeft(){
    for(var i = 0 ; i < nCell -1 ; i++){
        if(cells[i].score == cells[i+1].score && (i+1)%4 != 0){
            cells[i].score = cells[i].score + cells[i+1].score;
            cells[i+1].score = 0;
            gameScore += cells[i].score;
        }
    }
}

function combineRight(){
    for(var i = nCell - 1 ; i > 0 ; i--){
        if(cells[i].score == cells[i - 1].score && i%4 != 0 ){
            cells[i].score = cells[i].score + cells[i - 1].score;
            cells[i -1].score = 0;
            gameScore += cells[i].score;
        }
    }
}
function combineUp(){
    for(var i = 0; i < nCell - 4 ; i ++){
        if(cells[i].score == cells[i + 4].score){
            cells[i].score = cells[i].score + cells[i+4].score;
            cells[i+4].score = 0;
            gameScore += cells[i].score;
        }
    }
}

function combineDown(){
    for(var i = nCell - 1; i > 3; i --){
        if(cells[i].score == cells[i - 4].score){
            cells[i].score = cells[i].score + cells[i-4].score;
            cells[i-4].score = 0;
            gameScore += cells[i].score;
        }
    }
}

function floatLeft(){
    var t = moveLeft();
    combineLeft();
    moveLeft();
    if( t == false)
        createRandomCell();
  
}

function floatRight(){
    var t = moveRight();
    combineRight();
    moveRight();
    if( t == false)
        createRandomCell();
   
}

function floatUp(){
    var t = moveUp();
    combineUp();
    moveUp();
    if(t == false)
        createRandomCell();
   
}
function floatDown(){
    var t = moveDown();
    combineDown();
    moveDown();
    if(t == false)
        createRandomCell();
   
    
}

function isFull() {
    for(var i = 0 ; i < nCell  ; i ++){
        if(cells[i].score == 0)
            return false;
    }
    return true;
}

function checkRow(){
    for(var i = 0; i <nCell - 1; i++){
        if(cells[i].score == cells[i+1].score && (i+1)%4 != 0)
            return false;
    }
    return true;
}

function checkColumn() {
    for(var i = 0; i < nCell - 4 ; i ++){
        if(cells[i].score == cells[i + 4].score){
            return false;
        }
    }
    return true;
}
function gameOver(){
    if(checkColumn() && checkRow() && isFull()){
        console.log("lose");
        document.getElementById("restart").style.display = "block";
        document.getElementById("game-over").style.display = "block";
    }
}

function victory() {
    var f = false;
    for(var i = 0 ; i < nCell; i ++){
        if(cells[i].score == 2048){
            f = true;
        }
    }
    if(f){
        document.getElementById("victory").style.display = "block";
        document.getElementById("restart").style.display = "block";
    }
   
    
}


function game() {
    requestAnimationFrame(game);
    displayScore();
    draw();
    gameOver();
    victory();
    
}


init();

game();


