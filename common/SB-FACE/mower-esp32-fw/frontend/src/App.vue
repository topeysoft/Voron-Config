<template>
  <transition-group
    appear
    enter-active-class="animated zoomIn"
    leave-active-class="animated zoomOut"
  >
    <div
      v-if="loading"
      key="loading"
      class="loader wrap row flex flex-center text-center full-width"
    >
      <div class="loading row mnw-30em">
        <div class="bounceball col-auto q-mr-lg text-right"></div>
        <div class="text col text-left text-3">NOW LOADING {{dots}}</div>
      </div>
    </div>
    <router-view
      v-else
      key="content"
    />
  </transition-group>
</template>
<script>
import { defineComponent } from 'vue';
import { mapGetters, mapActions } from 'vuex';
import wsManager from 'src/services/ws.service.js';

export default defineComponent({
  name: 'App',
  data () {
    return {
      dotsCounts: 2,
      loading: true,
      statusInterval: null,
    }
  },
  computed: {
    ...mapGetters({
      isAuthenticated: 'user/isAuthenticated',
    }),
    dots () {
      return '.'.repeat(this.dotsCounts);
    },
  },
  methods: {
    ...mapActions({
      getStatus: 'devices/getStatus',
      getSettings: 'devices/getSettings',
      getIdentity: 'devices/getIdentity',
      startSSE: 'devices/startSSE',
      createWsConnection: 'devices/createWsConnection',
      getLogs: 'devices/getLogs',
      startRtcmSse: 'devices/startRtcmSse',
      getRegistrationStatus: 'devices/getRegistrationStatus',
    }),
    updateDots () {
      if (this.dotsCounts > 2) {
        return this.dotsCounts = 0;
      }
      this.dotsCounts++;
    },
    startLoadingAnimation () {
      this.loading = true;
      this.interval = setInterval(() => {
        this.updateDots();
      }, 500);
    },
    stopLoadingAnimation () {
      this.loading = false;
      clearInterval(this.interval);
    },
    loadData () {
      let promiseArray;
      let critialPromiseArray;
      if (this.isAuthenticated) {
        promiseArray = [
          // this.getStatus(),
          // this.getIdentity(),
          // this.getSettings(),
          // // this.createWsConnection(),
          // this.startSSE(),
          // this.getLogs(),
          // this.startRtcmSse(),
        ]
        // critialPromiseArray = [
        //   this.getSettings(),
        // ]
      } else {
        critialPromiseArray = [
          this.getRegistrationStatus(),
        ]
      }
      if (promiseArray) {
        Promise.all(promiseArray).then(() => { });
      }
      if (critialPromiseArray) {
        Promise.all(critialPromiseArray).finally(() => {
          this.stopLoadingAnimation();
        });
      } else {
        this.stopLoadingAnimation();
      }

    },
  },
  mounted () {
    this.startLoadingAnimation();
    this.loadData();
    // wsManager.createConnection("test", "ws://" + window.location.host + "/api/ws");
  },
})
</script>
<style lang="scss" scoped>
$width: 2.5rem;
$height: 2.5rem;
$color: $primary;
$color2: $primary;
$bounce_height: -7.5rem;

.wrap {
  width: 100vw;
  height: 100vh;
  position: relative;
}

.text {
  color: $color;
}

.bounceball {
  position: relative;
  height: 37px;
  width: $width;
  &:before {
    position: absolute;
    content: "";
    display: block;
    top: 0;
    width: $width;
    height: $height;
    border-radius: 50%;
    background-color: $color2;
    transform-origin: 50%;
    animation: bounce 500ms alternate infinite ease;
  }
}

@keyframes bounce {
  0% {
    top: 2rem;
    height: 5px;
    border-radius: 60px 60px 20px 20px;
    transform: scaleX(2);
  }
  35% {
    height: $height;
    border-radius: 50%;
    transform: scaleX(1);
  }
  100% {
    top: $bounce_height;
  }
}
</style>