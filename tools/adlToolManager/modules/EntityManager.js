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


module.exports = {
    GetInformer: GetInformer,
    SetInformer: SetInformer
};
