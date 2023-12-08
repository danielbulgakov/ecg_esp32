// vite.config.js
import path from 'path';

export default {
  build: {
    // outDir: path.resolve(__dirname, 'dist/renderer'), // Указываем путь к папке, где будет собран код
    emptyOutDir: true, // Очищаем outDir перед каждой сборкой
    rollupOptions: {
      input: {
        main: path.resolve(__dirname, 'renderer/index.html'), // Указываем путь к вашему HTML-файлу
      },
    },
  },
};