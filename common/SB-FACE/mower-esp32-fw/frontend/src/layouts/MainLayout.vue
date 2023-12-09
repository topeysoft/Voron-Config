<template>
  <q-layout view="lHh Lpr lFf">
    <q-header
      bordered
      elevated
      class="bg-white text-grey-10"
    >
      <q-toolbar>
        <q-btn
          flat
          dense
          round
          icon="menu"
          aria-label="Menu"
          @click="toggleLeftDrawer"
        />

        <q-toolbar-title>
          {{productName}}
        </q-toolbar-title>

        <!-- Nav Item - WiFi -->
        <div class="row q-gutter-lg justify-center items-center">
          <div class="row items-center">
            <q-icon
              v-if="status.chargerConnected"
              size="1.5em"
              :name="'power'"
              :color="'info'"
            ></q-icon>
            <q-icon
              size="1.5em"
              :name="batteryStatusIcon"
              :color="batteryStatusColor"
            >
              <tooltip>Battery level: {{status.battery_level?status.battery_level+'%':'Unknown'}}
                <q-badge
                  v-if="status.chargerConnected"
                  color="positive"
                >Charger Connected</q-badge>
                <!-- <q-badge
                  v-else
                  color="negative"
                >Disconnected</q-badge> -->
              </tooltip>
            </q-icon>
          </div>
          <div class="row items-center">
            <q-icon
              size="1.5em"
              :name="status.wifiConnected?'wifi':'wifi_off'"
              :color="status.wifiConnected?'positive':'negative'"
            >
              <tooltip>WiFi connection status:
                <q-badge
                  v-if="status.wifiConnected"
                  color="positive"
                >Connected</q-badge>
                <q-badge
                  v-else
                  color="negative"
                >Disconnected</q-badge>
              </tooltip>
            </q-icon>
          </div>
          <div class="row items-center">
            <q-icon
              size="1.5em"
              :name="'satellite_alt'"
              :color="status.gpsConnected?'positive':'negative'"
            >

            </q-icon>
            <q-badge
              v-if="status.gpsConnected"
              color="info"
            >{{status.gpsSiv}}</q-badge>
            <tooltip>
              <div>
                GPS status:
                <q-badge
                  v-if="status.gpsConnected"
                  color="positive"
                >Fixed</q-badge>
                <q-badge
                  v-else
                  color="negative"
                >Not Fixed</q-badge>
              </div>
              <div>
                Satellites In View:
                <q-badge
                  v-if="status.gpsConnected"
                  color="info"
                >{{status.gpsSiv}}</q-badge>
              </div>
            </tooltip>
          </div>
          <div class="row items-center">
            <q-icon
              size="1.5em"
              :name="status.ntripConnected?'public':'public_off'"
              :color="status.ntripConnected?'positive':(settings.connectNtrip?'negative':'grey-4')"
            >
            </q-icon>
            <tooltip>
              <span class="row">
                NTRIP Server Connection status:
                <q-badge
                  v-if="status.ntripConnected"
                  color="positive"
                >Active</q-badge>
                <q-badge
                  v-if="!settings.connectNtrip"
                  color="grey-10"
                >Disabled</q-badge>
                <q-badge
                  v-else
                  color="negative"
                >Inactive</q-badge>
              </span>
            </tooltip>
          </div>
          <div class="row items-center">
            <q-icon
              size="1.5em"
              :name="status.wsConnected?'hub':'hub'"
              :color="status.wsConnected?'positive':(settings.connectWs?'negative':'grey-4')"
            >
            </q-icon>
            <tooltip>
              <span class="row">
                RTCM Web Socket Connection status:
                <q-badge
                  v-if="status.wsConnected"
                  color="positive"
                >Active</q-badge>
                <q-badge
                  v-if="!settings.connectWs"
                  color="grey-10"
                >Disabled</q-badge>
                <q-badge
                  v-else
                  color="negative"
                >Inactive</q-badge>
              </span>
            </tooltip>
          </div>

          <div>
            <q-icon
              v-if="sseConnected"
              color="positive"
              size="1.5rem"
              name="link"
            ></q-icon>
            <q-icon
              v-else
              color="negative"
              size="1.5rem"
              name="link_off"
            ></q-icon>
            <tooltip>Device events connection status:
              <q-badge
                v-if="sseConnected"
                color="positive"
              >Connected</q-badge>
              <q-badge
                v-else
                color="negative"
              >Disconnected</q-badge>
            </tooltip>
            <!-- <tooltip>{{sseConnected?'Connected and getting events from device':'Not connected to device'}}</tooltip> -->
          </div>
        </div>
      </q-toolbar>
    </q-header>

    <q-drawer
      v-model="leftDrawerOpen"
      show-if-above
      bordered
      elevated
      class="column"
    >
      <div class="mxh-10em bg-grey-2">
        <!-- <q-item>
          <q-item-section avatar>
            <q-icon name="face" />
          </q-item-section>

          <q-item-section>
            <q-item-label>User Name</q-item-label>
            <q-item-label caption>
              User Email
            </q-item-label>
          </q-item-section>
        </q-item> -->

      </div>
      <q-list>
        <q-item
          clickable
          tag="a"
          :href="item.link"
          v-for="(item, index) in menuItems"
          :key="'menu-item-'+index"
          :active="item.active?item.active():false"
        >
          <q-item-section
            v-if="item.icon"
            avatar
          >
            <q-icon :name="item.icon" />
          </q-item-section>

          <q-item-section>
            <q-item-label>{{ item.title }}</q-item-label>
            <q-item-label caption>
              {{ item.caption }}
            </q-item-label>
          </q-item-section>
        </q-item>
      </q-list>
      <q-separator></q-separator>
      <div class="text-center mt-2">
        <q-btn
          flat
          color="primary"
          class="full-width"
          @click="logout"
          :loading="loggingOut"
        >Sign out
          <template v-slot:loading>
            <q-spinner-oval class="mr-1"></q-spinner-oval>Signing out...
          </template>
        </q-btn>
      </div>
      <q-space></q-space>
      <div class="p-1 q-mt-md  text-center">
        <span class="faded">FW: v{{ identity.fw_version }}</span> --
        <span class="faded"> FS: v{{ identity.fs_version }}</span>
      </div>

    </q-drawer>

    <q-page-container>
      <router-view />
    </q-page-container>
  </q-layout>
