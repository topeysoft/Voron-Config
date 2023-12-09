(()=>{"use strict";var e={4793:(e,t,n)=>{n(5363),n(71);var o=n(8880),s=n(9592),r=n(3673),i=n(2323);const a=e=>((0,r.dD)("data-v-71ea964c"),e=e(),(0,r.Cn)(),e),c={key:"loading",class:"loader wrap row flex flex-center text-center full-width"},d={class:"loading row mnw-30em"},l=a((()=>(0,r._)("div",{class:"bounceball col-auto q-mr-lg text-right"},null,-1))),u={class:"text col text-left text-3"};function h(e,t,n,s,a,h){const p=(0,r.up)("router-view");return(0,r.wg)(),(0,r.j4)(o.W3,{appear:"","enter-active-class":"animated zoomIn","leave-active-class":"animated zoomOut"},{default:(0,r.w5)((()=>[e.loading?((0,r.wg)(),(0,r.iD)("div",c,[(0,r._)("div",d,[l,(0,r._)("div",u,"NOW LOADING "+(0,i.zw)(e.dots),1)])])):((0,r.wg)(),(0,r.j4)(p,{key:"content"}))])),_:1})}n(9544);var p=n(741);n(3845);const f=(0,r.aZ)({name:"App",data(){return{dotsCounts:2,loading:!0,statusInterval:null}},computed:{...(0,p.Se)({isAuthenticated:"user/isAuthenticated"}),dots(){return".".repeat(this.dotsCounts)}},methods:{...(0,p.nv)({getStatus:"devices/getStatus",getSettings:"devices/getSettings",getIdentity:"devices/getIdentity",startSSE:"devices/startSSE",createWsConnection:"devices/createWsConnection",getLogs:"devices/getLogs",startRtcmSse:"devices/startRtcmSse",getRegistrationStatus:"devices/getRegistrationStatus"}),updateDots(){if(this.dotsCounts>2)return this.dotsCounts=0;this.dotsCounts++},startLoadingAnimation(){this.loading=!0,this.interval=setInterval((()=>{this.updateDots()}),500)},stopLoadingAnimation(){this.loading=!1,clearInterval(this.interval)},loadData(){let e,t;this.isAuthenticated?e=[]:t=[this.getRegistrationStatus()],e&&Promise.all(e).then((()=>{})),t?Promise.all(t).finally((()=>{this.stopLoadingAnimation()})):this.stopLoadingAnimation()}},mounted(){this.startLoadingAnimation(),this.loadData()}});var g=n(4260);const m=(0,g.Z)(f,[["render",h],["__scopeId","data-v-71ea964c"]]),v=m;var y=n(2401),b=n(3340),w=n(9582);const k=[{path:"/",component:()=>Promise.all([n.e(736),n.e(378)]).then(n.bind(n,9378)),meta:{guestOnly:!0},children:[{name:"welcome",path:"",component:()=>Promise.all([n.e(736),n.e(989)]).then(n.bind(n,2989))},{name:"login",path:"/login",component:()=>Promise.all([n.e(736),n.e(672)]).then(n.bind(n,672))},{name:"setup",path:"/setup",component:()=>Promise.all([n.e(736),n.e(554)]).then(n.bind(n,7554))},{name:"register",path:"/register",component:()=>Promise.all([n.e(736),n.e(554)]).then(n.bind(n,7554))}]},{path:"/",component:()=>Promise.all([n.e(736),n.e(360)]).then(n.bind(n,5360)),meta:{requiresAuth:!0},children:[{name:"dashboard",path:"",component:()=>Promise.all([n.e(736),n.e(496)]).then(n.bind(n,4708))},{name:"settings",path:"/settings",component:()=>Promise.all([n.e(736),n.e(132)]).then(n.bind(n,132))},{name:"wifi",path:"/wifi",component:()=>Promise.all([n.e(736),n.e(232)]).then(n.bind(n,8672))},{name:"ota",path:"/ota",component:()=>Promise.all([n.e(736),n.e(593)]).then(n.bind(n,6593))},{name:"control",path:"/control",component:()=>Promise.all([n.e(736),n.e(145)]).then(n.bind(n,1145))},{name:"about",path:"/about",component:()=>Promise.all([n.e(736),n.e(411)]).then(n.bind(n,8411))}]},{path:"/:catchAll(.*)*",component:()=>n.e(193).then(n.bind(n,2193))}],S=k,_=(0,y["default"])(),C=()=>_.getters["user/isLoggedIn"],A=(e,t,n)=>{n({name:"login",params:{nextUrl:e.fullPath}})},P=(e,t,n)=>{n({name:"dashboard"})},E=(0,b.BC)((function(){const e=w.r5,t=(0,w.p7)({scrollBehavior:()=>({left:0,top:0}),routes:S,history:e("")});return t.beforeEach(((e,t,n)=>{e.matched.some((e=>e.meta.requiresAuth))?C()?n():A(e,t,n):e.matched.some((e=>e.meta.guestOnly))&&(C()?P(e,t,n):n())})),t}));async function T(e,t){const o="function"===typeof y["default"]?await(0,y["default"])({}):y["default"],{storeKey:r}=await Promise.resolve().then(n.bind(n,2401)),i="function"===typeof E?await E({store:o}):E;o.$router=i;const a=e(v);return a.use(s.Z,t),{app:a,store:o,storeKey:r,router:i}}var D=n(5151);const x={config:{},plugins:{Dialog:D.Z}},I="";async function L({app:e,router:t,store:n,storeKey:o},s){let r=!1;const i=e=>{try{return t.resolve(e).href}catch(n){}return Object(e)===e?null:e},a=e=>{if(r=!0,"string"===typeof e&&/^https?:\/\//.test(e))return void(window.location.href=e);const t=i(e);null!==t&&(window.location.href=t,window.location.reload())},c=window.location.href.replace(window.location.origin,"");for(let l=0;!1===r&&l<s.length;l++)try{await s[l]({app:e,router:t,store:n,ssrContext:null,redirect:a,urlPath:c,publicPath:I})}catch(d){return d&&d.url?void a(d.url):void console.error("[Quasar] boot error:",d)}!0!==r&&(e.use(t),e.use(n,o),e.mount("#q-app"))}T(o.ri,x).then((e=>Promise.all([Promise.resolve().then(n.bind(n,4112)),Promise.resolve().then(n.bind(n,5474)),Promise.resolve().then(n.bind(n,525)),Promise.resolve().then(n.bind(n,5304)),Promise.resolve().then(n.bind(n,7175)),Promise.resolve().then(n.bind(n,9779)),Promise.resolve().then(n.bind(n,5551)),Promise.resolve().then(n.bind(n,2490))]).then((t=>{const n=t.map((e=>e.default)).filter((e=>"function"===typeof e));L(e,n)}))))},5474:(e,t,n)=>{n.r(t),n.d(t,{api:()=>c,default:()=>d});var o=n(3340),s=n(52),r=n.n(s),i=n(2401);const a=(0,i["default"])(),c=r().create({baseURL:"https://api.example.com"});r().defaults.timeout=5e4,r().interceptors.request.use((function(e){let t=a.getters["user/accessToken"];return t&&!e.bypassAuthIntercept&&(e.headers.Authorization=`Bearer ${t}`),{...e}})),r().interceptors.response.use((function(e){return e}),(function(e,t){const n=((e||{}).response||{}).status;if(401!==n||e.config.bypassUnauthorizeRedirect)return Promise.reject(e);a.dispatch("user/logout",{},{root:!0}),window.location.reload()}));const d=(0,o.xr)((({app:e})=>{e.config.globalProperties.$axios=r(),e.config.globalProperties.$api=c}))},5304:(e,t,n)=>{n.r(t),n.d(t,{default:()=>s});var o=n(1082);const s=({app:e})=>{e.config.globalProperties.$date=o.ZP,e.config.globalProperties.$formatDate=o.ZP.formatDate}},2490:(e,t,n)=>{n.r(t),n.d(t,{database:()=>c});var o=n(5720),s=n(9040),r=n(2401);const i={apiKey:"AIzaSyCxHy8Cw05QPkRPFmT_DlpMkk952yWAbsQ",authDomain:"elyir-d4ede.firebaseapp.com",databaseURL:"https://elyir-d4ede.firebaseio.com",projectId:"elyir-d4ede",storageBucket:"elyir-d4ede.appspot.com",messagingSenderId:"1025994341095",appId:"1:1025994341095:web:f457fe11b610a735"},a=(0,o.ZF)(i);(0,r["default"])().dispatch("user/onUserStateChanged",{},{root:!0});const c=(0,s.N8)(a)},4112:(e,t,n)=>{n.r(t),n.d(t,{default:()=>a});var o=n(3340),s=n(5948);const r={failed:"Action failed",success:"Action was successful"},i={"en-US":r},a=(0,o.xr)((({app:e})=>{const t=(0,s.o)({locale:"en-US",messages:i});e.use(t)}))},5551:(e,t,n)=>{n.r(t),n.d(t,{default:()=>r});var o=n(3340),s=(n(1712),n(385));const r=(0,o.xr)((async({app:e})=>{delete s.Icon.Default.prototype._getIconUrl,s.Icon.Default.mergeOptions({iconRetinaUrl:n(8927),iconUrl:n(2406),shadowUrl:n(5219)})}))},7175:(e,t,n)=>{n.r(t),n.d(t,{default:()=>r});var o=n(2130);const{humanStorageSize:s}=o.ZP,r=({app:e})=>{e.config.globalProperties.$size=s}},525:(e,t,n)=>{n.r(t),n.d(t,{default:()=>h});var o=n(3340),s=n(3673),r=n(2323);function i(e,t,n,o,i,a){return(0,s.wg)(),(0,s.iD)("span",null,(0,r.zw)(e.timeago),1)}var a=n(4700);const c=(0,s.aZ)({name:"TimeAgo",props:{datetime:{required:!0}},computed:{timeago(){const e=a.WU(this.datetime);return e}}});var d=n(4260);const l=(0,d.Z)(c,[["render",i]]),u=l,h=(0,o.xr)((async({app:e})=>{e.component("time-ago",u)}))},9779:(e,t,n)=>{n.r(t),n.d(t,{default:()=>p});var o=n(3340),s=n(3673);function r(e,t,n,o,r,i){const a=(0,s.up)("q-tooltip");return(0,s.wg)(),(0,s.j4)(a,{"content-class":{"text-white bg-black":e.$q.dark.isActive,"text-black bg-grey-4":!e.$q.dark.isActive},"hide-delay":n.hideDelay,color:""},{default:(0,s.w5)((()=>[(0,s.WI)(e.$slots,"default")])),_:3},8,["content-class","hide-delay"])}const i={name:"Tooltip",props:{hideDelay:{type:Number,default:0}}};var a=n(4260),c=n(8870),d=n(7518),l=n.n(d);const u=(0,a.Z)(i,[["render",r]]),h=u;l()(i,"components",{QTooltip:c.Z});const p=(0,o.xr)((async({app:e})=>{e.component("tooltip",h)}))},3845:(e,t,n)=>{n.d(t,{Z:()=>a});n(6701),n(8603);function o(e){let t=e||"";try{t=JSON.parse(t),t.payload=o(t.payload)}catch(n){}return t}class s{constructor(){this.onInit=()=>{},this.onConnect=e=>{},this.onBeforeAuth=()=>{},this.onAuthSuccess=e=>{},this.onAuthFailure=e=>{},this.onDisconnect=e=>{},this._onMessage=e=>{},this.onParseError=(e,t)=>{},this.onBeforeReconnectAttempt=()=>{},this.onBeforeReconnect=()=>{},this.onBeforeAuthRetry=()=>{},this.onBeforeDestroy=()=>{},this.onError=e=>{},this.onDestroy=()=>{},this.tokenFactory=()=>{},this.keepAlive=!0,this._messageTypeHandlers={}}init(e,t=!0){return this.wsUrl=e,this.keepAlive=t,this._delay=5,console.log("WebSocket: Initialized!"),this.onInit&&this.onInit(this),this.connect(),this._keepConnectionAlive(),this}requestData(e,t){if(this.authenticated&&this.connected){console.log("WebSocket: Requesting data...");let n={type:"data_request",data:{device_uuid:t,request_type:e}};this._sendMessage(n)}}connect(e){return console.log("WebSocket: Connecting..."),"undefined"!==typeof e&&(this.keepAlive=e),this._resetFlags(),this.connecting=!0,this.websocket=new WebSocket(this.wsUrl),this.websocket.onopen=e=>{this._openHandler(e)},this.websocket.onmessage=e=>{this._messageHandler(e)},this.websocket.onclose=e=>{this._closeHandler(e)},this.websocket.onerror=e=>{this._errorHandler(e)},this}disconnect(){return console.log("WebSocket: Disconnecting..."),this._resetFlags(),this.websocket.close(),this}destroy(){this._resetFlags(),console.log("WebSocket: Cleaning up"),this.onDestroy&&this.onDestroy(this),this.websocket&&(this.websocket.close(),this.websocket=null)}_resetFlags(){this.connected=!1,this.connecting=!1,this.authenticating=!1,this.authenticated=!1}_keepConnectionAlive(){!this.keepAlive||this.connected||this.authenticating||this.connecting||this.authenticated||(console.log("WebSocket: Connection lost, will attempt to reconnect"),this.onBeforeReconnectAttempt&&this.onBeforeReconnectAttempt(this),this.connected?this.authenticated||(this.onBeforeAuthRetry&&this.onBeforeAuthRetry(this),this._authenticate()):(this.onBeforeReconnect&&this.onBeforeReconnect(this),this.connect())),setTimeout((()=>{this._keepConnectionAlive()}),1e3*this._delay)}_authenticate(){let e="";this.onBeforeAuth&&(e=this.onBeforeAuth(this)),console.info("WebSocket: Connected, begining authentication"),this.authenticating=!0,!e&&this.tokenFactory&&(console.info("WebSocket: fetching access token"),e=this.tokenFactory());const t={type:"authenticate",data:{token:e}},n=JSON.stringify(t);this.websocket.send(n)}_sendMessage(e){const t=JSON.stringify(e);this.websocket.send(t)}_closeHandler(e){console.log(`WebSocket: Closed. code: ${e.code}`),this.onDisconnect&&this.onDisconnect(this,e),this.keepAlive||this.destroy()}_openHandler(e){this.connecting=!1,this.connected=!0,this.onConnect&&this.onConnect(this,e),this._authenticate()}_errorHandler(e){console.error("WebSocket: Error - message: ",e),this.onError&&this.onError(this,e),this.destroy()}_messageHandler(e){const t=o(e.data);"authSuccess"===t.type?(this.authenticating=!1,this.authenticated=!0,console.info("WebSocket: Connected and authenticated"),this.onAuthSuccess&&this.onAuthSuccess(this,t)):"authFailure"===t.type?(this.authenticating=!1,this.authenticated=!1,console.error("WebSocket: authentication failed"),this.onAuthFailure&&this.onAuthFailure(this,t)):"error"===t.type&&this.onError&&this.onError(this,t),t.type&&"function"===typeof this._messageTypeHandlers[t.type]&&this._messageTypeHandlers[t.type](o(t.data)),"function"===typeof this._onMessage&&this._onMessage(t)}setMessageHandler(e){if("function"!==typeof e)throw new Error("Handler of type function is required");this._onMessage=e}setHandler(e,t){if(!e||"string"!==typeof e)throw new Error("Message Type of type string is required");if("function"!==typeof t)throw new Error("Handler of type function is required");this._messageTypeHandlers[e]=t}unsetHandler(e){if(!e||"string"!==typeof e)throw new Error("Message Type of type string is required");delete this._messageTypeHandlers[e]}unsetAllHandlers(){this._messageTypeHandlers={}}}class r{constructor(){this._connections={}}createConnection(e,t,n=!0){if(!e)throw new Error("Connection ID is required");if(this._connections[e])throw new Error("Connection exists with this, try starting it instead");const o=new s;return this._connections[e]=o,o.init(t,n),o}stopConnection(e){if(!e)throw new Error("Connection ID is required");const t=this._connections[e];if(t)return t.keepAlive=!1,t.disconnect()}startConnection(e,t=!0){if(!e)throw new Error("Connection ID is required");const n=this._connections[e];if(!n)throw new Error("Connection does not exist for this id ");return n.keepAlive=t,n.connect(),n.disconnect()}destroyConnection(e){if(!e)throw new Error("Connection ID is required");const t=this._connections[e];t&&(t.keepAlive=!1,t.destroy(),delete this._connections[e])}}const i=new r,a=i},2401:(e,t,n)=>{n.r(t),n.d(t,{default:()=>pe});var o={};n.r(o),n.d(o,{appInfo:()=>y,identity:()=>g,logs:()=>b,registered:()=>v,settings:()=>f,sseConnected:()=>m,status:()=>p});var s={};n.r(s),n.d(s,{addLog:()=>A,addLogs:()=>P,setIdentity:()=>S,setLogs:()=>E,setRegistered:()=>C,setSettings:()=>k,setSseConnected:()=>_,setStatus:()=>w});var r={};n.r(r),n.d(r,{createWsConnection:()=>J,getIdentity:()=>j,getLogs:()=>H,getRegistrationStatus:()=>L,getSettings:()=>R,getStatus:()=>I,rebootEsp32Device:()=>Z,resetGpsDevice:()=>W,saveSettings:()=>O,scanWifi:()=>q,setup:()=>F,startRtcmSse:()=>z,startSSE:()=>U});var i={};n.r(i),n.d(i,{accessToken:()=>ee,isAuthenticated:()=>V,isLoggedIn:()=>Y});var a={};n.r(a),n.d(a,{clearAccessToken:()=>re,clearLoginData:()=>ie,setAccessToken:()=>ne,setIdToken:()=>oe,setRefreshToken:()=>se,setUser:()=>te});var c={};n.r(c),n.d(c,{login:()=>de,logout:()=>le,onUserStateChanged:()=>ue,register:()=>ce});var d=n(3340),l=n(741);function u(){return{status:{},settings:{},identity:{},sseConnected:!1,registered:!1,logs:[]}}var h=n(4147);function p(e){return e.status}function f(e){return e.settings}function g(e){return e.identity}function m(e){return e.sseConnected}function v(e){return e.registered}function y(e){return h}function b(e){return e.logs}function w(e,t){e.status=t}function k(e,t){e.settings=t}function S(e,t){e.identity=t}function _(e,t){e.sseConnected=t}function C(e,t){e.registered=t}function A(e,t){e.logs.length>100&&e.logs.shift(),e.logs.push(t)}function P(e,t){e.logs.length>100&&e.logs.slice(0,t.length-1),e.logs.concat(t)}function E(e,t){e.logs=t}n(9544),n(5363);var T=n(52),D=n.n(T),x=n(3845);function I({commit:e}){return new Promise(((t,n)=>{D().get("/api/status").then((n=>{e("devices/setStatus",n.data,{root:!0}),t(n.data)})).catch((e=>{n(e)}))}))}function L({commit:e}){return new Promise(((t,n)=>{e("devices/setRegistered",!0,{root:!0}),t(!0)}))}function R({commit:e}){return new Promise(((t,n)=>{D().get("/api/settings").then((n=>{e("devices/setSettings",n.data,{root:!0}),t(n.data)})).catch((e=>{n(e)}))}))}function O({dispatch:e},t){return new Promise(((n,o)=>{var s=new FormData;for(var r in t)s.append(r,t[r]);D().post("/api/settings",s).then((t=>{setTimeout((()=>{e("devices/getSettings",null,{root:!0}).finally((()=>{n(t.data)}))}),15e3)})).catch((e=>{o(e)}))}))}function q({commit:e}){return new Promise(((e,t)=>{let n=!1;const o=()=>{D().get("/api/wifi/scan").then((t=>{0!==t.data.length||n?e(t.data):(n=!0,setTimeout((()=>{o()}),5e3))})).catch((e=>{t(e)}))};o()}))}function j({commit:e}){return new Promise(((t,n)=>{D().get("/api/update/identity").then((n=>{e("devices/setIdentity",n.data,{root:!0}),t(n.data)})).catch((e=>{n(e)}))}))}function H({commit:e}){return new Promise(((t,n)=>{D().get("/api/logs").then((o=>{try{const n="string"===typeof o.data?JSON.parse((o.data||"").replace(/\r?\n|\r/g,"")):o.data;e("devices/setLogs",n,{root:!0}),t(n)}catch(s){console.log(s),n(s)}})).catch((e=>{n(e)}))}))}function F({commit:e},t){return new Promise(((e,n)=>{var o=new FormData;for(var s in t)o.append(s,t[s]);D().post("/api/setup",o).then((t=>{e(t.data)})).catch((e=>{n(e)}))}))}function W({commit:e}){return new Promise(((e,t)=>{D().post("/api/devices/gps/reset",{}).then((t=>{e(t.data)})).catch((e=>{t(e)}))}))}function Z({commit:e}){return new Promise(((e,t)=>{D().post("/api/devices/esp/reboot",{}).then((t=>{e(t.data)})).catch((e=>{t(e)}))}))}let N=0,B=null,M=null;function U({commit:e,dispatch:t}){const n=()=>{clearTimeout(B),B=setTimeout((()=>{e("devices/setSseConnected",!1,{root:!0}),t("devices/startSSE",{},{root:!0})}),5e3)};return new Promise(((o,s)=>{M=new EventSource("/api/events",{withCredentials:!0}),M.addEventListener("open",(function(n){console.log("Events Connected"),e("devices/setSseConnected",!0,{root:!0}),t("devices/getLogs",null,{root:!0}),o()}),!1),M.addEventListener("error",(function(n){console.log("SSE Error",n),e("devices/setSseConnected",!1,{root:!0}),n.target.readyState!=EventSource.OPEN&&(console.log("Events Disconnected",n),setTimeout((()=>{t("devices/startSSE",{},{root:!0})}),5e3),s())}),!1),M.addEventListener("status",(function(t){N=Date.now();const o=JSON.parse(t.data);e("devices/setStatus",o,{root:!0}),n()})),M.addEventListener("logs",(function(t){N=Date.now();const n=JSON.parse(t.data);e("devices/addLog",n,{root:!0})})),M.addEventListener("ping",(function(t){N=Date.now(),e("devices/setSseConnected",!0,{root:!0}),n()})),M.onmessage=function(e){n()}}))}function z({commit:e,dispatch:t}){return new Promise(((e,t)=>{M=new EventSource("/api/events/rtcm",{withCredentials:!0}),M.addEventListener("open",(function(t){console.log("RTCM Events Connected"),e()}),!1),M.addEventListener("error",(function(e){console.log("RTCM SSE Error",e),e.target.readyState!=EventSource.OPEN&&(console.log("RTCM Events Disconnected",e),t())}),!1),M.addEventListener("rtcm",(function(e){console.log("RTCM",e)})),M.onmessage=function(e){}}))}let $=0,G=0;function J({dispatch:e,commit:t,state:n,rootGetters:o}){return new Promise(((n,s)=>{try{const s="device_websocket_connecton";x.Z.destroyConnection(s);const r=x.Z.createConnection(s,"ws://"+window.location.host+"/api/ws",!1);r.tokenFactory=()=>{const e=o["user/accessToken"];return e},r.setHandler("status",(e=>{t("devices/setStatus",e,{root:!0})})),r.setHandler("log",(e=>{t("devices/addLog",e,{root:!0})})),r.setHandler("disconnected",(e=>{t("devices/setSseConnected",!1,{root:!0})})),r.setHandler("ping",(n=>{t("devices/setSseConnected",!0,{root:!0}),clearTimeout(G),G=setTimeout((()=>{t("devices/setSseConnected",!1,{root:!0})}),6e3),clearTimeout($),$=setTimeout((()=>{e("devices/createWsConnection",{},{root:!0})}),15e3)})),r.setHandler("connected",(e=>{})),n(s)}catch(r){s(r)}}))}const K={namespaced:!0,getters:o,mutations:s,actions:r,state:u};function Q(){return{user:{},accessToken:null}}var X=n(6395);function V(e){return Y(e)}function Y(e){return!!ee(e);//!!accessToken(state);
}function ee(e){const t=X.Z.getItem("access_token");return t}function te(e,t){e.user=t}function ne(e,t){X.Z.set("access_token",t)}function oe(e,t){X.Z.set("id_token",t)}function se(e,t){X.Z.set("refresh_token",t)}function re(e,t){X.Z.remove("access_token")}function ie(e,t){X.Z.remove("access_token"),X.Z.remove("id_token"),X.Z.remove("refresh_token")}var ae=n(8424);function ce({commit:e,rootGetters:t},n){return new Promise(((e,t)=>{const o=(0,ae.v0)();(0,ae.Xb)(o,n.email,n.password).then((t=>{const n=t.user;e(n)})).catch((e=>{e.code,e.message;t(e)}))}))}function de({commit:e,rootGetters:t},n){const o=(0,ae.v0)();return new Promise(((t,s)=>{(0,ae.Fb)(o,ae.aT).then((()=>{(0,ae.e5)(o,n.email,n.password).then((n=>{const o=n.user,s=n._tokenResponse;let r=s.refreshToken;e("user/setAccessToken",o.accessToken,{root:!0}),e("user/setIdToken",s.idToken,{root:!0}),e("user/setRefreshToken",r,{root:!0}),t(o)})).catch((e=>{e.code,e.message;s(e)}))})).catch((e=>{e.code,e.message}))}))}function le({commit:e,rootGetters:t},n){return new Promise(((t,n)=>{const o=(0,ae.v0)();(0,ae.w7)(o).then((()=>{t()})).catch((e=>{n(e)})).finally((()=>{e("user/clearLoginData",null,{root:!0}),window.location.reload()}))}))}function ue({commit:e,rootGetters:t},n){const o=(0,ae.v0)();(0,ae.Aj)(o,(async t=>{if(t){t.uid;e("user/setUser",t,{root:!0});let n=await t.getIdToken();e("user/setIdToken",n,{root:!0})}else e("user/clearLoginData",null,{root:!0})}))}const he={namespaced:!0,getters:i,mutations:a,actions:c,state:Q},pe=(0,d.h)((function(){const e=(0,l.MT)({modules:{devices:K,user:he},strict:!1});return e}))},4147:e=>{e.exports=JSON.parse('{"name":"frontend","version":"0.0.1","description":"User interface for Elyir Robotix Mower","productName":"Elyir Robotix Mower","author":"Temitope Adeyeri <temi.adeyeri@gmail.com>","private":true,"scripts":{"dev":"quasar dev","build":"quasar build && yarn fix-paths","build-package":"node ./build-package.js","fix-paths":"node ./fix-paths.js","build-fs":"cd ../ && pio run -t uploadfs || true && cd ./frontend && node ./post-build.js","build-fw":"cd ../ && pio run -t upload || true && cd ./frontend && node ./post-build.js","deploy-fs":"yarn build && yarn upload-fs","deploy-fw":"yarn upload-fw","deploy-all":"yarn build && yarn build-fs && yarn build-fw && yarn build-package","deploy":"yarn deploy-all","test":"echo \\"No test specified\\" && exit 0"},"dependencies":{"@quasar/extras":"^1.0.0","@zip.js/zip.js":"^2.4.23","axios":"^0.21.1","core-js":"^3.6.5","firebase":"^9.9.2","leaflet":"^1.8.0","quasar":"^2.0.0","shortid":"^2.2.16","spark-md5":"^3.0.2","timeago.js":"^4.0.2","vue":"^3.0.0","vue-i18n":"^9.0.0","vue-router":"^4.0.0","vue2-leaflet":"^2.7.1","vuex":"^4.0.1"},"devDependencies":{"@quasar/app":"^3.0.0","adm-zip":"^0.5.9"},"browserslist":["last 10 Chrome versions","last 10 Firefox versions","last 4 Edge versions","last 7 Safari versions","last 8 Android versions","last 8 ChromeAndroid versions","last 8 FirefoxAndroid versions","last 10 iOS versions","last 5 Opera versions"],"engines":{"node":">= 12.22.1","npm":">= 6.13.4","yarn":">= 1.21.1"},"fw_manifest":{"name":"Elyir RTK Base Station FW","fw_version":"0.5.0","fw_hash":"","fs_version":"0.5.0","fs_hash":"","description":"Elyir RTK base OTA package","build_date":"","device_env":"esp32things","author":"Temitope Adeyeri ","email":"temi.adeyeri@gmail.com"}}')}},t={};function n(o){var s=t[o];if(void 0!==s)return s.exports;var r=t[o]={id:o,loaded:!1,exports:{}};return e[o].call(r.exports,r,r.exports,n),r.loaded=!0,r.exports}n.m=e,(()=>{var e=[];n.O=(t,o,s,r)=>{if(!o){var i=1/0;for(l=0;l<e.length;l++){for(var[o,s,r]=e[l],a=!0,c=0;c<o.length;c++)(!1&r||i>=r)&&Object.keys(n.O).every((e=>n.O[e](o[c])))?o.splice(c--,1):(a=!1,r<i&&(i=r));if(a){e.splice(l--,1);var d=s();void 0!==d&&(t=d)}}return t}r=r||0;for(var l=e.length;l>0&&e[l-1][2]>r;l--)e[l]=e[l-1];e[l]=[o,s,r]}})(),(()=>{n.n=e=>{var t=e&&e.__esModule?()=>e["default"]:()=>e;return n.d(t,{a:t}),t}})(),(()=>{n.d=(e,t)=>{for(var o in t)n.o(t,o)&&!n.o(e,o)&&Object.defineProperty(e,o,{enumerable:!0,get:t[o]})}})(),(()=>{n.f={},n.e=e=>Promise.all(Object.keys(n.f).reduce(((t,o)=>(n.f[o](e,t),t)),[]))})(),(()=>{n.u=e=>"js/"+e+"."+{132:"77b2e2d7",145:"40a81dc2",193:"92df4762",232:"06df229e",360:"7ab9f31a",378:"6f34d8bb",411:"690cf268",496:"c23a76b1",554:"e2734a37",593:"cadd3f87",672:"5d41eb25",989:"1ac86b43"}[e]+".js"})(),(()=>{n.miniCssF=e=>"css/"+({143:"app",736:"vendor"}[e]||e)+"."+{143:"528166fd",496:"1ef0305e",736:"371a2e0e"}[e]+".css"})(),(()=>{n.g=function(){if("object"===typeof globalThis)return globalThis;try{return this||new Function("return this")()}catch(e){if("object"===typeof window)return window}}()})(),(()=>{n.o=(e,t)=>Object.prototype.hasOwnProperty.call(e,t)})(),(()=>{var e={},t="frontend:";n.l=(o,s,r,i)=>{if(e[o])e[o].push(s);else{var a,c;if(void 0!==r)for(var d=document.getElementsByTagName("script"),l=0;l<d.length;l++){var u=d[l];if(u.getAttribute("src")==o||u.getAttribute("data-webpack")==t+r){a=u;break}}a||(c=!0,a=document.createElement("script"),a.charset="utf-8",a.timeout=120,n.nc&&a.setAttribute("nonce",n.nc),a.setAttribute("data-webpack",t+r),a.src=o),e[o]=[s];var h=(t,n)=>{a.onerror=a.onload=null,clearTimeout(p);var s=e[o];if(delete e[o],a.parentNode&&a.parentNode.removeChild(a),s&&s.forEach((e=>e(n))),t)return t(n)},p=setTimeout(h.bind(null,void 0,{type:"timeout",target:a}),12e4);a.onerror=h.bind(null,a.onerror),a.onload=h.bind(null,a.onload),c&&document.head.appendChild(a)}}})(),(()=>{n.r=e=>{"undefined"!==typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})}})(),(()=>{n.nmd=e=>(e.paths=[],e.children||(e.children=[]),e)})(),(()=>{n.p=""})(),(()=>{var e=(e,t,n,o)=>{var s=document.createElement("link");s.rel="stylesheet",s.type="text/css";var r=r=>{if(s.onerror=s.onload=null,"load"===r.type)n();else{var i=r&&("load"===r.type?"missing":r.type),a=r&&r.target&&r.target.href||t,c=new Error("Loading CSS chunk "+e+" failed.\n("+a+")");c.code="CSS_CHUNK_LOAD_FAILED",c.type=i,c.request=a,s.parentNode.removeChild(s),o(c)}};return s.onerror=s.onload=r,s.href=t,document.head.appendChild(s),s},t=(e,t)=>{for(var n=document.getElementsByTagName("link"),o=0;o<n.length;o++){var s=n[o],r=s.getAttribute("data-href")||s.getAttribute("href");if("stylesheet"===s.rel&&(r===e||r===t))return s}var i=document.getElementsByTagName("style");for(o=0;o<i.length;o++){s=i[o],r=s.getAttribute("data-href");if(r===e||r===t)return s}},o=o=>new Promise(((s,r)=>{var i=n.miniCssF(o),a=n.p+i;if(t(i,a))return s();e(o,a,s,r)})),s={143:0};n.f.miniCss=(e,t)=>{var n={496:1};s[e]?t.push(s[e]):0!==s[e]&&n[e]&&t.push(s[e]=o(e).then((()=>{s[e]=0}),(t=>{throw delete s[e],t})))}})(),(()=>{var e={143:0};n.f.j=(t,o)=>{var s=n.o(e,t)?e[t]:void 0;if(0!==s)if(s)o.push(s[2]);else{var r=new Promise(((n,o)=>s=e[t]=[n,o]));o.push(s[2]=r);var i=n.p+n.u(t),a=new Error,c=o=>{if(n.o(e,t)&&(s=e[t],0!==s&&(e[t]=void 0),s)){var r=o&&("load"===o.type?"missing":o.type),i=o&&o.target&&o.target.src;a.message="Loading chunk "+t+" failed.\n("+r+": "+i+")",a.name="ChunkLoadError",a.type=r,a.request=i,s[1](a)}};n.l(i,c,"chunk-"+t,t)}},n.O.j=t=>0===e[t];var t=(t,o)=>{var s,r,[i,a,c]=o,d=0;if(i.some((t=>0!==e[t]))){for(s in a)n.o(a,s)&&(n.m[s]=a[s]);if(c)var l=c(n)}for(t&&t(o);d<i.length;d++)r=i[d],n.o(e,r)&&e[r]&&e[r][0](),e[r]=0;return n.O(l)},o=globalThis["webpackChunkfrontend"]=globalThis["webpackChunkfrontend"]||[];o.forEach(t.bind(null,0)),o.push=t.bind(null,o.push.bind(o))})();var o=n.O(void 0,[736],(()=>n(4793)));o=n.O(o)})();