const { app, BrowserWindow, ipcMain } = require('electron')
const path = require('path')

let selectBluetoothCallback

function createWindow (page) {
  const mainWindow = new BrowserWindow({
    width: 1000,
    height: 700,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      nodeIntegration: true,
      defaultEncoding: 'UTF-8', // Установите кодировку окна
    }
  })

  // В данном случае callback служит для поключения (вызывается каждый раз, когда найдено новое устройство)
  mainWindow.webContents.on('select-bluetooth-device', (event, deviceList, callback) => {
    console.log('Event select-bluetooth-device was triggered: ', event, deviceList);
    event.preventDefault()
    mainWindow.webContents.send("get-device-list", deviceList);
    console.log("Bluetooth device list dispatched.");
    selectBluetoothCallback = callback;
  });

  //cancels Discovery
  ipcMain.on('cancel-bluetooth-request', _ => {
    selectBluetoothCallback(''); //reference to callback of win.webContents.on('select-bluetooth-device'...)
    console.log("Discovery cancelled");
  });

  //resolves navigator.bluetooth.requestDevice() and stops device discovery
  ipcMain.on('accept-bluetooth-request', (event, device) => {
    selectBluetoothCallback(device.deviceId); //reference to callback of win.webContents.on('select-bluetooth-device'...)
    console.log("Device selected, discovery finished");
  });

  mainWindow.loadFile(`dist/renderer/auth.html`)
}

app.whenReady().then(() => {
  createWindow()

  app.on('activate', function () {
    if (BrowserWindow.getAllWindows().length === 0) createWindow()
  })
})

app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
})