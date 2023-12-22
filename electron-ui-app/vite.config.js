// vite.config.js
import path from 'path';

export default {
  base: './', // Указываем относительный путь, относительно index.html
  build: {
    emptyOutDir: true, // Очищаем outDir перед каждой сборкой
    rollupOptions: {
      input: {
        auth: path.resolve(__dirname, 'renderer/auth.html'), // Указываем путь к вашему HTML-файлу
        main: path.resolve(__dirname, 'renderer/index.html')
      },
    },
  },
};