<template>
  <q-layout view="lHh Lpr lFf">
    <q-page-container>
      <router-view />
    </q-page-container>
  </q-layout>
</template>

<script>
import { defineComponent, ref } from 'vue'
import { mapActions, mapGetters } from 'vuex'



export default defineComponent({
  name: 'MainLayout',

  components:
  {
  },

  data () {
    return {
      leftDrawerOpen: false,

    }
  },
  computed: {
    ...mapGetters({
    }),
  },
  methods: {
    ...mapActions({
    }),
  },
  mounted () {

  }
})
</script>
