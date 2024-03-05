<script setup>
import { Line } from 'vue-chartjs';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from 'chart.js';
import { onMounted, reactive, ref } from 'vue';
import axios from 'axios';
import { chartData } from '@/chartsConfig';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

const data = ref({
  datasets: [],
});
const chartOptions = reactive({
  responsive: true,
  scales: {
    x: {
      ticks: {
        autoSkip: true, // This will enable auto skipping of labels
        maxTicksLimit: 10, // Set the maximum number of ticks to show
      },
    },
  },
});

onMounted(async () => {
  // Пробую код из примера
  setInterval(() => {
    data.value = chartData();
  }, 1000);
  // try {
  //   const { data } = await axios.get('http://localhost:4002/data');
  // } catch (err) {
  //   console.error(err);
  // }
});
</script>

<template>
  <div class="main-container">
    <Line id="my-chart-id" :options="chartOptions" :data="data" />
  </div>
</template>

<style lang="scss" scoped>
.main-container {
  flex-grow: 1;
  padding: 20px;
}
</style>
<!-- [x] Добавить простенький график -->
<!-- [] Добавить линейный график -->
<!-- [] Попробовать сделать график интерактивным -->
