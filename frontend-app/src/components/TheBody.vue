<script setup>
import { Bar } from 'vue-chartjs';
import {
  Chart as ChartJS,
  Title,
  Tooltip,
  Legend,
  BarElement,
  CategoryScale,
  LinearScale,
} from 'chart.js';
import { onMounted, reactive } from 'vue';
import axios from 'axios';

ChartJS.register(
  Title,
  Tooltip,
  Legend,
  BarElement,
  CategoryScale,
  LinearScale
);

const chartData = reactive({
  labels: ['January', 'February', 'March'],
  datasets: [{ data: [40, 20, 12] }],
});
const chartOptions = reactive({
  responsive: true,
});

onMounted(async () => {
  try {
    const { data } = await axios.get('http://localhost:4002/data');
  } catch (err) {
    console.error(err);
  }
});
</script>

<template>
  <div class="main-container">
    <Bar id="my-chart-id" :options="chartOptions" :data="chartData" />
  </div>
</template>

<style lang="scss" scoped>
.main-container {
  flex-grow: 1;
}
</style>
<!-- [x] Добавить простенький график -->
<!-- [] Попробовать сделать график интерактивным -->
