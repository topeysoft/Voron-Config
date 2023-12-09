<template>
  <q-tooltip
    :content-class="{
        'text-white bg-black':$q.dark.isActive,
        'text-black bg-grey-4':!$q.dark.isActive,
    }"
    :hide-delay="hideDelay"
    color=""
  >
    <slot></slot>
  </q-tooltip>
</template>

<script>
export default {
  name: "Tooltip",
  props: {
    hideDelay: {
      type: Number,
      default: 0
    }
  }

}
</script>