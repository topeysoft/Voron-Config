import { boot } from 'quasar/wrappers'
import TimeAgo from 'src/components/TimeAgo.vue';

export default boot(async ({ app }) => {

    app.component('time-ago', TimeAgo);
})