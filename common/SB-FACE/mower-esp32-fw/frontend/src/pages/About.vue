<template>
  <q-page class=" q-pa-md">
    <!-- Content Row -->
    <div class="row">
      <div class="p-1 q-mt-md  text-left self-end">
        <div class="text-2">Device Information:</div>
        <div class="faded"> Hardware: {{ identity.hardware }}</div>
        <div class="faded"> Unique Identifier: {{ identity.id }}</div>
        <div class="faded"> IP Address: {{ identity.ip }}</div>
      </div>
    </div>
    <div class="row">
      <div class="p-1 q-mt-md  text-left self-end">
        <div class="text-2">Registered To:</div>
        <div class="faded"> Name: {{ identity.user_name }} </div>
        <div>
          <span class="faded"> Email:</span> <a
            :href="'mailto:'+identity.user_email"
            class="text-primary"
          >{{identity.user_email}}</a>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="p-1 q-mt-md  text-left self-end">
        <div class="text-2">Software Version:</div>
        <div class="faded"> Firmware: {{ identity.fw_version }}</div>
        <div class="faded"> File System: {{ identity.fs_version }}</div>
      </div>
    </div>

  </q-page>
</template>

<script>
import { defineComponent } from 'vue';
import { mapGetters } from 'vuex';

export default defineComponent({
  name: 'PageAbout',
  computed: {
    ...mapGetters({
      identity: 'devices/identity',
    }),
  },
})
</script>
