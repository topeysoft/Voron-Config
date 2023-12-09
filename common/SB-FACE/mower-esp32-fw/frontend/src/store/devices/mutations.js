import { ref } from "vue";

export function setStatus (state, status) {
    state.status = status;
}
export function setSettings (state, settings) {
    state.settings = settings;
}
export function setIdentity (state, identity) {
    state.identity = identity;
}
export function setSseConnected (state, sseConnected) {
    state.sseConnected = sseConnected;
}
export function setRegistered (state, registered) {
    state.registered = registered;
}
export function addLog (state, log) {
    if (state.logs.length > 100) {
        state.logs.shift();
    }
    state.logs.push(log);
}
export function addLogs (state, logs) {
    if (state.logs.length > 100) {
        state.logs.slice(0, logs.length - 1);
    }
    state.logs.concat(logs);
}
export function setLogs (state, logs) {
    state.logs = logs;
}