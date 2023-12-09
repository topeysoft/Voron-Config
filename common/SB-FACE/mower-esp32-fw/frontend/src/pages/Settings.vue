<template>
  <q-page class=" q-pa-md">
    <!-- Content Row -->
    <q-card>
      <q-card-section class="pb-4">
        <div class="row">
          <div class="col-xl-8 col-md-12 mb-12">
            <q-form>
              <h4>Device Settings</h4>
              <div class="row">
                <div class="col-4">
                  <!-- <label for="hostName">Hostname</label> -->
                  <q-input
                    type="text"
                    outlined
                    id="hostname"
                    v-model="settings.hostname"
                    label="Hostname"
                    placeholder="Hostname"
                    required
                    hint="Hostname to be used on the network."
                  ></q-input>
                </div>
              </div>
              <div class="">
                <h4 class="mb-1">GPS Antenna Position Method</h4>
                <q-toggle
                  v-model="settings.useSurveyIn"
                  checked-icon="check"
                  color="green"
                  unchecked-icon="clear"
                  label="Use Survey-In"
                />
              </div>
              <div v-if="settings.useSurveyIn">
                <h5 class="">GPS Survey-In Options</h5>
                <div class="row q-gutter-md">
                  <div class="col">
                    <q-input
                      type="number"
                      step="0.01"
                      outlined
                      v-model="gpsSvInSeconds"
                      label="Survey-In Duration In Seconds"
                      placeholder="Survey-In Duration In Seconds"
                      required
                      :rules="[ val => val && val >= 0 || 'You must enter a positive number greater than 0' ]"
                      hint="How long GPS must be in survey-in (in seconds)."
                    ></q-input>
                  </div>
                  <div class="col">
                    <q-input
                      type="number"
                      step="0.01"
                      outlined
                      v-model="settings.gpsSvInAcc"
                      label="Survey-In Accuracy In Meters"
                      placeholder="Survey-In Accuracy In Meters"
                      required
                      :rules="[ val => val && val >= 0 || 'You must enter a positive number greater than 0' ]"
                      hint="How accurate (in meters) GPS must be before exiting survey-in mode ."
                    ></q-input>
                  </div>
                  <div class="col">
                  </div>
                </div>
              </div>
              <div v-else>
                <h5>GPS Antenna Coordinates</h5>
                <div class="row q-gutter-md">
                  <div class="form-group col">
                    <q-input
                      type="number"
                      step="0.001"
                      outlined
                      id="ecefX"
                      v-model="settings.ecefX"
                      label="ECEF X"
                      placeholder="ECEF X"
                      required
                      :rules="[ val => val && val !== 0 || 'You must enter a non-zero number.' ]"
                      hint="ECEF X coordinate of the base station in meters."
                    ></q-input>
                    <small class="form-text text-muted"></small>
                  </div>
                  <div class="form-group col">
                    <q-input
                      outlined
                      type="number"
                      step="0.001"
                      id="ecefY"
                      v-model="settings.ecefY"
                      placeholder="ECEF Y"
                      label="ECEF Y"
                      required
                      :rules="[ val => val && val !== 0 || 'You must enter a non-zero number.' ]"
                      hint="ECEF Y coordinate of the base station in meters."
                    ></q-input>
                  </div>
                  <div class="form-group col">
                    <q-input
                      type="number"
                      step="0.001"
                      outlined
                      id="ecefZ"
                      v-model="settings.ecefZ"
                      placeholder="ECEF Z"
                      label="ECEF Z"
                      required
                      :rules="[ val => val && val !== 0 || 'You must enter a non-zero number.' ]"
                      hint="ECEF Z coordinate of the base station in meters."
                    ></q-input>
                  </div>
                </div>
              </div>
              <h4>NTRIP Settings (e.g rtk2go.com, caster.emlid.com, etc)</h4>
              <div class="row q-gutter-md q-mb-md">
                <div class="form-group col-md-4">
                  <q-input
                    type="text"
                    outlined
                    id="casterHost"
                    name="casterHost"
                    v-model="settings.casterHost"
                    placeholder="Caster Host"
                    label="Caster Host"
                    required
                    hint="URL of the Caster server."
                  ></q-input>
                </div>
                <div class="form-group col-md-4">
                  <q-input
                    type="number"
                    outlined
                    id="casterPort"
                    name="casterPort"
                    v-model="settings.casterPort"
                    placeholder="Caster Port"
                    label="Caster Port"
                    required
                    hint="Port of the Caster server."
                  ></q-input>
                </div>
              </div>
              <div class="row q-gutter-md q-mb-md">
                <div class="form-group col-md-4">
                  <q-input
                    type="text"
                    outlined
                    id="rtk_mntpnt"
                    name="rtk_mntpnt"
                    v-model="settings.rtk_mntpnt"
                    placeholder="Caster mountpoint"
                    label="Caster mountpoint"
                    required
                    hint="Caster Mount point."
                  ></q-input>
                </div>
                <div class="form-group col-md-4">
                  <q-input
                    type="password"
                    outlined
                    id="rtk_mntpnt_pw"
                    name="rtk_mntpnt_pw"
                    v-model="settings.rtk_mntpnt_pw"
                    placeholder="Caster mount password"
                    label="Caster mount password"
                    required
                    hint="Caster mount point password."
                  ></q-input>
                </div>
              </div>
              <div class="row  q-gutter-md q-mb-md">
                <div class="form-group col-md-4">
                  <q-input
                    type="text"
                    outlined
                    id="rtk_user"
                    name="rtk_user"
                    v-model="settings.rtk_user"
                    placeholder="Caster username"
                    label="Caster username"
                    required
                    hint="Caster username."
                  ></q-input>
                </div>
                <div class="form-group col-md-4">
                  <q-input
                    type="password"
                    outlined
                    id="rtk_user_pw"
                    name="rtk_user_pw"
                    v-model="settings.rtk_user_pw"
                    placeholder="Caster user password"
                    label="Caster user password"
                    required
                    hint="Caster user password."
                  ></q-input>
                </div>
              </div>
              <div class="row q-mb-lg">
                <!-- <div class="form-group col-md-4">
                                        <label for="rtk_svr_name">NTRIP server name</label>
                                        <q-input type="text" class="form-control" id="rtk_svr_name" name="rtk_svr_name"
                                            placeholder="NTRIP server name" required>
                                        <small class="form-text text-muted">NTRIP server name.</small>
                                    </div> -->
                <div class="form-group col-md-4">
                  <q-input
                    type="text"
                    outlined
                    id="ntrip_sName"
                    name="ntrip_sName"
                    v-model="settings.ntrip_sName"
                    placeholder="NTRIP server name"
                    label="NTRIP server name"
                    required
                    hint="NTRIP server name."
                  ></q-input>
                </div>
              </div>
              <div class="">
                <q-toggle
                  v-model="settings.connectNtrip"
                  checked-icon="check"
                  color="green"
                  unchecked-icon="clear"
                  label="Connect to NTRIP Server"
                />
              </div>
              <br>
              <q-btn
                :outline="!isDirty"
                color="primary"
                @click="saveSettingNow"
                :loading="loading"
                :disable="loading || !isDirty"
                class="mnw-15em"
              >Save &amp;
                Reboot
                <template v-slot:loading>
                  <q-spinner-oval class="mr-1"></q-spinner-oval> Saving changes
                </template>
              </q-btn>
            </q-form>
          </div>
        </div>
      </q-card-section>
    </q-card>
    <q-dialog
      v-model="loading"
      persistent
      transition-show="scale"
      transition-hide="scale"
    >
      <q-card
        class=""
        style="width: 300px"
      >
        <q-card-section>
          <div class="text-h6">
            <q-spinner-oval
              color="primary"
              size="3rem"
              class="mr-1"
            ></q-spinner-oval>Saving changes
          </div>
        </q-card-section>
      </q-card>
    </q-dialog>
    <q-dialog
      v-model="success"
      persistent
      transition-show="scale"
      transition-hide="scale"
    >
      <q-card class="">
        <q-card-section>
          <div class="row items-center">
            <q-icon
              color="positive"
              size="3rem"
              name="info"
              class="col-auto pr-1"
            ></q-icon>
            <div>
              <div class="text-h6">
                Changes saved successfully.
              </div>
              <!-- <p>You changes has been saved successfully</p> -->
            </div>
          </div>
        </q-card-section>

        <q-card-actions
          align="right"
          class=""
        >
          <q-btn
            flat
            label="Close"
            color="primary"
            v-close-popup
          />
        </q-card-actions>
      </q-card>
    </q-dialog>
    <q-dialog
      v-model="error"
      persistent
      transition-show="scale"
      transition-hide="scale"
    >
      <q-card class="">
        <q-card-section>
          <div class="row items-center">
            <q-icon
              color="negative"
              size="3rem"
              name="info"
              class="col-auto pr-1"
            ></q-icon>
            <div>
              <div class="text-h6">
                Error saving changes
              </div>
              <p>There was an error while saving changes</p>
            </div>
          </div>
        </q-card-section>

        <q-card-actions
          align="right"
          class=""
        >
          <q-btn
            flat
            label="Close"
            color="primary"
            v-close-popup
          />
        </q-card-actions>
      </q-card>
    </q-dialog>
  </q-page>
