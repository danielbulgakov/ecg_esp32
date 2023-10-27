import { arrayAxeX, arrayAxeY } from "./chartData.js";

const canvas = document.getElementById('myChart');
// Для возможности рисовать на холсте
const context = canvas.getContext('2d');
// График создаётся, когда произошло подключение к устройству
function createLineChart() { 
  const config = {
    type: 'line',
    data: {
      labels: [], // Массив для меток времени (X-ось)
      // Массив принимает массив объектов, так как может быть несколько графиков
      datasets: [{
        label: 'Graph of sin(x)',
        data: [],
        pointStyle: false
      }]
    },
    options: {
      plugins: {
        zoom: {
          pan: {
            enabled: true,
            mode: 'x',
          },
          zoom: {
            mode: 'x',
            pinch: {
              enabled: true
            },
            wheel: {
              enabled: true
            },
          }
        }
      },
      scales: {
        x: {
          type: 'linear',
          position: 'bottom'
        }
      }
    }
  };

  return new Chart(context, config);
}

// Мне нужно обновлять данные в реальном времени

export {
  createLineChart
}