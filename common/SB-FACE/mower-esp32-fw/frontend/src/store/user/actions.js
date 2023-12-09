import axios from "axios";
import { LocalStorage } from "quasar";

import { getAuth, createUserWithEmailAndPassword, signOut, signInWithEmailAndPassword, onAuthStateChanged, setPersistence, browserSessionPersistence, localPersistence } from "firebase/auth";


// export function getStatus ({ commit }) {
//     return new Promise((resolve, reject) => {

//     });
// }
// export function login ({ commit }, data) {
//     return new Promise((resolve, reject) => {
//         var form_data = new FormData();
//         for (var key in data) {
//             form_data.append(key, data[key]);
//         }
//         axios.post('/api/login', form_data)
//             .then(response => {
//                 if (response.data.access_token) {
//                     commit("user/setAccessToken", response.data.access_token, { root: true });
//                     window.location.reload();
//                     return resolve(response.data);
//                 }
//                 reject(response.data);
//             }).catch(error => {
//                 reject(error);
//             });
//     });
// }

// export function validateToken ({ commit, rootGetters }, data) {
//     return new Promise((resolve, reject) => {
//         var form_data = new FormData();
//         form_data.append("token", rootGetters["user/accessToken"]);
//         axios.post('/api/token/validate', form_data)
//             .then(response => {
//                 return resolve(response.data);
//             }).catch(error => {
//                 reject(error);
//             });
//     });
// }
// export function revokeToken ({ commit, rootGetters }, data) {
//     return new Promise((resolve, reject) => {
//         var form_data = new FormData();
//         form_data.append("token", rootGetters["user/accessToken"]);
//         axios.post('/api/token/revoke', form_data)
//             .catch(error => {
//                 // reject(error);
//             }).finally(() => {
//                 commit("user/clearAccessToken", null, { root: true });
//                 window.location.reload();
//                 return resolve();
//             });
//     });
// }
// export function logout ({ commit, rootGetters, dispatch }, data) {
//     return dispatch("user/revokeToken", null, { root: true });
// }

export function register ({ commit, rootGetters }, data) {
    // onUserStateChanged({ commit, rootGetters }, data)
    return new Promise((resolve, reject) => {
        const auth = getAuth();
        createUserWithEmailAndPassword(auth, data.email, data.password)
            .then((userCredential) => {
                // Signed in 
                const user = userCredential.user;
                resolve(user);
            })
            .catch((error) => {
                const errorCode = error.code;
                const errorMessage = error.message;
                reject(error);
                // ..
            });
    });
}
export function login ({ commit, rootGetters }, data) {
    // onUserStateChanged({ commit, rootGetters }, data);
    const auth = getAuth();
    return new Promise((resolve, reject) => {
        setPersistence(auth, browserSessionPersistence)
            .then(() => {
                signInWithEmailAndPassword(auth, data.email, data.password)
                    .then((userCredential) => {
                        debugger;
                        // Signed in 
                        const user = userCredential.user;
                        const resp = userCredential._tokenResponse;
                        let refreshToken = resp.refreshToken;
                        commit("user/setAccessToken", user.accessToken, { root: true });
                        commit("user/setIdToken", resp.idToken, { root: true });
                        commit("user/setRefreshToken", refreshToken, { root: true });

                        resolve(user);
                        // ...
                    })
                    .catch((error) => {
                        const errorCode = error.code;
                        const errorMessage = error.message;
                        reject(error);
                    });
            })
            .catch((error) => {
                // Handle Errors here.
                const errorCode = error.code;
                const errorMessage = error.message;
            });
    });
}
export function logout ({ commit, rootGetters }, data) {
    return new Promise((resolve, reject) => {
        const auth = getAuth();
        signOut(auth).then(() => {
            // Sign-out successful.

            resolve();
        }).catch((error) => {
            // An error happened.
            reject(error);
        }).finally(() => {
            commit("user/clearLoginData", null, { root: true });
            window.location.reload();
        });
    });
}

export function onUserStateChanged ({ commit, rootGetters }, data) {
    const auth = getAuth();
    onAuthStateChanged(auth, async (user) => {
        if (user) {
            // User is signed in, see docs for a list of available properties
            // https://firebase.google.com/docs/reference/js/firebase.User
            const uid = user.uid;
            commit("user/setUser", user, { root: true });
            let idToken = await user.getIdToken();
            commit("user/setIdToken", idToken, { root: true });
            // ...
        } else {
            // User is signed out
            commit("user/clearLoginData", null, { root: true });
            // ...
        }
    });
}