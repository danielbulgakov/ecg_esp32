const MAX_PULSE_VALUE = 250;
const STEP_PULSE_CHART_DAY = 5;
// Массив для наполнения
const pulses = [];

function getRandomPulse() {
  return Math.floor(Math.random() * MAX_PULSE_VALUE);
}

function addMeasurementPulse() {
  for (let i = 0; i < 10; i++) {
    pulses.push(getRandomPulse());
  }
  return pulses;
}

export function renderMinutes(numberMinutes) {
  // Example: 60 -> 01:00
  const minutes = numberMinutes % 60;
  const hours = Math.floor(numberMinutes / 60);
  function renderTime(time) {
    return time >= 10 ? time : '0' + time;
  }
  return `${renderTime(hours)}:${renderTime(minutes)}`;
}

function makeLabels() {
  const NUMBER_MINUTES_IN_DAY = 24 * 60;
  const result = [];
  for (let i = 0; i < NUMBER_MINUTES_IN_DAY; i += STEP_PULSE_CHART_DAY) {
    result.push(renderMinutes(i));
    if (i + STEP_PULSE_CHART_DAY >= NUMBER_MINUTES_IN_DAY) {
      result.push(renderMinutes(NUMBER_MINUTES_IN_DAY - 1));
    }
  }
  return result;
}

export const chartData = () => {
  return {
    labels: makeLabels(),
    datasets: [
      {
        pointRadius: 0,
        borderCapStyle: 'round',
        label: 'Data pulse',
        borderColor: '#f87979',
        data: addMeasurementPulse()
      }
    ]
  }
};

// [] - Отобразить данные на графике за день
// [] - Величину интервала задавать const