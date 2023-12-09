<template>
  <q-page class=" q-pa-md">
    <!-- Content Row 
    <div class="row flex items-stretch">
-->
    <!-- Boot Time Card
      <q-card class="col  items-stretch q-mb-md q-mr-md">
        <q-card-section>
          <div class="row no-gutters align-items-center">
            <div class="col mr-2">
              <div class="text-xs font-weight-bold  text-uppercase mb-1">Boot
                time (UTC)
              </div>
              <div class="row no-gutters align-items-center">
                <div class="col-auto">
                  <div
                    class="h5 mb-0 mr-3 font-weight-bold text-gray-800"
                    id="upSince"
                  >{{bootTimeFormatted}}</div>
                  <small
                    class="faded"
                    v-if="this.status.bootMillis"
                  >
                    <time-ago
                      :refresh="60"
                      :datetime="bootTime"
                      tooltip
                    ></time-ago>
                  </small>
                </div>

              </div>
            </div>
            <div class="col-auto">
              <i class="fas fa-bolt fa-2x text-gray-300"></i>
            </div>
          </div>
        </q-card-section>
      </q-card> -->

    <!-- NTRIP online since Card
      <q-card class="col-auto  items-stretch  q-mb-md q-mr-md ">
        <q-card-section>
          <div class="row no-gutters align-items-center">
            <div class="col mr-2">
              <div class="text-xs font-weight-bold  text-uppercase mb-1">
                NTRIP online since (UTC)</div>
              <div
                class="h5 mb-0 font-weight-bold text-gray-8"
                id="ntripCard"
              >{{status.ntripConnectedTime?status.ntripConnectedTime:'--:--:--'}}
              </div>
            </div>
            <div class="col-auto">
              <i class="fas fa-comments fa-2x text-gray-300"></i>
            </div>
          </div>
        </q-card-section>
      </q-card>  -->

    <!-- NTRIP MB sent Card
      <q-card class="col-auto  items-stretch q-mb-md q-mr-md">
        <q-card-section>
          <div class="row no-gutters align-items-center">
            <div class="col mr-2">
              <div class="text-xs font-weight-bold  text-uppercase mb-1">
                NTRIP MB sent</div>
              <div
                class="h5 mb-0 font-weight-bold text-gray-800"
                id="ntripKBSent"
              >{{status.ntripServerKBSent?$size(status.ntripServerKBSent):'--'}}
              </div>
            </div>
            <div class="col-auto">
              <i class="fas fa-network-wired fa-2x text-gray-300"></i>
            </div>
          </div>
        </q-card-section>
      </q-card> -->

    <!-- SIV Card
      <q-card class="col-auto  q-mb-md items-stretch">
        <q-card-section>
          <div class="row no-gutters align-items-center">
            <div class="col mr-2">
              <div class="text-xs font-weight-bold  text-uppercase mb-1">
                Satellites (in view)</div>
              <div
                class="h5 mb-0 font-weight-bold text-gray-8"
                id="sivCard"
              >{{status.gpsSiv}}
              </div>
            </div>
            <div class="col-auto">
              <i class="fas fa-satellite-dish fa-2x text-gray-300"></i>
            </div>
          </div>
        </q-card-section>
      </q-card>
    </div>  -->
    <!-- Content Row -->

    <div class="row items-stretch  q-col-gutter-md">

      <!-- MAP Area  -->
      <div class="col-12">
        <q-card class="">
          <!-- MAP Body -->
          <q-card-section class="m-0 q-pa-sm">
            <div
              id="map"
              style="height: 280px"
            ></div>

            <!-- <l-map
              style="height: 300px"
              :zoom="zoom"
              :center="center"
            >
              <l-tile-layer
                :url="url"
                :attribution="attribution"
              ></l-tile-layer>
              <l-marker :lat-lng="markerLatLng"></l-marker>
            </l-map> -->
          </q-card-section>
        </q-card>
      </div>

      <div class="col-12">
        <q-card class="card shadow p-1 mnh-10em">
          <h2 class="m-0 p-0">Status</h2>
          {{status}}
        </q-card>
      </div>

      <div class="col-12 col-md-6">
        <q-card class="">
          <!-- MAP Body -->
          <q-card-section>
            <compass :heading="status.yaw"></compass>
          </q-card-section>
        </q-card>
      </div>

      <div class="col-12 col-md-6">
        <q-card class="">
          <!-- Controller -->
          <q-card-section>
            <controller></controller>
          </q-card-section>
        </q-card>
      </div>

      <!-- LOG Area -->
      <div class="col-12 col-md-6">
        <q-card class="  ">
          <q-card-section>
            <q-table
              title="Logs"
              dense
              class="shadow-0"
              :rows="deviceLogs"
              :columns="logColumns"
              row-key="timestamp"
              binary-state-sort
              virtual-scroll
              :virtual-scroll-item-size="48"
              :rows-per-page-options="[0]"
              style="height: 50em"
            >
              <template v-slot:top>
                <h5 class="w-100 mb-2 m-0 row justify-between">
                  <span class="col">Device Logs</span>
                  <span class="col-auto">
                    <q-btn
                      @click="clearLogs"
                      color="primary"
                      label="Clear logs"
                      flat
                      dense
                    />
                  </span>
                </h5>
              </template>
              <template v-slot:body-cell="props">
                <q-td
                  :props="props"
                  :class="{
                    'bg-info text-white': props.row.type === 'info',
                    'bg-negative text-white': props.row.type === 'error',
                    'bg-warning text-white': props.row.type === 'warning',
                    }"
                >
                  {{props.value}}
                </q-td>
              </template>
            </q-table>
            <!-- <table
              class="table datatable"
              id="logTable"
            >
              <thead>
                <tr>
                  <th>Log - Timestamp (UTC)</th>
                  <th>Log - Details</th>
                </tr>
              </thead>
              <tbody>
            </tbody>
            </table> -->

          </q-card-section>
        </q-card>
      </div>

    </div>
  </q-page>
