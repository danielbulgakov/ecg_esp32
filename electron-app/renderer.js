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
  // Сбрасываю флаг обновления списка устройств
  resetUpdateListDeviceFlag();
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
    // Сбрасываю флаг обновления списка устройств
    resetUpdateListDeviceFlag();
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
let isUpdateListDevices = null;
const secondPerUpdate = 10;

// Если произошло выключение окна выбора устройства, то нужно сбросить isUpdateListDevices
function resetUpdateListDeviceFlag() {
  isUpdateListDevices = null;
}

// Поменять лист доступных устройств
function changeDeviceList(devices) {
  // Логика удаления отсюда элементов, которые не появляются долгое время
  if (!isUpdateListDevices) {
    isUpdateListDevices = setTimeout(() => {
      console.log('Devices length: ', devices.length);
      if (devices.length) {
        // Нужно сравнить текущие devices с теми что запомнили
        // Для начала посмотрим на них через console.log
        console.log('Те устройства, что сейчас есть: ', currentDevices);
        console.log('Те устройства, что пришли: ', devices);
        // TODO: Можно, конечно, сделать иначе (фильтрануть и удалить только нужные звенья, но пускай пока так)
        // TODO: Так же, вместо, setTimeout можно использовать setInterval
        currentDevices = devices;
        clearDeviceList();
        currentDevices.forEach(currentDevice => {
          deviceList.append(createListItem(currentDevice));
        });
      }


      // Сбрасываю флаг обновления списка устройств
      resetUpdateListDeviceFlag();
    }, secondPerUpdate * 1000);
  }
  
  // Создаёт новое устройство
  function createListItem(device) {
    const listItem = document.createElement('li');
    listItem.classList.add('devices__list-item');
    listItem.innerHTML = device.deviceName;
    listItem.addEventListener('click', event => {
      console.log('Параметры текущего создаваемого устройства: ', device, device.deviceId)
      window.electronAPI.acceptBluetoothRequest(device);
      popup.classList.remove('devices_show');
      // Сбрасываю флаг обновления списка устройств
      resetUpdateListDeviceFlag();
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

  // console.log('Устройства ', devices);
  const deviceList = document.querySelector('.devices__list');
  // console.log('Текущий массив: ', currentDevices)
  // Добавим уникальные значения
  makeUniqueList().forEach(currentDevice => {
    deviceList.append(createListItem(currentDevice));
  });
}

let connectedDevice;
const bleService = '17b5290c-2e8b-11ed-a261-0242ac120002';

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
  // x
  gattCharacteristic[0].addEventListener('characteristicvaluechanged',
    handleChangedValueX);
  // y
  gattCharacteristic[1].addEventListener('characteristicvaluechanged',
    handleChangedValueY);
  document.querySelector('#start').disabled = false
  document.querySelector('#stop').disabled = false
  console.log('Успешно выполнено!');
}

// Функция для чтения x
function handleChangedValueX(event) {
  // Массив значений по x
  let value = new Float32Array(event.target.value.buffer);
  outputX.textContent = `Получены данные: ${value}`;
  var now = new Date()
  console.log('> ' + now.getHours() + ':' + now.getMinutes() + ':' + now.getSeconds() + ' UV Index is ', value)
}

// Функция для чтения y
function handleChangedValueY(event) {
  // Функция для преобразования пакета
  function bytesToString(arraysBytes) {
    return new TextDecoder().decode(arraysBytes);
  }
  const buffer = event.target.value.buffer;
  // Массив значений по x
  const startMessage = new Int8Array(buffer.slice(0, 8));
  const packNumber = new Int32Array(buffer.slice(8, 12));
  const numberUMV = new Int16Array(buffer.slice(12, 14));
  const startBracket = new Int8Array(buffer.slice(14, 15));
  console.log(buffer.slice(15, 414));
  const data = new Float32Array(buffer.slice(15, 415));
  const endBracket = new Int8Array(buffer.slice(415, 416));
  
  const stringValue = bytesToString(startMessage);
  const stringStartBracket = bytesToString(startBracket);
  const stringEndBracket = bytesToString(endBracket);
  console.log('Start message', stringValue);
  console.log('Number pack: ', packNumber);
  console.log('Number UMV: ', numberUMV);
  console.log('Start bracket: ', stringStartBracket);
  console.log('Number UMV: ', data);
  console.log('End bracket: ', stringEndBracket);


  outputY.textContent = `Получены данные: ${stringValue}, ${packNumber[0]}, ${numberUMV}, ${stringStartBracket}\n${data}\n${stringEndBracket}`;
  // var now = new Date()
  // console.log('> ' + now.getHours() + ':' + now.getMinutes() + ':' + now.getSeconds() + ' UV Index is ', value)
}

document.getElementById('start').addEventListener('click', readDataFromDevice);
document.getElementById('stop').addEventListener('click', stopDataFromDevice);

// Функция будет читать данные
function readDataFromDevice() {
  // x
  gattCharacteristic[0].startNotifications()
  .then(_ => {
    console.log('Start reading...')
    document.querySelector('#start').disabled = true
    document.querySelector('#stop').disabled = false
  })
  .catch(error => {
    console.log('[ERROR] Start: ' + error)
  })

  // y
  gattCharacteristic[1].startNotifications()
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
  gattCharacteristic[0].stopNotifications()
  .then(_ => {
    console.log('Stop reading...')
    document.querySelector('#start').disabled = false
    document.querySelector('#stop').disabled = true
  })
  .catch(error => {
    console.log('[ERROR] Stop: ' + error)
  })

  // y
  gattCharacteristic[1].stopNotifications()
  .then(_ => {
    console.log('Stop reading...')
    document.querySelector('#start').disabled = false
    document.querySelector('#stop').disabled = true
  })
  .catch(error => {
    console.log('[ERROR] Stop: ' + error)
  })
}