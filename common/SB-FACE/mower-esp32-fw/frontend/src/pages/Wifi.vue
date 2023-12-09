<template>
  <q-page class=" q-pa-md">
    <!-- Content Row -->
    <q-card>
      <q-card-section>
        <q-tabs
          v-model="tab"
          inline-label
          outside-arrows
          mobile-arrows
          indicator-color="primary"
          active-class="text-primary"
          class=""
        >
          <q-tab
            name="sta"
            icon="wifi"
            label="WiFi Connection Settings"
          />
          <q-tab
            name="ap"
            icon="router"
            label="WiFi Access Point "
          />
        </q-tabs>
        <q-tab-panels
          v-model="tab"
          animated
        >
          <q-tab-panel name="sta">
            <div class="row flex-center">
              <div class="col w-80 mxw-30em">
                <q-form id="settingsForm">
                  <h4>WiFi Connection</h4>
                  <div class="row">
                    <div class="col">
                      <!-- <label for="hostName">Hostname</label> -->
                      <p>
                        <q-input
                          type="text"
                          outlined
                          id="sta_ssid"
                          v-model="wifiSta.wifi_sta_ssid"
                          label="WiFi SSID"
                          placeholder="WiFi SSID"
                          required
                          hint="SSID of the WiFi to connect to."
                        >
                          <q-menu v-model="showWifiList">
                            <q-list
                              class="mnw-25em"
                              separator
                            >
                              <q-item
                                v-for="(wifi, index) in wifiList"
                                :key="'wifi-item-'+index"
                                clickable
                                v-close-popup
                                v-ripple
                              >

                                <q-item-section avatar>
                                  <q-icon :name="wifi.secure?'wifi_password':'wifi'" />
                                </q-item-section>
                                <q-item-section>
                                  <q-item-label>{{wifi.ssid}}</q-item-label>
                                  <q-item-label caption>Signal strength: {{(wifi.rssi+100)+'%'}}</q-item-label>
                                </q-item-section>
                                <q-item-section side>

                                  <q-icon
                                    v-if="wifi.secure"
                                    name="lock"
                                  ></q-icon>
                                </q-item-section>
                              </q-item>
                            </q-list>
                          </q-menu>
                          <template v-slot:append>
                            <q-btn
                              icon="wifi_find"
                              @click.stop="scanDeviceWifi"
                              :loading="scanningWifi"
                            >
                              <tooltip>Scan to select from a list of available wifi networks</tooltip>
                            </q-btn>
                          </template>
                        </q-input>
                      </p>
                      <p>
                        <q-input
                          type="password"
                          outlined
                          id="sta_password"
                          v-model="wifiSta.wifi_sta_pass"
                          label="WiFi Password"
                          placeholder="WiFi Password"
                          required
                          hint=" Leave blank if no password is required."
                        >
                        </q-input>
                      </p>
                      <p class="q-pt-md">
                        <q-btn
                          @click.stop="saveWifiSta"
                          :loading="loading"
                          :disabled="!wifiSta.wifi_sta_ssid || loading"
                          color="primary"
                          label="Update WiFi Credentials And Reboot"
                        ></q-btn>
                      </p>
                    </div>
                  </div>

                </q-form>
              </div>

            </div>
          </q-tab-panel>
          <q-tab-panel name="ap">
            <div class="row items-center flex-center">
              <div class="col w-80 mxw-30em">
                <q-form id="settingsForm">
                  <h4>WiFi Access Point </h4>
                  <div class="row">
                    <div class="col ">
                      <!-- <label for="hostName">Hostname</label> -->
                      <p>
                        <q-input
                          type="text"
                          outlined
                          id="ap_ssid"
                          v-model="wifiAp.wifi_ap_ssid"
                          label="WiFi Access Point SSID"
                          placeholder="WiFi Access Point SSID"
                          required
                          hint="SSID of the WiFi Access Point."
                        >
                        </q-input>
                      </p>
                      <p>
                        <q-input
                          type="password"
                          outlined
                          id="ap_password"
                          v-model="wifiAp.wifi_ap_pass"
                          label="WiFi Access Point Password"
                          placeholder="WiFi Access Point Password"
                          required
                          hint="Leave blank if you want it to be an open network."
                        >
                        </q-input>
                      </p>
                      <p class="
                  q-pt-md">
                        <q-btn
                          @click.stop="saveWifiAp"
                          :loading="loading"
                          :disabled="!wifiAp.wifi_ap_ssid || loading"
                          color="primary"
                          label="Save And Reboot"
                        ></q-btn>
                      </p>
                    </div>
                  </div>
                </q-form>
              </div>

            </div>
          </q-tab-panel>
        </q-tab-panels>
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
      scanningWifi: false,
      showWifiList: false,
      wifiList: [],
      wifiSta: {},
      wifiAp: {},
      tab: 'sta',
      loading: false,
      error: false,
      success: false,
      settings: {
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
        connectNtrip: false,
        ntrip_sName: '',
      },
    };
  },
  methods: {
    ...mapActions({
      getSettings: 'devices/getSettings',
      saveSettings: 'devices/saveSettings',
      scanWifi: 'devices/scanWifi',
    }),
    saveWifiAp () {
      this.loading = true;
      this.saveSettings(this.wifiAp).then(() => {
        this.success = true;
      }).catch((err) => {
        this.error = true;
      }).finally(() => {
        this.loading = false;
      });
    },
    saveWifiSta () {
      this.loading = true;
      this.saveSettings(this.wifiSta).then(() => {
        this.success = true;
      }).catch((err) => {
        this.error = true;
      }).finally(() => {
        this.loading = false;
      });
    },
    scanDeviceWifi () {
      this.scanningWifi = true;
      this.scanWifi().then((result) => {
        this.wifiList = result.filter((wifi, i) => {
          return wifi.ssid.length > 0;
        }).filter((wifi, i, a) => {
          return a.findIndex(b => b.ssid === wifi.ssid) === i;
        });
        this.scanningWifi = false;
        this.showWifiList = true;
      });

    },
    getWifiRssiColor (wifi) {
      return 'default';
      // if (wifi.rssi > -50) {
      //   return 'positive';
      // } else if (wifi.rssi > -70) {
      //   return 'warning';
      // } else {
      //   return 'negative';
      // }
    },

  },
  computed: {
    ...mapGetters({
      savedSettings: 'devices/settings',
    }),
  },
  mounted () {
    this.wifiSta = {
      wifi_sta_ssid: this.savedSettings.wifi_sta_ssid,
      wifi_sta_pass: this.savedSettings.wifi_sta_pass,
    };
    this.wifiAp = {
      wifi_ap_ssid: this.savedSettings.wifi_ap_ssid,
      wifi_ap_pass: this.savedSettings.wifi_ap_pass,
    };
  },
})
</script>
