<template>
  <q-page class=" q-pa-md flex flex-center">
    <div class="text-center items-center ">
      <h1 class="m-0 pb-0 text-center">{{appInfo.productName}}</h1>
      <h2 class="m-0 p-0">Log In</h2>
      <div class="flex justify-center">
        <q-form
          ref="setupForm"
          class="mxw-25em w-100"
        >
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
            <q-btn
              color="primary"
              class="mnw-20em"
              @click="login"
              :disable="loading"
              :loading="loading"
            >Log in to the device
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
  name: 'PageLogin',
  data () {
    return {
      loginModel: {
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
    login () {
      this.$refs.setupForm.validate().then((valid) => {
        if (valid) {
          this.loading = true;
          this.$store.dispatch('user/login', this.loginModel).then(() => {
            this.$router.push('/');
          }).finally(() => {
            this.loading = false;
          });
        }
      });
    },
  },
})
</script>
