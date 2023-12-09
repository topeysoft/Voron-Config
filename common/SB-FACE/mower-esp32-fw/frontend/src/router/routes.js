
const routes = [
  {
    path: '/',
    component: () => import('layouts/AccessLayout.vue'),
    meta: {
      guestOnly: true
    },
    children: [
      { name: 'welcome', path: '', component: () => import('pages/Welcome.vue') },
      { name: 'login', path: '/login', component: () => import('pages/Login.vue') },
      { name: 'setup', path: '/setup', component: () => import('pages/Register.vue') },
      { name: 'register', path: '/register', component: () => import('pages/Register.vue') },
      // { path: '/ota', component: () => import('pages/OTA.vue') },
      // { path: '/control', component: () => import('pages/Control.vue') },
      // { path: '/about', component: () => import('pages/About.vue') },
    ],
  },
  {
    path: '/',
    component: () => import('layouts/MainLayout.vue'),
    meta: {
      requiresAuth: true
    },
    children: [
      {
        name: 'dashboard', path: '', component: () => import('pages/Index.vue')
      },
      { name: 'settings', path: '/settings', component: () => import('pages/Settings.vue') },
      { name: 'wifi', path: '/wifi', component: () => import('pages/Wifi.vue') },
      { name: 'ota', path: '/ota', component: () => import('pages/OTA.vue') },
      { name: 'control', path: '/control', component: () => import('pages/Control.vue') },
      { name: 'about', path: '/about', component: () => import('pages/About.vue') },
    ]
  },

  // Always leave this as last one,
  // but you can also remove it
  {
    path: '/:catchAll(.*)*',
    component: () => import('pages/Error404.vue')
  }
]

export default routes
