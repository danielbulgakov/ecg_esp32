// Логика popup
const popup = document.querySelector('.devices');
const popupCloseButton = document.querySelector('.devices__close-button');
const popupWrapper = document.querySelector('.devices__wrapper');

popupCloseButton.addEventListener('click', event => {
  popup.classList.remove('devices_show');
  // Отправляю запрос в главный поток о прекращении события
  cancelRequest();
  // Сбрасываю запомненные устройства
  currentDevices = [];
  // Очищаю эти устройства
  clearDeviceList();
});

popupWrapper.addEventListener('click', event => {
  if (event.target === popupWrapper) {
    popup.classList.remove('devices_show');
    // Отправляю запрос в главный поток о прекращении события
    cancelRequest();
    // Сбрасываю запомненные устройства
    currentDevices = [];
    // Очищаю эти устройства
    clearDeviceList();
  }
});

// Очистить лист
function clearDeviceList() {
  const deviceList = document.querySelector('.devices__list');
  console.log('Число элементов 1: ', deviceList.children.length);
  while (deviceList.children.length) {
    console.log('Число элементов: ', deviceList.children.length);
    // Info: remove удаляет само звено!
    deviceList.firstElementChild.remove()
  }
}

let currentDevices = [];

// Поменять лист доступных устройств
function changeDeviceList(devices) {
  // TODO: Было бы неплохо удалять отсюда элементы, которые не появляются долгое время
  // Создаёт новое устройство
  function createListItem(device) {
    const listItem = document.createElement('li');
    listItem.classList.add('devices__list-item');
    listItem.innerHTML = device.deviceName;
    listItem.addEventListener('click', event => {
      console.log('Параметры текущего создаваемого устройства: ', device, device.deviceId)
      window.electronAPI.acceptBluetoothRequest(device);
      popup.classList.remove('devices_show');
    });
    return listItem;
  }

  // Проверить есть ли устройство в моём массиве и если нет, но добавить его
  function makeUniqueList() {
    return devices.filter(device => {
      const result = currentDevices.find(currentDevice => {
        return currentDevice.deviceName === device.deviceName && currentDevice.deviceId === device.deviceId
      });

      if (!result) {
        currentDevices.push(device);
        return true;
      }
      return false
    })
  }

  console.log('Устройства ', devices);
  const deviceList = document.querySelector('.devices__list');
  console.log('Текущий массив: ', currentDevices)
  // Добавим уникальные значения
  makeUniqueList().forEach(currentDevice => {
    deviceList.append(createListItem(currentDevice));
  });
}

let connectedDevice;
const bleService = '4fafc201-1fb5-459e-8fcc-c5c9c331914b';

async function startFind () {
  window.electronAPI.getDeviceList((event, deviceList) => {
    // console.log(deviceList);
    changeDeviceList(deviceList);
  });
  // Показываем модалку
  popup.classList.add('devices_show');
  console.log('Осуществляю поиск устройсва');
  connectedDevice = await navigator.bluetooth.requestDevice({
    optionalServices: [bleService],
    acceptAllDevices: true
  })
  console.log('Устройство найдено!');
  document.getElementById('device-name').innerHTML = connectedDevice.name || `ID: ${connectedDevice.id}`;
  // Ищем сервисы и прочую шушару
  connection();
}

document.getElementById('find').addEventListener('click', startFind);

// Отправить ответ, что не выбрано устройство
function cancelRequest() {
  window.electronAPI.cancelBluetoothRequest()
}

document.getElementById('start').addEventListener('click', readDataFromDevice);

let gattCharacteristic;
// Функция запускается после успешного подклчюения к устройству
async function connection() {
  // Получаем сервер
  const server = await connectedDevice.gatt.connect();
  // Получаем нужный нам сервис
  const service = await server.getPrimaryService(bleService);
  // Получаем характеристики
  const characteristics = await service.getCharacteristics();
  gattCharacteristic = characteristics;
  // size
  gattCharacteristic[0].addEventListener('characteristicvaluechanged',
    handleSize);
  // package
  gattCharacteristic[1].addEventListener('characteristicvaluechanged',
    handlePackage);
  // data
  gattCharacteristic[2].addEventListener('characteristicvaluechanged',
    handleData);
  document.querySelector('#start').disabled = false
  document.querySelector('#stop').disabled = false
  console.log('Успешно выполнено!');
}

function handleSize(event) {
  console.log('Size пришла');
  const value = new Int16Array(event.target.value.buffer);
  outputSize.textContent = `Получены данные: ${value}`;

}

function handlePackage(event) {
  console.log('Package пришла');
  const value = new Int16Array(event.target.value.buffer);
  outputPackage.textContent = `Получены данные: ${value}`;
}

function handleData(event) {
  console.log('Data пришла', event.target.value.buffer);
  const value = new Int16Array(event.target.value.buffer);
  outputData.textContent = `Получены данные: ${value}`;
}

document.getElementById('start').addEventListener('click', readDataFromDevice);
document.getElementById('stop').addEventListener('click', stopDataFromDevice);

// Функция будет читать данные
function readDataFromDevice() {
  // size
  gattCharacteristic[0].startNotifications()
  .then(_ => {
    console.log('Start reading...')
    document.querySelector('#start').disabled = true
    document.querySelector('#stop').disabled = false
  })
  .catch(error => {
    console.log('[ERROR] Start: ' + error)
  })

  // package
  gattCharacteristic[1].startNotifications()
  .then(_ => {
    console.log('Start reading...')
    document.querySelector('#start').disabled = true
    document.querySelector('#stop').disabled = false
  })
  .catch(error => {
    console.log('[ERROR] Start: ' + error)
  })

  // data
  gattCharacteristic[2].startNotifications()
  .then(_ => {
    console.log('Start reading...')
    document.querySelector('#start').disabled = true
    document.querySelector('#stop').disabled = false
  })
  .catch(error => {
    console.log('[ERROR] Start: ' + error)
  })
}

// Функция отменяет чтение данных
function stopDataFromDevice() {
  // size
  gattCharacteristic[0].stopNotifications()
  .then(_ => {
    console.log('Stop reading...')
    document.querySelector('#start').disabled = false
    document.querySelector('#stop').disabled = true
  })
  .catch(error => {
    console.log('[ERROR] Stop: ' + error)
  })

  // package
  gattCharacteristic[1].stopNotifications()
  .then(_ => {
    console.log('Stop reading...')
    document.querySelector('#start').disabled = false
    document.querySelector('#stop').disabled = true
  })
  .catch(error => {
    console.log('[ERROR] Stop: ' + error)
  })

  // data
  gattCharacteristic[2].stopNotifications()
  .then(_ => {
    console.log('Stop reading...')
    document.querySelector('#start').disabled = false
    document.querySelector('#stop').disabled = true
  })
  .catch(error => {
    console.log('[ERROR] Stop: ' + error)
  })
}