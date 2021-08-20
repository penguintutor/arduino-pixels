const char* index_html = R"=====(

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <title>Arduino Pixels</title>
        <link href="pixels.css" rel="stylesheet" type="text/css" />
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js" type="text/javascript"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/jquery-ui.min.js"></script>
        <script src="pixels.js" type="text/javascript"></script>
        </head>

    <body>
        <div id="divapplybuttons"><button type="button" id="applybutton" onclick="apply()">Apply</button><button type="button" id="reversebutton" class="reverse-not-selected" onclick="reverse_toggle()">Reverse</button></div>
        <div id="sequences"><h2>Sequences</h2>
          <div id="sequences-list"></div>
        </div>
        <div id="options">
            <div id="speedoption">
                <h2>Speed</h2>
                <input type="range" min="0" max="1000" value="100" class="speed-slider" id="speed" onchange="show_speed()"/>
                <p>Delay <span id="speed-val">1000</span> ms</p>
            </div>
        </div>
        <div id="colors">
            <h2>Colors</h2>
            <div id="divcolors">
                <ul id="ulcolchosen">
                    <li class="licolchosen"><button id="defaultcolchosen" class="buttoncolchosen" style="background: #ffffff">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</button></li>
                </ul>
                <br class="clearall" />
                </div>
            <div id="selectcolors">
                <h3>Add Colors</h3>
                <ul id="ulcolselect">
                    <li class="licolselect"><button name="ffffff" class="colbutton colwhite">White</button></li>
                    <li class="licolselect"><button name="ff0000" class="colbutton colred">Red</button></li>
                    <li class="licolselect"><button name="ffc0cb" class="colbutton colpink">Pink</button></li>
                    <li class="licolselect"><button name="008000" class="colbutton colgreen">Green</button></li>
                    <li class="licolselect"><button name="4bbf5a" class="colbutton collightgreen">Light Green</button></li>
                    <li class="licolselect"><button name="0000ff" class="colbutton colblue">Blue</button></li>
                    <li class="licolselect"><button name="00ffff" class="colbutton colaqua">Aqua</button></li>
                    <li class="licolselect"><button name="800080" class="colbutton colpurple">Purple</button></li>
                    <li class="licolselect"><button name="ffa500" class="colbutton colorange">Orange</button></li>
                    <li class="licolselect"><button name="000000" class="colbutton colblack">Black</button></li>
                </ul>
            </div>
            <br class="clearall" />
        </div>
        <div id="divstatus">
            <h2>LED Status:</h2>
            <div id="status">status</div>
        </div>
    </body>
</html>

)=====";
