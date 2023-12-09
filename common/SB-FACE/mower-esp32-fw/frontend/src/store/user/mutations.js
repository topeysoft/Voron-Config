import { LocalStorage } from "quasar";
import { ref } from "vue";



export function setUser (state, user) {
    state.user = user;
}
export function setAccessToken (state, token) {
    LocalStorage.set("access_token", token);
}
export function setIdToken (state, token) {
    LocalStorage.set("id_token", token);
}
export function setRefreshToken (state, token) {
    LocalStorage.set("refresh_token", token);
}
export function clearAccessToken (state, access_token) {
    LocalStorage.remove("access_token");
}
export function clearLoginData (state, access_token) {
    LocalStorage.remove("access_token");
    LocalStorage.remove("id_token");
    LocalStorage.remove("refresh_token");
}