</template>

<script>
import { defineComponent } from 'vue';
import { mapGetters } from 'vuex';
import Compass from 'src/components/Compass.vue';
import Controller from '../components/Controller.vue';

export default defineComponent({
  components: { Compass },
  name: 'PageIndex',
  components:
  {
    Compass,
    Controller
  },
  data () {
    return {
      logColumns: [
        {
          name: 'timestamp',
          field: 'timestamp',
          label: 'Timestamp (UTC)',
          align: 'left',
          sortable: true,
          width: '10%',
        },
        {
          name: 'message',
          field: 'message',
          label: 'Details',
          align: 'left',
          sortable: true,
          width: '90%',
        },
      ],
      url: 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
      attribution:
        '&copy; <a target="_blank" href="http://osm.org/copyright">OpenStreetMap</a> contributors',
      zoom: 15,
      center: [51.505, -0.159],
      markerLatLng: [51.504, -0.159]
    };
  },
  computed: {
    ...mapGetters({
      _status: 'devices/status',
      logs: 'devices/logs',
    }),
    deviceLogs () {
      return this.logs || [];
    },
    status () {
      return this._status || {
        pitch: 0,
        roll: 0,
        yaw: 20,
        lat: 0,
        lon: 0,
        alt: 0,
      };
    },
    bootTime () {
      return new Date(Date.now() - this.status.bootMillis);
    },
    bootTimeFormatted () {
      return this.status.bootMillis ? this.$date.formatDate(this.bootTime, 'ddd, MMM DD, YYYY HH:mm A') : '--:--:--';
    },
  },
  methods: {
    customSort (rows, sortBy, descending) {
      const data = [...rows]

      if (sortBy) {
        data.sort((a, b) => {
          const x = descending ? b : a
          const y = descending ? a : b

          if (sortBy === 'timestamp') {
            // string sort
            return x[sortBy] > y[sortBy] ? 1 : x[sortBy] < y[sortBy] ? -1 : 0
          }
          else {
            // numeric sort
            return parseFloat(x[sortBy]) - parseFloat(y[sortBy])
          }
        })
      }

      return data
    },
    clearLogs () {
      this.$store.commit('devices/setLogs', []);
    },
  },
  mounted () {
    var map = L.map('map').setView([38.608420, -92.122500], 20);
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
      maxZoom: 60,
      attribution: '© OpenStreetMap'
    }).addTo(map);


    let mapboxUrl = 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
    let mapId = 'mapbox/streets-v11';
    let mapboxAttribution = '© OpenStreetMap';
    // var osm = L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    //   maxZoom: 19,
    //   attribution: '© OpenStreetMap'
    // });
    var osm = L.tileLayer(mapboxUrl, { id: 'mapbox/streets-v11', tileSize: 512, zoomOffset: -1, attribution: mapboxAttribution }).addTo(map);



    var marker = L.marker([38.608420, -92.122500]).addTo(map);
    // var circle = L.circle([51.508, -0.11], {
    //   color: 'red',
    //   fillColor: '#f03',
    //   fillOpacity: 0.5,
    //   radius: 500
    // }).addTo(map);
    // var polygon = L.polygon([
    //   [51.509, -0.08],
    //   [51.503, -0.06],
    //   [51.51, -0.047]
    // ]).addTo(map);
    marker.bindPopup("<b>Hello world!</b><br>I am a popup.").openPopup();
    // circle.bindPopup("I am a circle.");
    // polygon.bindPopup("I am a polygon.");

    var satellite = L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw', { id: 'mapbox/satellite-v9', tileSize: 512, zoomOffset: -1, maxZoom: 25, attribution: mapboxAttribution });
    var baseLayers = {
      'Street Names': osm,
      'Satellite': satellite
    };
    var layerControl = L.control.layers(baseLayers).addTo(map);
    // layerControl.addBaseLayer(satellite, 'Satellite');
    // var baseMaps = {
    //   "OpenStreetMap": osm,
    //   "Mapbox Streets": streets
    // };

    // // var overlayMaps = {
    // //   "Cities": cities
    // // };
    // var layerControl = L.control.layers(baseMaps).addTo(map);
    // var satellite = L.tileLayer(mapboxUrl, { id: 'MapID2', tileSize: 512, zoomOffset: -1, attribution: mapboxAttribution });

    // layerControl.addBaseLayer(satellite, "Satellite");

    // var cities = L.layerGroup();

    // var mLittleton = L.marker([39.61, -105.02]).bindPopup('This is Littleton, CO.').addTo(cities);
    // var mDenver = L.marker([39.74, -104.99]).bindPopup('This is Denver, CO.').addTo(cities);
    // var mAurora = L.marker([39.73, -104.8]).bindPopup('This is Aurora, CO.').addTo(cities);
    // var mGolden = L.marker([39.77, -105.23]).bindPopup('This is Golden, CO.').addTo(cities);

    // var mbAttr = 'Map data &copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors, Imagery © <a href="https://www.mapbox.com/">Mapbox</a>';
    // var mbUrl = 'https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token=pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';

    // // var streets = L.tileLayer(mbUrl, { id: 'mapbox/streets-v11', tileSize: 512, zoomOffset: -1, attribution: mbAttr });

    // var osm = L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    //   maxZoom: 19,
    //   attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
    // });

    // var map = L.map('map', {
    //   center: [39.73, -104.99],
    //   zoom: 10,
    //   layers: [osm]
    // });

    // var baseLayers = {
    //   'OpenStreetMap': osm,
    //   // 'Streets': streets
    // };

    // // var overlays = {
    // //   'Cities': cities
    // // };

    // var layerControl = L.control.layers(baseLayers).addTo(map);
    // // var crownHill = L.marker([39.75, -105.09]).bindPopup('This is Crown Hill Park.');
    // // var rubyHill = L.marker([39.68, -105.00]).bindPopup('This is Ruby Hill Park.');

    // // var parks = L.layerGroup([crownHill, rubyHill]);

    // var satellite = L.tileLayer(mbUrl, { id: 'mapbox/satellite-v9', tileSize: 512, zoomOffset: -1, attribution: mbAttr });
    // layerControl.addBaseLayer(satellite, 'Satellite');
    // // layerControl.addOverlay(parks, 'Parks');
  },
})
</script>

