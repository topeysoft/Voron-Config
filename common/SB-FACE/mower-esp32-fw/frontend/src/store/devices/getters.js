import pkgInfo from '../../../package.json'

export function status (state) {
    return state.status;
}
export function settings (state) {
    return state.settings;
}
export function identity (state) {
    return state.identity;
}
export function sseConnected (state) {
    return state.sseConnected;
}
export function registered (state) {
    return state.registered;
}
export function appInfo (state) {
    return pkgInfo;
}
export function logs (state) {
    return state.logs;
}
