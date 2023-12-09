<template>
  <q-page class=" q-pa-md">
    <!-- Content Row -->
    <q-card>
      <q-card-section class="pb-4">
        <div class="row">
          <div class="col-xl-8 col-md-12 mb-12">
            <q-form>
              <h4 class="m-0">Device Controls</h4>
              <div class="">
                <h5 class="mb-1">GPS Device Controls</h5>
                <q-btn
                  checked-icon="check"
                  color="green"
                  unchecked-icon="clear"
                  label="Reset GPS Device"
                  @click="resetGpsDeviceNow"
                />
              </div>
              <div>
                <h5 class="">ESP32 Device Controls</h5>
                <div class="row q-gutter-md">
                  <div class="col">
                    <q-btn
                      checked-icon="check"
                      color="green"
                      unchecked-icon="clear"
                      label="Reboot Device"
                      @click="rebootEsp32DeviceNow"
                    />
                  </div>
                </div>
              </div>
              <br>
              <!-- <q-btn
                color="primary"
                @click="saveSettingNow"
                :loading="loading"
                :disable="loading"
                class="mnw-15em"
              >Save &amp;
                Reboot
                <template v-slot:loading>
                  <q-spinner-oval class="mr-1"></q-spinner-oval> Saving changes
                </template>
              </q-btn> -->
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
      <q-card class="mxw-40">
        <q-card-section>
          <div class="text-h6">
            <q-spinner-oval
              color="primary"
              size="3rem"
              class="mr-1"
            ></q-spinner-oval>Processing, please wait...
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
                Request processed successfully.
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
                Error processing request.
              </div>
              <p>There was an error while processing your request</p>
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
  name: 'PageControl',
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
    };
  },
  methods: {
    ...mapActions({
      resetGpsDevice: 'devices/resetGpsDevice',
      rebootEsp32Device: 'devices/rebootEsp32Device',
    }),
    resetGpsDeviceNow () {
      this.$q.dialog({
        title: 'Reset GPS Device',
        message: 'Are you sure you want to reset the GPS device?',
        cancel: true,
        persistent: true
      }).onOk(() => {
        // console.log('>>>> OK')
        this.loading = true;
        this.resetGpsDevice().then(() => {
          this.success = true;
        }).catch((err) => {
          this.error = true;
        }).finally(() => {
          this.loading = false;
        });
      }).onOk(() => {
        // console.log('>>>> second OK catcher')
      }).onCancel(() => {
        // console.log('>>>> Cancel')
      }).onDismiss(() => {
        // console.log('I am triggered on both OK and Cancel')
      })
    },
    rebootEsp32DeviceNow () {
      this.$q.dialog({
        title: 'Reboot ESP 32 Device',
        message: 'Are you sure you want to reboot device?',
        cancel: true,
        persistent: true
      }).onOk(() => {
        // console.log('>>>> OK')
        this.loading = true;
        this.rebootEsp32Device().then(() => {
          this.success = true;
        }).catch((err) => {
          this.error = true;
        }).finally(() => {
          this.loading = false;
        });
      }).onOk(() => {
        // console.log('>>>> second OK catcher')
      }).onCancel(() => {
        // console.log('>>>> Cancel')
      }).onDismiss(() => {
        // console.log('I am triggered on both OK and Cancel')
      })
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
  },
  mounted () {
    Object.keys(this.settings).forEach((key) => {
      this.settings[key] = this.savedSettings[key];
    });
    this.settings.useSurveyIn = this.savedSettings.useSurveyIn || false;
  },
})
</script>
