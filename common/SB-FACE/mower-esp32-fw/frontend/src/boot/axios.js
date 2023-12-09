import { boot } from 'quasar/wrappers'
import axios from 'axios'
import useStore from 'src/store'

const store = useStore();
// Be careful when using SSR for cross-request state pollution
// due to creating a Singleton instance here;
// If any client changes this (global) instance, it might be a
// good idea to move this instance creation inside of the
// "export default () => {}" function below (which runs individually
// for each client)
const api = axios.create({ baseURL: 'https://api.example.com' })
axios.defaults.timeout = 50000;
axios.interceptors.request.use(function (config) {

  let token = store.getters['user/accessToken'];
  if (token && !config.bypassAuthIntercept) {
    config.headers.Authorization = `Bearer ${token}`;
  }

  return { ...config }
});
axios.interceptors.response.use(function (response) {
  return response;
}, function (error, config) {
  const statusCode = ((error || {}).response || {}).status;
  // logError('ERR: ', statusCode, errName, errCode);
  if (401 === statusCode && !error.config.bypassUnauthorizeRedirect) {
    // user is not authorized therefore reload the page to attempt to get a new token
    // log('Unauthorized user, reloading page...');
    store.dispatch('user/logout', {}, { root: true });
    window.location.reload();
  } else {
    return Promise.reject(error);
  }
});
export default boot(({ app }) => {
  // for use inside Vue files (Options API) through this.$axios and this.$api

  app.config.globalProperties.$axios = axios
  // ^ ^ ^ this will allow you to use this.$axios (for Vue Options API form)
  //       so you won't necessarily have to import axios in each vue file

  app.config.globalProperties.$api = api
  // ^ ^ ^ this will allow you to use this.$api (for Vue Options API form)
  //       so you can easily perform requests against your app's API
})

export { api }
