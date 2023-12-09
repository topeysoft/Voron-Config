const fs = require('fs');
const fse = require('fs-extra');
const shortId = require('shortid');
const srcBasePath = '../.pio/build/';
const destBasePath = '../firmware/artifacts/';
const packageData = require('./package.json');

const manifest = packageData.fw_manifest;
let deviceEnv = process.argv[2] || manifest.device_env;



function copyFilesToDataDir () {
    if (!deviceEnv) {
        console.log('Device environment is required');
        return;
    }
    if (fs.existsSync(srcBasePath + deviceEnv + '/firmware.bin')) {
        console.log('firmware.bin found');
        fse.copy(srcBasePath + deviceEnv + '/firmware.bin', destBasePath + 'firmware.bin', { overwrite: true }, function (err) {
            if (err) {
                console.error(err);
            } else {
                console.log("success!");
            }
        });
    }
    if (fs.existsSync(srcBasePath + deviceEnv + '/spiffs.bin')) {
        console.log('spiffs.bin found');
        fse.copy(srcBasePath + deviceEnv + '/spiffs.bin', destBasePath + 'spiffs.bin', { overwrite: true }, function (err) {
            if (err) {
                console.error(err);
            } else {
                console.log("success!");
            }
        });
    }
}
copyFilesToDataDir();