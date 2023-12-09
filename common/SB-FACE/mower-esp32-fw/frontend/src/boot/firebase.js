// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";
import store from "src/store";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyCxHy8Cw05QPkRPFmT_DlpMkk952yWAbsQ",
    authDomain: "elyir-d4ede.firebaseapp.com",
    databaseURL: "https://elyir-d4ede.firebaseio.com",
    projectId: "elyir-d4ede",
    storageBucket: "elyir-d4ede.appspot.com",
    messagingSenderId: "1025994341095",
    appId: "1:1025994341095:web:f457fe11b610a735",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
store().dispatch("user/onUserStateChanged", {}, { root: true })


// TODO: Replace the following with your app's Firebase project configuration
// See: https://firebase.google.com/docs/web/learn-more#config-object


// Initialize Realtime Database and get a reference to the service
export const database = getDatabase(app);