</template>

<script>
import { defineComponent } from 'vue';
import { mapActions, mapGetters } from 'vuex';

export default defineComponent({
  name: 'PageSettings',
  data () {
    return {
      loading: false,
      error: false,
      success: false,
      settings: {
        hostname: '',
        rtk_svr_name: '',
        rtk_mntpnt: '',
        rtk_mntpnt_pw: '',
        rtk_user: '',
        rtk_user_pw: '',
        casterHost: '',
        casterPort: '2101',
        ecefX: 0,
        ecefY: 0,
        ecefZ: 0,
        useSurveyIn: false,
        connectNtrip: false,
        ntrip_sName: '',
        gpsSvInAcc: 0,
        gpsSvInMsec: 0,
      },
      originalSettings: {},
    };
  },
  methods: {
    ...mapActions({
      saveSettings: 'devices/saveSettings',
    }),
    saveSettingNow () {
      this.loading = true;
      this.saveSettings(this.settings).then(() => {
        this.success = true;
      }).catch((err) => {
        this.error = true;
      }).finally(() => {
        this.loading = false;
      });
    },

  },
  computed: {
    ...mapGetters({
      savedSettings: 'devices/settings',
    }),
    gpsSvInSeconds: {
      get () {
        return this.settings.gpsSvInMsec / 1000;
      },
      set (val) {
        this.settings.gpsSvInMsec = val * 1000;
      }
    },
    isDirty: {
      get () {
        return JSON.stringify(this.settings) !== JSON.stringify(this.originalSettings);
      },
      set (val) {
        // do nothing
      }
    },
  },
  mounted () {
    Object.keys(this.settings).forEach((key) => {
      this.settings[key] = this.savedSettings[key];
    });
    this.settings.useSurveyIn = this.savedSettings.useSurveyIn || false;
    this.originalSettings = JSON.parse(JSON.stringify(this.settings));
  },
})
</script>
