import axios from "axios";
import WebsocketConnectionManager from "src/services/ws.service";

export function getStatus ({ commit }) {
    return new Promise((resolve, reject) => {
        axios.get("/api/status")
            .then(response => {
                commit("devices/setStatus", response.data, { root: true });
                resolve(response.data);
            }).catch(error => {
                reject(error);
            });
    });
}
export function getRegistrationStatus ({ commit }) {
    return new Promise((resolve, reject) => {
        commit("devices/setRegistered", true, { root: true });
        resolve(true);
        // axios.get("/api/registered")
        //     .then(response => {
        //         commit("devices/setRegistered", response.data.registered, { root: true });
        //         resolve(response.data);
        //     }).catch(error => {
        //         reject(error);
        //     });
    });
}
export function getSettings ({ commit }) {
    return new Promise((resolve, reject) => {
        axios.get("/api/settings")
            .then(response => {
                commit("devices/setSettings", response.data, { root: true });
                resolve(response.data);
            }).catch(error => {
                reject(error);
            });
    });
}
export function saveSettings ({ dispatch }, settings) {
    return new Promise((resolve, reject) => {
        var form_data = new FormData();
        for (var key in settings) {
            form_data.append(key, settings[key]);
        }
        axios.post("/api/settings", form_data)
            .then(response => {
                setTimeout(() => {
                    dispatch('devices/getSettings', null, { root: true }).finally(() => {
                        resolve(response.data);
                    });
                }, 15000); // Wait 15 seconds for device to reboot
            }).catch(error => {
                reject(error);
            });
    });
}
export function scanWifi ({ commit }) {
    return new Promise((resolve, reject) => {
        let retried = false;
        const scan = () => {
            axios.get("/api/wifi/scan")
                .then(response => {
                    if (response.data.length === 0 && !retried) {
                        retried = true;
                        setTimeout(() => {
                            scan();
                        }, 5000);
                    } else {
                        resolve(response.data);
                    }
                }).catch(error => {
                    reject(error);
                });
        }
        scan();
    });
}
export function getIdentity ({ commit }) {
    return new Promise((resolve, reject) => {
        axios.get('/api/update/identity')
            .then(response => {
                commit("devices/setIdentity", response.data, { root: true });
                resolve(response.data);
            }).catch(error => {
                reject(error);
            });
    });
}
export function getLogs ({ commit }) {
    return new Promise((resolve, reject) => {
        axios.get('/api/logs')
            .then(response => {
                try {
                    const data = typeof response.data === 'string' ? JSON.parse((response.data || "").replace(/\r?\n|\r/g, "")) : response.data;
                    commit("devices/setLogs", data, { root: true });
                    resolve(data);
                } catch (error) {
                    console.log(error);
                    reject(error);
                }
            }).catch(error => {
                reject(error);
            });
    });
}
export function setup ({ commit }, data) {
    return new Promise((resolve, reject) => {
        var form_data = new FormData();
        for (var key in data) {
            form_data.append(key, data[key]);
        }
        axios.post('/api/setup', form_data)
            .then(response => {
                resolve(response.data);
            }).catch(error => {
                reject(error);
            });
    });
}
export function resetGpsDevice ({ commit }) {
    return new Promise((resolve, reject) => {
        axios.post('/api/devices/gps/reset', {})
            .then(response => {
                resolve(response.data);
            }).catch(error => {
                reject(error);
            });
    });
}
export function rebootEsp32Device ({ commit }) {
    return new Promise((resolve, reject) => {
        axios.post('/api/devices/esp/reboot', {})
            .then(response => {
                resolve(response.data);
            }).catch(error => {
                reject(error);
            });
    });
}
let lastMessageReceivedAt = 0;
let sseReconnectInterval = null;
let sseDisconnectInterval = null;
let source = null;

