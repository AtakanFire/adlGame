var util = require('util');
var dirMan = require('./modules/DirectoryManager');
var resMan = require('./modules/ResourceManager');
var classor = require('./modules/ClassCreator');
var entMan = require('./modules/EntityManager');

module.exports = {
    PostManager: function (arg) {
        var commands = arg.split(":"); 

        if (commands[0] == undefined || commands[1] == undefined) {
            console.log("commands: " + commands);        
            return;    
        }

        if (commands[0] == "GetDirs") { // GetDirs:../../res
            var flist;
            flist = dirMan.walkSync(commands[1]);

            /*console.log("------------------------------");
            console.log("flist: ");
            console.log(flist);*/

            return flist;
        } else if (commands[0] == "Tree") { // Tree:../../res
            //var fJSON = util.inspect(dirMan.TreeBuilder(commands[1]), false, null)
            var fJSON = dirMan.TreeBuilder(commands[1]);

            /*console.log("------------------------------");
            console.log("fJSON.name: ");
            console.log(fJSON.name);*/

            return fJSON;      
        } else if(commands[0] == "ReCore") { // ReCore:../../res
            var fJSON = dirMan.TreeBuilder(commands[1]);
            var CoreJSON = resMan.CoreRefresher(fJSON);
            resMan.WriteJSONFile(commands[1], CoreJSON);

            /*console.log("------------------------------");
            console.log("CoreJSON: ");
            console.log(CoreJSON);*/

            return CoreJSON;      
        } else if (commands[0] == "Classor") { // Classor:../../source/ -> engine/.. || game/.. ->className
            var clses = classor.FileCreator(commands[1], commands[2]);

            return clses;
        } else if (commands[0] == "LineCount") { // LineCount:../../source/
            var flist;
            flist = dirMan.walkSync(commands[1]);

            var counter = [];

            for (let index = 0; index < flist.length; index++) {            
                count = dirMan.CountLinesSync(flist[index]);   
                counter.push({"file" : flist[index], "lineNumber" : count});                             
            }

            return counter;
        } else if (commands[0] == "Entity") {
            var entity;
            if (commands[2] == 'GetInfo') {
                entity = entMan.GetInformer(commands[1]);                
            } else if (commands[2] == 'SetInfo') {
                var fName = commands[1];
                commands.shift();
                commands.shift();
                commands.shift();
                var fData = JSON.parse(commands.join(':'));

                entity = entMan.SetInformer(fName, fData);                
            }

            return entity;
        }  else {
            console.log("Command can't found!");
            return "Commmand can't found!";
        }

    }

};