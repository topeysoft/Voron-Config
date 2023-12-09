<template>
  <span>{{timeago}}</span>
</template>

<script>
import { defineComponent } from 'vue'
import * as timeago from 'timeago.js';

export default defineComponent({
  name: 'TimeAgo',
  props: {
    datetime: {
      required: true,
    },
  },
  computed: {
    timeago () {
      const result = timeago.format(this.datetime);
      return result;
    }
  }
})
</script>