export function startSSE ({ commit, dispatch }) {
    const keepSSEConnectionAlive = () => {
        clearTimeout(sseDisconnectInterval);
        sseDisconnectInterval = setTimeout(() => {
            commit("devices/setSseConnected", false, { root: true });
            dispatch("devices/startSSE", {}, { root: true });
        }, 5000);
    }
    return new Promise((resolve, reject) => {
        source = new EventSource('/api/events', { withCredentials: true });

        source.addEventListener('open', function (e) {
            console.log("Events Connected");
            commit("devices/setSseConnected", true, { root: true });
            dispatch("devices/getLogs", null, { root: true });
            resolve();
        }, false);
        source.addEventListener('error', function (e) {
            console.log("SSE Error", e);
            commit("devices/setSseConnected", false, { root: true });
            if (e.target.readyState != EventSource.OPEN) {
                console.log("Events Disconnected", e);
                setTimeout(() => {
                    dispatch("devices/startSSE", {}, { root: true });
                }, 5000);
                reject();
            }
        }, false);

        source.addEventListener('status', function (e) {
            lastMessageReceivedAt = Date.now();
            const data = JSON.parse(e.data);
            commit("devices/setStatus", data, { root: true });
            keepSSEConnectionAlive();
        });
        source.addEventListener('logs', function (e) {
            lastMessageReceivedAt = Date.now();
            const data = JSON.parse(e.data);
            commit("devices/addLog", data, { root: true });
        });
        source.addEventListener('ping', function (e) {
            lastMessageReceivedAt = Date.now();
            commit("devices/setSseConnected", true, { root: true });
            // clearTimeout(sseReconnectInterval);
            // sseReconnectInterval = setTimeout(() => {
            //     source.close();
            // }, 5000);
            keepSSEConnectionAlive();
        });
        source.onmessage = function (e) {
            keepSSEConnectionAlive();
        }
    });

}
export function startRtcmSse ({ commit, dispatch }) {
    return new Promise((resolve, reject) => {
        source = new EventSource('/api/events/rtcm', { withCredentials: true });

        source.addEventListener('open', function (e) {
            console.log("RTCM Events Connected");
            // commit("devices/setSseConnected", true, { root: true });
            resolve();
        }, false);
        source.addEventListener('error', function (e) {
            console.log("RTCM SSE Error", e);
            // commit("devices/setSseConnected", false, { root: true });
            if (e.target.readyState != EventSource.OPEN) {
                console.log("RTCM Events Disconnected", e);
                // setTimeout(() => {
                //     dispatch("devices/startSSE", {}, { root: true });
                // }, 5000);
                reject();
            }
        }, false);

        source.addEventListener('rtcm', function (e) {
            console.log("RTCM", e);
        });

        source.onmessage = function (e) {
        }
    });

}

let ws_ping_timeout = 0;
let ws_disconnect_timeout = 0;
export function createWsConnection ({ dispatch, commit, state, rootGetters }) {
    return new Promise((resolve, reject) => {
        try {
            const connectionId = 'device_websocket_connecton';

            WebsocketConnectionManager.destroyConnection(connectionId);
            const client = WebsocketConnectionManager.createConnection(connectionId, 'ws://' + window.location.host + `/api/ws`, false);
            client.tokenFactory = () => {
                const token = rootGetters['user/accessToken'];
                return token;
            }
            client.setHandler('status', (data) => {
                commit('devices/setStatus', data, { root: true });
            })
            client.setHandler('log', (data) => {
                commit("devices/addLog", data, { root: true });
            })
            client.setHandler('disconnected', (data) => {
                commit("devices/setSseConnected", false, { root: true });
            })
            client.setHandler('ping', (data) => {
                commit("devices/setSseConnected", true, { root: true });
                clearTimeout(ws_disconnect_timeout);
                ws_disconnect_timeout = setTimeout(() => {
                    commit("devices/setSseConnected", false, { root: true });
                }, 6000);
                clearTimeout(ws_ping_timeout);
                ws_ping_timeout = setTimeout(() => {
                    dispatch('devices/createWsConnection', {}, { root: true });
                }, 15000);
            })
            client.setHandler('connected', (thing) => {
                // client.requestData()
            })
            resolve(connectionId);
        } catch (err) {
            reject(err)
        }
    });
}