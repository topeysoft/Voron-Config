const fs = require('fs');
const fse = require('fs-extra');
const crypto = require('crypto');
const shortId = require('shortid');
const AdmZip = require("adm-zip");

// const srcBasePath = '../.pio/build/';
const srcBasePath = '../firmware/artifacts/';
const destBasePath = '../firmware/build/';
const packageData = require('./package.json');
const manifest = packageData.fw_manifest;
let deviceEnv = process.argv[2] || manifest.device_env;



function getUserInput (onCompleteCallback) {
    const readline = require('readline');
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl.question('Device Environment (defined in platformio.ini as [env:...], current: ' + manifest.device_env + '): ', function (dev) {
        dev = dev || manifest.device_env;
        rl.question('What version is this firmware? (current: ' + manifest.fw_version + '): ', function (fw_version) {
            fw_version = fw_version || manifest.fw_version;
            rl.question('What version is this File System? (current: ' + manifest.fs_version + '): ', function (fs_version) {
                fs_version = fs_version || manifest.fs_version;
                rl.question('Save this info in package.json? (yes): ', function (saveInfo) {
                    saveInfo = (saveInfo || 'yes').toLowerCase();
                    manifest.device_env = dev;
                    manifest.fw_version = fw_version;
                    manifest.fs_version = fs_version;

                    if (saveInfo === 'yes') {
                        manifest.build_date = '';
                        fs.writeFileSync(`./package.json`, JSON.stringify(packageData));
                    }
                    manifest.build_date = new Date().toISOString();
                    if (onCompleteCallback) onCompleteCallback();
                    rl.close();
                });
            });
        });
    });

    rl.on('close', function () {
        console.info('\nAll done!');
        process.exit(0);
    });
}

function beginPackageBuild () {
    getUserInput(buildPackage);
}
function buildPackage () {
    const deviceEnv = manifest.device_env;
    // if (!deviceEnv) {
    //     console.log('Device environment is required');
    //     return;
    // }

    console.log(`Building ${manifest.name} for ${deviceEnv}`);
    manifest.fw_hash = fileMD5(`${srcBasePath}firmware.bin`);
    manifest.fs_hash = fileMD5(`${srcBasePath}spiffs.bin`);
    fs.writeFileSync(`${srcBasePath}manifest.json`, JSON.stringify(manifest));
    const date = new Date();
    const stamp = date.getFullYear().toString().substring(-2) + '' + (date.getMonth() + 1) + '' + date.getDate() + '' + date.getHours() + '' + date.getMinutes() + '' + date.getSeconds();
    const outputDir = `${destBasePath}${deviceEnv}`;
    const output = `${outputDir}/fw_${manifest.fw_version}_${manifest.fs_version}_${stamp}.epkg`;
    fs.mkdirSync(outputDir, { recursive: true });
    createZipFromDir(srcBasePath, output);
    console.log(`Firmware package created successfully!`);
    console.log(`You can find the package file at: \n  ${output} `);

    // console.log(`Manifest: `, manifest);
}

function fileMD5 (filePath) {
    const fileBuffer = fs.readFileSync(filePath);
    const hashSum = crypto.createHash('md5');
    hashSum.update(fileBuffer);
    return hashSum.digest('hex');
}

function createZipFromDir (srcDir, destFile) {
    const zip = new AdmZip();
    zip.addLocalFolder(srcDir);
    zip.writeZip(destFile);
    console.log(`Created ${destFile} successfully`);
}
beginPackageBuild();
