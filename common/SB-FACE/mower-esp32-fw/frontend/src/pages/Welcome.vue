<template>
  <q-page class=" q-pa-md flex flex-center">
    <!-- Content Row -->
    <div class="mxw-40em">
      <h1 class="m-0 pb-2 text-center">{{appInfo.productName}}</h1>
      <h2 class="m-0 pb-2 text-center">{{appInfo.description}}</h2>
      <p>
        This is a simple web application that allows you to manage your RTCM data distribution using NTRIP, WebSocket or nRF24l01 radio transmission.
      </p>
      <p>This application is based on the {{appInfo.productName}} and is designed to be served from the {{appInfo.productName}} itself.</p>
      <p>
        This application is developed by <a href="//elyir.com">Elyir LLC</a>
      </p>
      <div
        v-if="registered"
        class="text-center mb-5 pb-5"
      >
        <p class=" mb-2">
          It appears that you have previouly configured your {{appInfo.productName}}. Click the button below to log in to your {{appInfo.productName}}.
        </p>
        <q-btn
          type="a"
          to="/login"
          color="primary"
        >Log In To Your Base Station</q-btn>
      </div>
      <div
        v-else
        class="text-center mb-5 pb-5"
      >
        <p class=" mb-2">
          It appears that you have not yet configured your {{appInfo.productName}}. Click the button below to set up your {{appInfo.productName}}.
        </p>
        <q-btn
          type="a"
          to="/setup"
          color="primary"
        >Begin Initial Configuration</q-btn>
      </div>
    </div>

  </q-page>
</template>

<script>
import { defineComponent } from 'vue';
import { mapActions, mapGetters } from 'vuex';

export default defineComponent({
  name: 'PageWelcome',
  data () {
    return {
    }
  },
  computed: {
    ...mapGetters({
      registered: 'devices/registered',
      appInfo: 'devices/appInfo',
    }),
  },
  methods: {
    ...mapActions({

    }),
  },
  mounted () {
  },

})
</script>
