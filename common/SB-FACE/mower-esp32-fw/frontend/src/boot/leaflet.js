import { boot } from 'quasar/wrappers'
// import { LMap, LTileLayer, LMarker } from 'vue2-leaflet';
import 'leaflet/dist/leaflet.js';
import 'leaflet/dist/leaflet.css';
import { Icon } from 'leaflet';

export default boot(async ({ app }) => {
    // app.component('l-map', LMap);
    // app.component('l-tile-layer', LTileLayer);
    // app.component('l-marker', LMarker);

    delete Icon.Default.prototype._getIconUrl;
    Icon.Default.mergeOptions({
        iconRetinaUrl: require('leaflet/dist/images/marker-icon-2x.png'),
        iconUrl: require('leaflet/dist/images/marker-icon.png'),
        shadowUrl: require('leaflet/dist/images/marker-shadow.png'),
    });
})