"use strict";(globalThis["webpackChunkfrontend"]=globalThis["webpackChunkfrontend"]||[]).push([[360],{5360:(t,e,a)=>{a.r(e),a.d(e,{default:()=>wt});var n=a(3673),i=a(2323);const s={class:"row q-gutter-lg justify-center items-center"},o={class:"row items-center"},l=(0,n.Uk)("Charger Connected"),r={class:"row items-center"},c=(0,n.Uk)("WiFi connection status: "),u=(0,n.Uk)("Connected"),d=(0,n.Uk)("Disconnected"),w={class:"row items-center"},g=(0,n.Uk)(" GPS status: "),p=(0,n.Uk)("Fixed"),v=(0,n.Uk)("Not Fixed"),m=(0,n.Uk)(" Satellites In View: "),_={class:"row items-center"},f={class:"row"},k=(0,n.Uk)(" NTRIP Server Connection status: "),b=(0,n.Uk)("Active"),y=(0,n.Uk)("Disabled"),h=(0,n.Uk)("Inactive"),C={class:"row items-center"},W={class:"row"},U=(0,n.Uk)(" RTCM Web Socket Connection status: "),q=(0,n.Uk)("Active"),S=(0,n.Uk)("Disabled"),j=(0,n.Uk)("Inactive"),D=(0,n.Uk)("Device events connection status: "),Z=(0,n.Uk)("Connected"),z=(0,n.Uk)("Disconnected"),Q=(0,n._)("div",{class:"mxh-10em bg-grey-2"},null,-1),I={class:"text-center mt-2"},O=(0,n.Uk)("Sign out "),F=(0,n.Uk)("Signing out... "),A={class:"p-1 q-mt-md text-center"},T={class:"faded"},$=(0,n.Uk)(" -- "),L={class:"faded"};function N(t,e,a,N,x,P){const V=(0,n.up)("q-btn"),B=(0,n.up)("q-toolbar-title"),H=(0,n.up)("q-icon"),M=(0,n.up)("q-badge"),R=(0,n.up)("tooltip"),G=(0,n.up)("q-toolbar"),K=(0,n.up)("q-header"),Y=(0,n.up)("q-item-section"),E=(0,n.up)("q-item-label"),J=(0,n.up)("q-item"),X=(0,n.up)("q-list"),tt=(0,n.up)("q-separator"),et=(0,n.up)("q-spinner-oval"),at=(0,n.up)("q-space"),nt=(0,n.up)("q-drawer"),it=(0,n.up)("router-view"),st=(0,n.up)("q-page-container"),ot=(0,n.up)("q-layout");return(0,n.wg)(),(0,n.j4)(ot,{view:"lHh Lpr lFf"},{default:(0,n.w5)((()=>[(0,n.Wm)(K,{bordered:"",elevated:"",class:"bg-white text-grey-10"},{default:(0,n.w5)((()=>[(0,n.Wm)(G,null,{default:(0,n.w5)((()=>[(0,n.Wm)(V,{flat:"",dense:"",round:"",icon:"menu","aria-label":"Menu",onClick:t.toggleLeftDrawer},null,8,["onClick"]),(0,n.Wm)(B,null,{default:(0,n.w5)((()=>[(0,n.Uk)((0,i.zw)(t.productName),1)])),_:1}),(0,n._)("div",s,[(0,n._)("div",o,[t.status.chargerConnected?((0,n.wg)(),(0,n.j4)(H,{key:0,size:"1.5em",name:"power",color:"info"})):(0,n.kq)("",!0),(0,n.Wm)(H,{size:"1.5em",name:t.batteryStatusIcon,color:t.batteryStatusColor},{default:(0,n.w5)((()=>[(0,n.Wm)(R,null,{default:(0,n.w5)((()=>[(0,n.Uk)("Battery level: "+(0,i.zw)(t.status.battery_level?t.status.battery_level+"%":"Unknown")+" ",1),t.status.chargerConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"positive"},{default:(0,n.w5)((()=>[l])),_:1})):(0,n.kq)("",!0)])),_:1})])),_:1},8,["name","color"])]),(0,n._)("div",r,[(0,n.Wm)(H,{size:"1.5em",name:t.status.wifiConnected?"wifi":"wifi_off",color:t.status.wifiConnected?"positive":"negative"},{default:(0,n.w5)((()=>[(0,n.Wm)(R,null,{default:(0,n.w5)((()=>[c,t.status.wifiConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"positive"},{default:(0,n.w5)((()=>[u])),_:1})):((0,n.wg)(),(0,n.j4)(M,{key:1,color:"negative"},{default:(0,n.w5)((()=>[d])),_:1}))])),_:1})])),_:1},8,["name","color"])]),(0,n._)("div",w,[(0,n.Wm)(H,{size:"1.5em",name:"satellite_alt",color:t.status.gpsConnected?"positive":"negative"},null,8,["color"]),t.status.gpsConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"info"},{default:(0,n.w5)((()=>[(0,n.Uk)((0,i.zw)(t.status.gpsSiv),1)])),_:1})):(0,n.kq)("",!0),(0,n.Wm)(R,null,{default:(0,n.w5)((()=>[(0,n._)("div",null,[g,t.status.gpsConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"positive"},{default:(0,n.w5)((()=>[p])),_:1})):((0,n.wg)(),(0,n.j4)(M,{key:1,color:"negative"},{default:(0,n.w5)((()=>[v])),_:1}))]),(0,n._)("div",null,[m,t.status.gpsConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"info"},{default:(0,n.w5)((()=>[(0,n.Uk)((0,i.zw)(t.status.gpsSiv),1)])),_:1})):(0,n.kq)("",!0)])])),_:1})]),(0,n._)("div",_,[(0,n.Wm)(H,{size:"1.5em",name:t.status.ntripConnected?"public":"public_off",color:t.status.ntripConnected?"positive":t.settings.connectNtrip?"negative":"grey-4"},null,8,["name","color"]),(0,n.Wm)(R,null,{default:(0,n.w5)((()=>[(0,n._)("span",f,[k,t.status.ntripConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"positive"},{default:(0,n.w5)((()=>[b])),_:1})):(0,n.kq)("",!0),t.settings.connectNtrip?((0,n.wg)(),(0,n.j4)(M,{key:2,color:"negative"},{default:(0,n.w5)((()=>[h])),_:1})):((0,n.wg)(),(0,n.j4)(M,{key:1,color:"grey-10"},{default:(0,n.w5)((()=>[y])),_:1}))])])),_:1})]),(0,n._)("div",C,[(0,n.Wm)(H,{size:"1.5em",name:(t.status.wsConnected,"hub"),color:t.status.wsConnected?"positive":t.settings.connectWs?"negative":"grey-4"},null,8,["name","color"]),(0,n.Wm)(R,null,{default:(0,n.w5)((()=>[(0,n._)("span",W,[U,t.status.wsConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"positive"},{default:(0,n.w5)((()=>[q])),_:1})):(0,n.kq)("",!0),t.settings.connectWs?((0,n.wg)(),(0,n.j4)(M,{key:2,color:"negative"},{default:(0,n.w5)((()=>[j])),_:1})):((0,n.wg)(),(0,n.j4)(M,{key:1,color:"grey-10"},{default:(0,n.w5)((()=>[S])),_:1}))])])),_:1})]),(0,n._)("div",null,[t.sseConnected?((0,n.wg)(),(0,n.j4)(H,{key:0,color:"positive",size:"1.5rem",name:"link"})):((0,n.wg)(),(0,n.j4)(H,{key:1,color:"negative",size:"1.5rem",name:"link_off"})),(0,n.Wm)(R,null,{default:(0,n.w5)((()=>[D,t.sseConnected?((0,n.wg)(),(0,n.j4)(M,{key:0,color:"positive"},{default:(0,n.w5)((()=>[Z])),_:1})):((0,n.wg)(),(0,n.j4)(M,{key:1,color:"negative"},{default:(0,n.w5)((()=>[z])),_:1}))])),_:1})])])])),_:1})])),_:1}),(0,n.Wm)(nt,{modelValue:t.leftDrawerOpen,"onUpdate:modelValue":e[0]||(e[0]=e=>t.leftDrawerOpen=e),"show-if-above":"",bordered:"",elevated:"",class:"column"},{default:(0,n.w5)((()=>[Q,(0,n.Wm)(X,null,{default:(0,n.w5)((()=>[((0,n.wg)(!0),(0,n.iD)(n.HY,null,(0,n.Ko)(t.menuItems,((t,e)=>((0,n.wg)(),(0,n.j4)(J,{clickable:"",tag:"a",href:t.link,key:"menu-item-"+e,active:!!t.active&&t.active()},{default:(0,n.w5)((()=>[t.icon?((0,n.wg)(),(0,n.j4)(Y,{key:0,avatar:""},{default:(0,n.w5)((()=>[(0,n.Wm)(H,{name:t.icon},null,8,["name"])])),_:2},1024)):(0,n.kq)("",!0),(0,n.Wm)(Y,null,{default:(0,n.w5)((()=>[(0,n.Wm)(E,null,{default:(0,n.w5)((()=>[(0,n.Uk)((0,i.zw)(t.title),1)])),_:2},1024),(0,n.Wm)(E,{caption:""},{default:(0,n.w5)((()=>[(0,n.Uk)((0,i.zw)(t.caption),1)])),_:2},1024)])),_:2},1024)])),_:2},1032,["href","active"])))),128))])),_:1}),(0,n.Wm)(tt),(0,n._)("div",I,[(0,n.Wm)(V,{flat:"",color:"primary",class:"full-width",onClick:t.logout,loading:t.loggingOut},{loading:(0,n.w5)((()=>[(0,n.Wm)(et,{class:"mr-1"}),F])),default:(0,n.w5)((()=>[O])),_:1},8,["onClick","loading"])]),(0,n.Wm)(at),(0,n._)("div",A,[(0,n._)("span",T,"FW: v"+(0,i.zw)(t.identity.fw_version),1),$,(0,n._)("span",L," FS: v"+(0,i.zw)(t.identity.fs_version),1)])])),_:1},8,["modelValue"]),(0,n.Wm)(st,null,{default:(0,n.w5)((()=>[(0,n.Wm)(it)])),_:1})])),_:1})}a(9544);var x=a(741),P=a(4147);const{productName:V,version:B}=P,H=(0,n.aZ)({name:"MainLayout",components:{},data(){return{productName:V,version:B,leftDrawerOpen:!1,loggingOut:!1,menuItems:[{title:"Dashboard",caption:"Application overview etc.",icon:"dashboard",link:"/#",active:()=>"/"===this.$route.path},{title:"Settings",caption:"Application settings etc.",icon:"settings",link:"/#settings",active:()=>"/settings"===this.$route.path},{title:"WiFi Settings",caption:"WiFi settings for Access Point etc.",icon:"wifi",link:"/#wifi",active:()=>"/wifi"===this.$route.path},{title:"OTA",caption:"Firmware update etc.",icon:"browser_updated",link:"/#ota",active:()=>"/ota"===this.$route.path},{title:"Controls",caption:"Device controls.",icon:"videogame_asset",link:"/#control",active:()=>"/control"===this.$route.path},{title:"About",caption:"About this application etc.",icon:"info",link:"/#about",active:()=>"/about"===this.$route.path}]}},computed:{...(0,x.Se)({identity:"devices/identity",statusData:"devices/status",settings:"devices/settings",sseConnected:"devices/sseConnected"}),status(){return this.statusData||{}},batteryStatusColor(){let t="grey-10";return t=this.status.battery_level>=30?"positive":this.status.battery_level<30&&this.status.battery_level>=10?"warning":"negative",t},batteryStatusIcon(){let t="battery_unknown";return this.status.battery_level>98?t="battery_full":this.status.battery_level>75?t="battery_6_bar ":this.status.battery_level>60?t="battery_5_bar":this.status.battery_level>45?t="battery_4_bar":this.status.battery_level>30?t="battery_3_bar":this.status.battery_level>15?t="battery_2_bar":this.status.battery_level>0?t="battery_1_bar":0==this.status.battery_level&&(t="battery_0_bar"),t}},methods:{...(0,x.nv)({getStatus:"devices/getStatus",getSettings:"devices/getSettings"}),logout(){this.loggingOut=!0,this.$store.dispatch("user/logout").then((()=>{this.$router.push("/login")})).finally((()=>{this.loggingOut=!1}))},toggleLeftDrawer(){this.leftDrawerOpen=!this.leftDrawerOpen}},mounted(){}});var M=a(4260),R=a(3066),G=a(3812),K=a(9570),Y=a(8240),E=a(3747),J=a(4554),X=a(9721),tt=a(6873),et=a(3414),at=a(2035),nt=a(2350),it=a(7011),st=a(5869),ot=a(2548),lt=a(2025),rt=a(2652),ct=a(7518),ut=a.n(ct);const dt=(0,M.Z)(H,[["render",N]]),wt=dt;ut()(H,"components",{QLayout:R.Z,QHeader:G.Z,QToolbar:K.Z,QBtn:Y.Z,QToolbarTitle:E.Z,QIcon:J.Z,QBadge:X.Z,QDrawer:tt.Z,QItem:et.Z,QItemSection:at.Z,QItemLabel:nt.Z,QList:it.Z,QSeparator:st.Z,QSpinnerOval:ot.Z,QSpace:lt.Z,QPageContainer:rt.Z})}}]);