<template>
  <q-page class="p-2 ">
    <q-card>
      <q-card-section class="pb-5">
        <h1 class="q-ma-none m-0 p-0">Over-The-Air Software Update</h1>
        <div
          v-if="!uploading"
          class="row mxw-40em mb-3"
        >
          <p>
            This page will allow you to update the firmware of the base station. You can find the latest firmware update package for your device on our software repository <a
              class="text-primary"
              target="_blank"
              href="//elyir.com/software"
            >here</a>.
          </p>
        </div>
        <div class="row">
          <div
            class="col-12  pt-2 p-centered"
            v-if="!loading && !uploading && OTAError !== null"
            key="error"
          >
            <div class="col">
              <span
                style="vertical-align: middle;"
                class="text-2"
              >
                <q-icon
                  name="info"
                  size="1.5em"
                  color="negative"
                  class="q-mr-sm"
                ></q-icon> {{ OTAError }}
              </span>
              <br>
              <br>
              <div class="mt-3">
                <q-btn
                  @click="clear"
                  color="primary"
                  icon="arrow_back"
                >
                  &nbsp; Cancel
                </q-btn>
                <q-btn
                  v-if="packageIsVerified"
                  icon="refresh"
                  class="ml-5"
                  @click="retryOTA"
                >
                  &nbsp; Retry
                </q-btn>
              </div>
            </div>
          </div>
          <div
            class="col-12  p-centered"
            v-else-if="!loading && !uploading && OTASuccess"
            key="success"
          >
            <div class="col">

              <span
                style="vertical-align: middle;"
                class="text-2"
              >
                <q-icon
                  size="3rem"
                  color="positive"
                  name="verified"
                ></q-icon> Device was successfully updated
              </span>
              <div class="q-mt-md  text-left self-end"> Updated version:
                <div class="faded"> Firmware: {{ identity.fw_version }}</div>
                <div class="faded"> File System: {{ identity.fs_version }}</div>
              </div>
              <br>
              <br>
              <div class="">
                <q-btn
                  class="btn btn-primary mt-3"
                  @click="clear"
                  color="primary"
                  icon="arrow_back"
                >
                  Back
                </q-btn>
                <q-btn
                  class="btn btn-primary mt-3"
                  @click="reloadApp"
                  color="primary"
                  icon="refresh"
                >
                  Reload Application
                  <tooltip>Use this to refresh the UI if there are changes to the UI in the update</tooltip>
                </q-btn>
              </div>
            </div>
          </div>
          <div
            class="col-12 p-centered"
            v-else-if="!loading && !uploading"
            key="otainput"
          >
            <div class="col mxw-50em">
              <div class="form-group ">
                <div class="row mxw-40em">
                  <q-label class="text-2 q-mb-sm">Select package file </q-label>
                  <p>
                    Please select the firmware update package you would like to install. You can also drag and drop the file onto the component.
                  </p>
                </div>

                <q-file
                  v-model="file"
                  label="Select File"
                  outlined
                  counter
                  use-chips
                  accept=".zip,.epkg,.efw"
                  class="mxw-30em"
                  ref="file"
                  @update:model-value="readPackage"
                >
                  <template v-slot:prepend>
                    <template v-if="file && !verifying">
                      <q-icon
                        v-if="packageIsVerified"
                        color="positive"
                        name="verified"
                      />
                      <q-icon
                        v-if="!packageIsVerified"
                        color="negative"
                        name="error"
                      />
                    </template>
                    <q-icon name="attach_file" />
                  </template>
                </q-file>
              </div>
              <div v-if="file && !verifying">
                <div
                  v-if="packageIsVerified"
                  class="pt-2"
                >

                  <div class="text-2">Package Manifest</div>
                  <div class="row">
                    <div class="col mb-1">
                      <div class="q-mb-xs">
                        <span class="faded">Package Name: </span>
                        <span>{{manifest.name}}</span>
                      </div>
                      <div class="q-mb-xs">
                        <span class="faded">Package Description: </span>
                        <span>{{manifest.description}}</span>
                      </div>
                      <div class="q-mb-xs">
                        <span class="faded">Package Build Date: </span>
                        <span>{{$formatDate(manifest.build_date, "ddd, DD MMM YYYY hh:mm:ss A")}}</span>
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col mb-1">
                      <div class="text-1">Firmware Information</div>
                      <div class="q-mb-xs">
                        <span class="faded">Version: </span>
                        <span>{{manifest.fw_version}}</span>
                      </div>
                      <div class="q-mb-xs">
                        <span class="faded">MD5 checksum: </span>
                        <span>{{manifest.fw_hash}}</span>
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col mb-1">
                      <div class="text-1">File System Information</div>
                      <div class="q-mb-xs">
                        <span class="faded">Version: </span>
                        <span>{{manifest.fs_version}}</span>
                      </div>
                      <div class="q-mb-xs">
                        <span class="faded"> MD5 checksum: </span>
                        <span>{{manifest.fs_hash}}</span>
                      </div>
                    </div>
                  </div>
                  <q-btn
                    color="primary"
                    class="mt-3"
                    @click="beginUpdate"
                    label="Upload To Device And Reboot"
                    :disabled="!file"
                  />
                </div>
                <div
                  v-else-if="file"
                  class="pt-2"
                >
                  <div class="pb-1">
                    <q-icon
                      color="negative"
                      size="24px"
                      name="error"
                    ></q-icon><span class="text-negative"> Package verification failed!</span> <br>
                    This package is not valid. Please check the package and try again.
                  </div>
                </div>
              </div>
              <div>
              </div>
            </div>
          </div>
        </div>
        <div class="row mnw-45em">
          <div
            class="col-12"
            v-if="!loading && uploading"
          >
            <div class="q-pa-md">
              <div class="row mb-2">
                <div class="text-2">Device Update In Progress</div>
                <p class=" col-12">
                  <q-icon
                    size="1.5rem"
                    color="warning"
                    name="info"
                    class="mr-1"
                  ></q-icon>Please do not refresh or navigate away from this page until this processes are completed. Doing so may cause the device to become unresponsive.
                </p>
              </div>
              <q-list>
                <ota-upload-stage-item
                  v-for="(item, key) in uploadStatusItems"
                  :key="'upload_status_item'+key"
                  :status="item.status"
                  :progress="item.progress"
                  :description="item.description"
                  :title="item.title"
                ></ota-upload-stage-item>
              </q-list>
            </div>

          </div>
        </div>
      </q-card-section>
    </q-card>

  </q-page>
