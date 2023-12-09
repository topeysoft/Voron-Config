import { route } from 'quasar/wrappers'
import { createRouter, createMemoryHistory, createWebHistory, createWebHashHistory } from 'vue-router'
import routes from './routes'
import useStore from 'src/store'

const store = useStore();
/*
 * If not building with SSR mode, you can
 * directly export the Router instantiation;
 *
 * The function below can be async too; either use
 * async/await or return a Promise which resolves
 * with the Router instance.
 */

const isLoggedIn = () => {
  return store.getters['user/isLoggedIn'];
}

const gotoLogin = (to, from, next) => {
  next({
    name: 'login',
    params: { nextUrl: to.fullPath }
  });
}
const gotoDashboard = (to, from, next) => {
  next({ name: 'dashboard' })
}

export default route(function (/* { store, ssrContext } */) {
  const createHistory = process.env.SERVER
    ? createMemoryHistory
    : (process.env.VUE_ROUTER_MODE === 'history' ? createWebHistory : createWebHashHistory)

  const Router = createRouter({
    scrollBehavior: () => ({ left: 0, top: 0 }),
    routes,

    // Leave this as is and make changes in quasar.conf.js instead!
    // quasar.conf.js -> build -> vueRouterMode
    // quasar.conf.js -> build -> publicPath
    history: createHistory(process.env.MODE === 'ssr' ? void 0 : process.env.VUE_ROUTER_BASE)
  })

  Router.beforeEach((to, from, next) => {
    if (to.matched.some(record => record.meta.requiresAuth)) {
      if (isLoggedIn()) {
        next()
      } else {
        gotoLogin(to, from, next);
      }
    } else if (to.matched.some(record => record.meta.guestOnly)) {
      if (isLoggedIn()) {
        gotoDashboard(to, from, next);
      } else {
        next();
      }
    }
  })


  return Router
})
