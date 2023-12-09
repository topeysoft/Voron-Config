<template>
  <q-page class=" q-pa-md flex flex-center">
    <div class="text-center items-center ">
      <h1>Initial Setup</h1>
      <p>We need to set up
        your {{appInfo.productName}} with some basic information.
      </p>
      <div class="flex justify-center">
        <q-form
          ref="setupForm"
          class="mxw-25em w-100"
        >
          <h3 class="text-left">Device Information</h3>
          <p>
            <q-input
              outlined
              label="Device Name"
              name="device_name"
              :disable="loading"
              v-model="loginModel.deviceName"
              :rules="[
              val=>val && val.length>0  || 'Please enter a name for your base station' ,
              val=>val && val.length>3 || 'Name must be at least 3 characters' ,
              val=>val && val.length<21 || 'Name must be at most 20 characters' ,
            ]"
            ></q-input>
          </p>
          <h3 class="text-left">Login Information</h3>
          <p>
            <q-input
              outlined
              label="Your Name"
              name="name"
              :disable="loading"
              v-model="loginModel.userName"
              :rules="[
              val=>val && val.length>0  || 'Please enter your name',
              val=>val && val.length>3 || 'Name must be at least 3 characters' ,
              val=>val && val.length<21 || 'Name must be at most 20 characters' ,
            ]"
            ></q-input>
          </p>
          <p>
            <q-input
              outlined
              label="Your Email Address"
              name="email"
              type="email"
              :disable="loading"
              v-model="loginModel.email"
              :rules="[
              val=>val && val.length>0  || 'Please enter a email address' ,
              val=>val.match(emailRegex)  || 'Please enter a valid email address format' ,
            ]"
            ></q-input>
          </p>
          <p>
            <q-input
              outlined
              label="Your Password"
              name="password"
              type="password"
              :disable="loading"
              v-model="loginModel.password"
              :rules="[
              val=>val && val.length>0  || 'Please enter a password for your base station' ,
              val=>val && val.length>7  || 'Password must be at least 8 characters' ,
              val=>val && val.length< 21  || 'Password must be at most 20 characters' ,
            ]"
            ></q-input>
          </p>
          <p>
            <q-input
              outlined
              label="Confirm Password"
              name="password_confirmation"
              type="password"
              v-model="confirmPassword"
              :disable="loading"
              :rules="[
              val=>val && val === loginModel.password ||  'Passwords do not match' ,
            ]"
            ></q-input>
          </p>
          <p>
            <q-btn
              color="primary"
              class="mnw-20em"
              @click="register"
              :disable="loading"
              :loading="loading"
            >Register &amp; Reboot device
              <template v-slot:loading>
                <div>
                  <q-spinner-oval class="mr-1" /> Processing, please wait...
                </div>
              </template>
            </q-btn>
          </p>
        </q-form>
      </div>
    </div>

  </q-page>
</template>

<script>
import { defineComponent } from 'vue';
import { mapGetters } from 'vuex';
import { EMAIL_REGEX } from 'src/constants';

export default defineComponent({
  name: 'PageSetup',
  data () {
    return {
      loginModel: {
        stationName: '',
        userName: '',
        email: '',
        password: '',
      },
      confirmPassword: '',
      emailRegex: EMAIL_REGEX,
      loading: false,
    }
  },
  computed: {
    ...mapGetters({
      identity: 'devices/identity',
      appInfo: 'devices/appInfo',
    }),
  },
  methods: {
    register () {
      this.$refs.setupForm.validate().then((valid) => {
        if (valid) {
          this.loading = true;
          this.$store.dispatch('devices/setup', this.loginModel).then(() => {
            this.$router.push('/');
            window.location.reload();
          }).finally(() => {
            this.loading = false;
          });
        }
      });
    },
  },
})
</script>