</template>

<script>
import { defineComponent, ref } from 'vue'
import { mapActions, mapGetters } from 'vuex'
import pack from '../../package.json'

const { productName, version } = pack;


export default defineComponent({
  name: 'MainLayout',

  components:
  {
  },

  data () {
    return {
      productName: productName,
      version: version,
      leftDrawerOpen: false,
      loggingOut: false,
      menuItems: [
        {
          title: 'Dashboard',
          caption: 'Application overview etc.',
          icon: 'dashboard',
          link: '/#',
          active: () => {
            return this.$route.path === '/'
          }
        },
        {
          title: 'Settings',
          caption: 'Application settings etc.',
          icon: 'settings',
          link: '/#settings',
          active: () => {
            return this.$route.path === '/settings'
          }
        },
        {
          title: 'WiFi Settings',
          caption: 'WiFi settings for Access Point etc.',
          icon: 'wifi',
          link: '/#wifi',
          active: () => {
            return this.$route.path === '/wifi'
          }
        },
        {
          title: 'OTA',
          caption: 'Firmware update etc.',
          icon: 'browser_updated',
          link: '/#ota',
          active: () => {
            return this.$route.path === '/ota'
          }
        },
        {
          title: 'Controls',
          caption: 'Device controls.',
          icon: 'videogame_asset',
          link: '/#control',
          active: () => {
            return this.$route.path === '/control'
          }
        },
        {
          title: 'About',
          caption: 'About this application etc.',
          icon: 'info',
          link: '/#about',
          active: () => {
            return this.$route.path === '/about'
          }
        }

      ]
    }
  },
  computed: {
    ...mapGetters({
      identity: 'devices/identity',
      statusData: 'devices/status',
      settings: 'devices/settings',
      sseConnected: 'devices/sseConnected',
    }),
    status () {
      return this.statusData || {}
    },
    batteryStatusColor () {
      let color = "grey-10"; // default color
      if (this.status.battery_level >= 30) {
        color = "positive";
      } else if (this.status.battery_level < 30 && this.status.battery_level >= 10) {
        color = "warning";
      } else {
        color = "negative";
      }
      return color;
    },
    batteryStatusIcon () {
      let status = "battery_unknown";
      if (this.status.battery_level > 98) {
        status = "battery_full";
      } else if (this.status.battery_level > 75) {
        status = "battery_6_bar ";
      } else if (this.status.battery_level > 60) {
        status = "battery_5_bar";
      } else if (this.status.battery_level > 45) {
        status = "battery_4_bar";
      } else if (this.status.battery_level > 30) {
        status = "battery_3_bar";
      } else if (this.status.battery_level > 15) {
        status = "battery_2_bar";
      } else if (this.status.battery_level > 0) {
        status = "battery_1_bar";
      } else if (this.status.battery_level == 0) {
        status = "battery_0_bar";
      }
      return status;
    },
  },
  methods: {
    ...mapActions({
      getStatus: 'devices/getStatus',
      getSettings: 'devices/getSettings',
    }),
    logout () {
      this.loggingOut = true
      this.$store.dispatch('user/logout').then(() => {
        this.$router.push('/login');
      }).finally(() => {
        this.loggingOut = false
      })
    },
    toggleLeftDrawer () {
      this.leftDrawerOpen = !this.leftDrawerOpen
    },
  },
  mounted () {

  }
})
</script>
