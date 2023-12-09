import { boot } from 'quasar/wrappers'
import Tooltip from 'src/components/Tooltip.vue';

export default boot(async ({ app }) => {

    app.component('tooltip', Tooltip);
})