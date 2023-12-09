<template>
  <q-item>
    <q-item-section avatar>
      <q-icon
        v-if="status === 'done'"
        color="positive"
        name="task_alt"
      />
      <q-spinner-ios
        v-else-if="status === 'processing'"
        color="primary"
        size="1.5em"
      />
      <!-- <q-icon
        v-else-if="
        status==='processing'"
        color="primary"
        name="east"
      /> -->
      <q-icon
        v-else
        color="grey-4"
        name="radio_button_unchecked"
      />
    </q-item-section>
    <q-item-section>
      <q-item-label>
        <div
          class="text-1 "
          :class="{
            'text-primary': status === 'processing',
            }"
        > {{ title }}</div>
      </q-item-label>
      <q-item-label
        caption
        lines="2"
      >{{ description }}
      </q-item-label>
      <q-item-label>
        <q-linear-progress
          :value="progress/100"
          class="q-mt-md"
        />
        <div class="text-right">{{progress}}%</div>
      </q-item-label>
    </q-item-section>
  </q-item>
</template>

<script>
export default {
  name: 'OTAUploadStageItem',
  props: ['status', 'progress', 'title', 'description'],
  data () {
    return {
      loading: true,
      statusInterval: null,
    }
  },

}
</script>

<style>
</style>