const char* pixels_css = R"=====(
/* Set padding and margins to 0 then change later
Helps with cross browser support */
* {
 padding:0;
 margin:0;
}


li, dd { margin-left:5%; }

fieldset { padding: .5em; }

br.all {
  clear: both;
}

br.clearall {
  clear: both;
}


/* remove margin (added above) on nested ul */
ul ul { margin: 0;}
ul ul ul { margin: 0;}


/* Set selected button color */
.sequence-selected {
    background: #AAAAAA;
}

.seq-select-div {
    display: inline-block;
}

.seq-select-btn {
    border: none;
    padding: 15px;
    text-align: center;
    font-size: 14pt;
    margin: 10px;
    cursor: pointer;
    width:  150px;
    height: 75px;
}

#sequences-list {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
}

.li-seq-select {
    float: left;
    padding: 0;
    margin: 0;
}


#divapplybuttons {
    background-color: #6666ff;
}

#applybutton {
    background-color: #ffffff;
    border: none;
    padding: 15px;
    text-align: center;
    font-size: 16pt;
    margin: 10px;
    cursor: pointer;
    width:  150px;
    height: 75px;
}


#reversebutton {
    border: none;
    padding: 15px;
    text-align: center;
    font-size: 16pt;
    margin: 10px;
    cursor: pointer;
    width:  110px;
    height: 75px;
    border-radius: 45%;
}

.speed-slider {
  -webkit-appearance: none;  /* Override default CSS styles */
  appearance: none;
  width: 100%; /* Full-width */
  height: 15px; /* Specified height */
  border-radius: 5px;
  background: #d3d3d3; /* Grey background */
  outline: none; /* Remove outline */
  opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */
  -webkit-transition: .2s; /* 0.2 seconds transition on hover */
  transition: opacity .2s;
}

.speed-slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  border-radius: 50%; 
  background: #aa0449;
  cursor: pointer;
}

.speed-slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  border-radius: 50%;
  background: #aa0449;
  cursor: pointer;
}

.speed-slider:hover {
  opacity: 1; /* Fully shown on mouse-over */
}

    
.colbutton {
    border: solid;
    width: 100px;
    height: 75px;
    text-align: center;
    padding: 20px;
    border-color: black;
}

.colwhite {
    background: #ffffff;
}

.colgrey {
    background: #7f7f7f;
}

.colred {
    background: #ff0000;
}

.colpink {
    background: #ffc0cb;
}

.colgreen {
    background: #008000;
}

.collightgreen {
    background: #90ee90;
}

.colblue {
    background: #0000ff;
}

.colaqua {
    background: #00ffff;
}

.colpurple {
    background: #800080;
}

.colorange {
    background: #ffa500;
}

.colblack {
    background: #000000;
    color: #ffffff;
}
    
/* color choice buttons */

#ulcolselect {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
}

.licolselect {
    float: left;
    padding: 0;
    margin: 0;
}


/* Selected colours */

#ulcolchosen {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
}

.licolchosen {
    float: left;
    padding: 0;
    margin: 0;
}


.buttoncolchosen {
    border-style: solid;
    padding: 20px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 4px 2px;
    border-radius: 50%;
}

.reverse-selected {
    background: #AAAAAA;
}

.reverse-not-selected {
    background-color: #ffffff;
}

)=====";
