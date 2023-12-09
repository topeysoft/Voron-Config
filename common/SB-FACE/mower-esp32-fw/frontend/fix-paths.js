const fs = require('fs');
const fse = require('fs-extra');
const shortId = require('shortid');
const srcBasePath = './dist/spa/';
const destBasePath = '../data/';
const assetPaths = [
    'fonts',
];
function fixLongFilePaths () {
    fs.readdir(srcBasePath + assetPaths[0], function (err, files) {
        //handling error
        if (err) {
            return console.log('Unable to scan directory: ' + err);
        }
        //listing all files using forEach
        files.forEach(function (file) {
            if (file.length > 20) {
                const filename = file.split('.').slice(0, -1).join('.');
                var ext = file.substring(file.lastIndexOf('.') + 1);
                const newName = shortId() + '.' + ext;
                console.log('Processing ' + file + ' as ' + newName);
                const originalFileName = srcBasePath + assetPaths[0] + '/' + file;
                const outputFileName = srcBasePath + assetPaths[0] + '/' + newName;
                try {
                    fs.renameSync(originalFileName, outputFileName);
                    replaceAllInFile(srcBasePath + 'index.html', file, newName);
                    fs.readdirSync(srcBasePath + 'css').forEach(function (cssFile) {
                        console.log('------ Processing css file ' + cssFile);
                        replaceAllInFile(srcBasePath + 'css/' + cssFile, file, newName);
                    });

                } catch (err) {
                    console.log(err);
                }
            } else {
                console.log('Skipping ' + file);
            }
        });
    });
}
function replaceAllInFile (filename, search, replace) {
    try {
        var data = fs.readFileSync(filename, 'utf8');
        var result = data.replace(new RegExp(search, 'mg'), replace);

        fs.writeFileSync(filename, result, 'utf8');
    } catch (err) {
        console.log(err);
    }
}

function copyFilesToDataDir () {
    // fse.copySync(srcBasePath, destBasePath);
    fs.rmdir(destBasePath, { recursive: true }, (err) => {
        if (err) {
            throw err;
        }
        fse.copy(srcBasePath, destBasePath, { overwrite: true }, function (err) {
            if (err) {
                console.error(err);
            } else {
                console.log("success!");
            }
        });
    });
}

fixLongFilePaths();
copyFilesToDataDir();