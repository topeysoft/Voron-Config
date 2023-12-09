import { date } from 'quasar';

export default ({ app }) => {
  app.config.globalProperties.$date = date;
  app.config.globalProperties.$formatDate = date.formatDate;
};
