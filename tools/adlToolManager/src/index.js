// index

// Post requests
function SendData(command) {
    var request = new XMLHttpRequest();
    request.open('POST', '/', true);
    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
    request.onload = function() {
        if (request.status >= 200 && request.status < 400) {
            Manager(this.responseText);
        }
    };

    request.send(command);
}    

function SendCommandData() {
    var request = new XMLHttpRequest();
    request.open('POST', '/', true);
    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
    request.onload = function() {
        if (request.status >= 200 && request.status < 400) {
            Manager(this.responseText);
        }
    };
    var command = document.getElementById("command").value;

    request.send(command);
}

// Get request
function GetFile() {
    var request = new XMLHttpRequest();
    request.open('GET', '/', true);

    request.onload = function() {
    if (request.status >= 200 && request.status < 400) {
        document.getElementById("res").innerHTML = this.responseText;
    }
    };
    request.send();
}

// Replacer
function RootReplacer(key, value) {
    if (typeof(value) == "string") { // key == "path"
        value = value.replace(/\\/g, "/"); // Win "\" to "/" 
        value = value.replace(/..\/..\//g, ""); // Root to res file
    }
    if (key  == "name") {  
        value = value.replace(/\.[^/.]+$/g, "");
    }

    return value;
}

// Display functions
function TabManager(ManagerId) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("TabContent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("TabLink");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(ManagerId).style.display = "block";
}

// Classor
function Classor() {
    var options = 
        document.getElementById('ClassFormat').value + "," // settings[0]
        + document.getElementById('ClassRegister').checked + "," // settings[1]
        + document.getElementById('ClassParent').value; // settings[2]
        + document.getElementById('GameGeneric').checked + "," // settings[3]
    
    var cPath = document.getElementById("pathGame").checked?'game/':'engine/';
    console.log(cPath);


    var commands = 'Classor:../../source/' + cPath + document.getElementById('ClassName').value + ':' + options
    console.log(commands);
    
    SendData(commands);
}

//Display
function ClassOptionsController() {
    var cFormat = document.getElementById('ClassFormat');
    if(cFormat.value == 'isCpp'){
        document.getElementById('ClassOptions').hidden = true;
        document.getElementById('ClassRegister').checked = false;
        document.getElementById('GameGeneric').checked = false;
        document.getElementById('ClassParent').value = "";            
    }else{
        document.getElementById('ClassOptions').hidden = false;
        document.getElementById('ClassRegister').checked = true;
        document.getElementById('GameGeneric').checked = true;
    }
}
// EntityManager
function EntityManager(command) {
    if (command == 'EtI') {
        SendData('Entity:../../res/entities/' + ':EtI')/*Change in ModuleManager*/        
    } else if (command == 'GetInfo') {
        SendData('Entity:../../res/entities/' + ':GetInfo');
    } else if (command == 'SetInfo') {
        console.log(table.getData());
        SendData('Entity:../../res/entities/' + ':SetInfo'+ ':' + JSON.stringify(table.getData()));
    }

}

// Data Table
var table;
function CreateTablor(createInfo) {
    table = new Tabulator("#Tablor", {
        data:createInfo.tableData, 
        layout:"fitDataFill",
        tooltips:true,  
        addRowPos:"top",          //when adding a new row, add it to the top of the table
        history:true,             //allow undo and redo actions on the table
        pagination:"local",       //paginate the data
        paginationSize:7,         //allow 7 rows per page of data
        movableColumns:true,      //allow column order to be changed
        resizableRows:true,       //allow row order to be changed
        columns: createInfo.cols,
    });
}

function UpdateTablor(entityInfo) {
    var req = entityInfo.components[0].requires; // For Game side
    var cols = [];

    for (const key in req[0]) {
        if (req[0].hasOwnProperty(key)) {
            cols.push({title:(key.charAt(0).toUpperCase() + key.slice(1)), field:key, width:180, align:"center", editor:true},)
        }
    }

    CreateTablor({tableData: req, cols: cols});
}

