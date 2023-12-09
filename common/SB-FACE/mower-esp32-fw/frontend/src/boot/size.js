import { format } from 'quasar'
const { humanStorageSize } = format
export default ({ app }) => {
  app.config.globalProperties.$size = humanStorageSize;
};
