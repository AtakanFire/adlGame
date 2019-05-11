const fs = require('fs');
const path = require('path');


GetInformer = function (fileName) { 
    var informer = JSON.parse(fs.readFileSync(fileName + "informer.json", 'utf8'));
    return informer;
}

SetInformer = function (fileName, fileData) { 
    var informer = JSON.parse(fs.readFileSync(fileName + "informer.json", 'utf8'));
    console.log(fileData);
    
    informer.components[0].requires = fileData;
    fs.writeFileSync(fileName + "informer.json", JSON.stringify(informer, null, 2));

    return informer;
}

CreateInformer = function (fileName) { // For All Game Entities

    var gameEntites = ["Constructions", "Humans", "Resources"]

    filePath = fileName; // "../../res/entities/"
  
    var informer = JSON.parse(fs.readFileSync(filePath + "informer.json", 'utf8'));
    
    console.log(JSON.stringify(informer.components, null, 2));

    console.log(JSON.stringify(informer.components[0].requires, null, 2));

    var files = walkSync(fileName);
    console.log(files);

    var folder = path.basename(path.dirname(files[0]));
    console.log("__" + folder + "__")
    for (let i = 0; i < files.length; i++) {
        const file = files[i];
        if (path.basename(path.dirname(file))!=folder) {
            folder =  path.basename(path.dirname(file));
            console.log("__" + folder + "__")
        }

        if (folder != gameEntites[0] && folder != gameEntites[1] && folder != gameEntites[2]) {
            continue;
        }

        console.log(path.basename(file, ".json"));
        if (!Array.isArray(informer.components[0].requires[folder])) {
            informer.components[0].requires[folder] = [];
        }

        informer.components[0].requires[folder].push({Name: path.basename(file, ".json"), Type: [""], Value: [0]});    
    }

    console.log("-----------------------");
    console.log(JSON.stringify(informer, null, 2));
    

    fs.writeFileSync(filePath + "informer.json", JSON.stringify(informer, null, 2));

    return informer;
}

function walkSync(dir, filelist = []) {
    fs.readdirSync(dir).forEach(file => {
        const dirFile = path.join(dir, file);
        try {
            filelist = walkSync(dirFile, filelist);
        }
        catch (err) {
            if (err.code === 'ENOTDIR' || err.code === 'EBUSY') filelist = [...filelist, dirFile];
            else throw err;
        }
    });
    return filelist;
}

module.exports = {
    CreateInformer: CreateInformer,
    GetInformer: GetInformer,
    SetInformer: SetInformer
};



/* Base Informer Json
{
    "type": "Informer",
    "components": 
    [
        {
            "type": "Informer",
            "requires": {
                
            }

        }
    ]
}
*/