</template>

<script>
import { defineComponent } from 'vue';
import { mapActions, mapGetters } from 'vuex';
import * as zip from "@zip.js/zip.js";
import SparkMD5 from 'spark-md5';
import OtaUploadStageItem from 'src/components/OtaUploadStageItem.vue';

export default defineComponent({
  components: { OtaUploadStageItem },
  name: 'PageOta',

  data () {
    return {
      loading: false,
      uploading: false,
      progress: 0,
      OTAError: null,
      OTASuccess: false,
      file: null,
      type: 'firmware',
      manifest: {},
      fwChecksum: '',
      calcFwChecksum: '',
      calcFsChecksum: '',
      firmware: null,
      fileSystem: null,
      verifying: false,
      currentStage: 'fw_upload',
      uploadStatusItems: {
        'fw_upload': {
          title: 'Updating device firmware',
          description: 'In this stage, the device firmware will be updated to the selected firmware file.',
          status: 'pending',
          progress: 0,
        },
        'restart_after_fw': {
          title: 'Awaiting device reboot',
          description: 'In this stage, we will wait for the device to reboot after the firmware update is complete.',
          status: 'pending',
          progress: 0,
        },
        'fs_upload': {
          title: 'Updating device file system',
          description: 'In this stage, the device file system will be updated to the version in the selected package.',
          status: 'pending',
          progress: 0,
        },
        'restart_after_fs': {
          title: 'Awaiting device reboot',
          description: 'In this stage, we will wait for the device to reboot after the file system update is complete.',
          status: 'pending',
          progress: 0,
        },
        'updating_manifest': {
          title: 'Updating device package manifest',
          description: 'In this stage, the device package manifest will be updated to the version in the selected package.',
          status: 'pending',
          progress: 0,
        }
      }
    };
  },
  computed: {
    ...mapGetters({
      identity: 'devices/identity',
      accessToken: 'user/accessToken',
    }),
    packageIsVerified () {
      return this.file && !this.verifying
        && (this.manifest || {}).fw_hash === this.calcFwChecksum
        && (this.manifest || {}).fs_hash === this.calcFsChecksum;
    },
  },
  methods: {
    ...mapActions({
      getStatus: 'devices/getStatus',
      getIdentity: 'devices/getIdentity',
    }),
    fileMD5 (file) {
      return new Promise((resolve, reject) => {
        const blobSlice = File.prototype.slice
          || File.prototype.mozSlice || File.prototype.webkitSlice;
        const chunkSize = 2097152; // Read in chunks of 2MB
        const chunks = Math.ceil(file.size / chunkSize);
        const spark = new SparkMD5.ArrayBuffer();
        const fileReader = new FileReader();
        let currentChunk = 0;
        let loadNext;

        fileReader.onload = (e) => {
          spark.append(e.target.result); // Append array buffer
          currentChunk += 1;

          if (currentChunk < chunks) {
            loadNext();
          } else {
            const md5 = spark.end();
            resolve(md5);
          }
        };

        fileReader.onerror = (e) => {
          reject(e);
        };

        loadNext = () => {
          const start = currentChunk * chunkSize;
          const end = ((start + chunkSize) >= file.size) ? file.size : start + chunkSize;

          fileReader.readAsArrayBuffer(blobSlice.call(file, start, end));
        };

        loadNext();
      });
    },
    beginUpdate () {
      this.uploading = true;
      switch (this.currentStage) {
        case 'fw_upload':
          this.uploadFirmware().then(() => {
            this.currentStage = 'restart_after_fw';
            this.beginUpdate();
          }).catch(() => {
            this.uploading = false;
          });
          break;
        case 'restart_after_fw':
          this.awaitReboot('fw', 15).then(() => {
            this.currentStage = 'fs_upload';
            this.beginUpdate();
          });
          break;
        case 'fs_upload':
          this.uploadFileSystem().then(() => {
            this.currentStage = 'restart_after_fs';
            this.beginUpdate();
          }).catch(() => {
            this.uploading = false;
          });
          break;
        case 'restart_after_fs':
          this.awaitReboot('fs', 15).then(() => {
            this.currentStage = 'updating_manifest';
            this.beginUpdate();
          });
          break;
        case 'updating_manifest':
          this.updateManifest().then(() => {
            this.currentStage = 'fw_upload';
            this.uploading = false;
            this.OTASuccess = true;
          }).catch(() => {
            this.uploading = false;
            this.OTAError = 'Failed to update manifest';
          })
          break;
        default:
          this.uploading = false;
          this.OTAError = 'Unknown stage';
      }

    },
    awaitReboot (stage = 'fw', secondsToWait = 15) {
      return new Promise((resolve, reject) => {
        this.uploadStatusItems['restart_after_' + stage].status = 'processing';
        this.uploadStatusItems['restart_after_' + stage].progress = 0;
        let interval = setInterval(() => {
          this.uploadStatusItems['restart_after_' + stage].progress += Math.round(((secondsToWait * 100) / (secondsToWait * 1000)) * 100);
          if (this.uploadStatusItems['restart_after_' + stage].progress >= 100) {
            clearInterval(interval);
            this.uploadStatusItems['restart_after_' + stage].progress = 100;
            this.uploadStatusItems['restart_after_' + stage].status = 'done';
            resolve();
          }
        }, secondsToWait * 100);
      });
    },
    updateManifest () {
      this.uploadStatusItems['updating_manifest'].progress = 0;
      return new Promise((resolve, reject) => {
        this.uploadStatusItems['updating_manifest'].status = 'processing';
        this.uploadStatusItems['updating_manifest'].progress = Math.floor(Math.random() * (50 - 28 + 1) + 28);
        var form_data = new FormData();
        for (var key in this.manifest) {
          form_data.append(key, this.manifest[key]);
        }
        this.$axios.put('/api/update', form_data).then(() => {
          this.uploadStatusItems['updating_manifest'].progress += 16;
          setTimeout(() => {
            this.uploadStatusItems['updating_manifest'].progress += 20;
            this.getIdentity().finally(() => {
              this.uploadStatusItems['updating_manifest'].progress = 100;
              setTimeout(() => {
                resolve();
              }, 2000);
            })
          }, 10000);
        }).catch(reject);
      });
    },
    uploadFileSystem () {
      return new Promise((resolve, reject) => {

        this.uploadStatusItems['fs_upload'].status = 'processing';
        const formData = new FormData();
        const request = new XMLHttpRequest();

        request.addEventListener('load', () => {
          // request.response will hold the response from the server
          if (request.status === 200) {
            // this.OTASuccess = true;
            this.uploadStatusItems['fs_upload'].status = 'done'
            resolve();
          } else if (request.status === 401) {
            this.OTAError = `You don't have the permission to perform this operation`;;
            reject();
          } else if (request.status !== 500) {
            this.OTAError = `[HTTP ERROR] ${request.statusText}`;
            reject();
          } else {
            this.OTAError = request.responseText;
            reject();
          }
        });

        request.addEventListener('error', () => {
          // request.response will hold the response from the server
          if (request.status === 401) {
            this.OTAError = `You don't have the permission to perform this operation`;
            reject();
          } else {
            this.OTAError = request.responseText;
            reject();
          }
        });

        // Upload progress
        request.upload.addEventListener('progress', (e) => {
          this.uploadStatusItems['fs_upload'].progress = Math.trunc((e.loaded / e.total) * 100);
        });

        request.withCredentials = true;

        formData.append('MD5', this.calcFsChecksum);
        formData.append("filesystem", this.fileSystem, "filesystem");
        request.open('post', '/api/update');
        request.setRequestHeader('Authorization', 'Bearer ' + this.accessToken);
        request.send(formData);
      });
    },
    uploadFirmware () {
      return new Promise((resolve, reject) => {

        this.uploadStatusItems['fw_upload'].status = 'processing';

        const formData = new FormData();
        const request = new XMLHttpRequest();

        request.addEventListener('load', () => {
          // request.response will hold the response from the server
          if (request.status === 200) {
            // this.OTASuccess = true;
            this.uploadStatusItems['fw_upload'].status = 'done';
            resolve();
          } else if (request.status === 401) {
            this.OTAError = `You don't have the permission to perform this operation`;;
            reject();
          } else if (request.status !== 500) {
            this.OTAError = `[HTTP ERROR] ${request.statusText}`;
            reject();
          } else {
            this.OTAError = request.responseText;
            reject();
          }
        });
        request.addEventListener('error', () => {
          // request.response will hold the response from the server
          if (request.status === 401) {
            this.OTAError = `You don't have the permission to perform this operation`;
            reject();
          } else {
            this.OTAError = request.responseText;
            reject();
          }
        });

        // Upload progress
        request.upload.addEventListener('progress', (e) => {
          this.uploadStatusItems['fw_upload'].progress
            = Math.trunc((e.loaded / e.total) * 100);
        });

        request.withCredentials = true;

        formData.append('MD5', this.calcFwChecksum);
        formData.append("firmware", this.firmware, "firmware");
        request.open('post', '/api/update');
        request.setRequestHeader('Authorization', 'Bearer ' + this.accessToken);
        request.send(formData);
      });
    },

    retryOTA () {
      this.OTAError = null;
      this.OTASuccess = false;
      this.beginUpdate();
    },

    reloadApp () {
      window.location.reload();
    },
    clear () {
      this.OTAError = null;
      this.OTASuccess = false;
      this.uploading = false;
      this.currentStage = 'fw_upload';
      Object.values(this.uploadStatusItems).forEach((item) => {
        item.status = 'pending';
        item.progress = 0;
      });
      this.file = null;
    },
    async readPackage (file) {
      this.verifying = true;
      const zipReader = new zip.ZipReader(new zip.BlobReader(file));

      // - get entries from the zip file
      const entries = await zipReader.getEntries();
      // - get the first entry

      try {
        const manifest = entries.find((entry) => entry.filename === 'manifest.json');
        this.firmware = await entries.find((entry) => entry.filename === 'firmware.bin').getData(new zip.BlobWriter());
        this.fileSystem = await entries.find((entry) => entry.filename === 'spiffs.bin').getData(new zip.BlobWriter());

        const str = await manifest.getData(new zip.TextWriter());
        this.manifest = JSON.parse(str);
        this.calcFwChecksum = await this.fileMD5(this.firmware)
        this.calcFsChecksum = await this.fileMD5(this.fileSystem)
        zipReader.close();
        this.verifying = false;
      } catch (e) {
        this.firmware = null;
        this.fileSystem = null;
        this.calcFwChecksum = null;
        this.calcFsChecksum = null;
        this.file = null;
        console.error(e);
        this.OTAError = 'Invalid package file';
        return;
      }
    }
  },

  mounted () {
  },
})
</script>
