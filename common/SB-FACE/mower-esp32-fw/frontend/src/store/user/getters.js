import { LocalStorage } from "quasar";

export function isAuthenticated (state) {
    return isLoggedIn(state);
}

export function isLoggedIn (state) {
    return !!accessToken(state) //!!accessToken(state);
}
export function accessToken (state) {
    const token = LocalStorage.getItem("access_token");
    return token;
}