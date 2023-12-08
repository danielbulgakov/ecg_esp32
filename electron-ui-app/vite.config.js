// vite.config.js
import path from 'path';

export default {
  base: './', // Указываем относительный путь, относительно index.html
  build: {
    emptyOutDir: true, // Очищаем outDir перед каждой сборкой
    rollupOptions: {
      input: {
        main: path.resolve(__dirname, 'renderer/index.html'), // Указываем путь к вашему HTML-файлу
      },
    },
  },
};