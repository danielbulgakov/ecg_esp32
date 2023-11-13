#ifndef CUSTOM_SERVER_CALLBACKS_HH
#define CUSTOM_SERVER_CALLBACKS_HH

#include <ble/ble_service_handler.hh>
#include <helpers/config.hh>

class CustomServerCallbacks : public BLEServerCallbacks {
   private:
    static bool deviceConnected;

    void onConnect(BLEServer* pServer) {
        log_i("BLE :: Device connected");
        deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer) {
        log_i("BLE :: disconnected");
        deviceConnected = false;
        reconnect(pServer);
    }

    void reconnect(BLEServer* pServer) {
        // reconnect endlessly
        while (!deviceConnected) {
            pServer->getAdvertising()->start();
            delay(100);
        }
    }

   public:
    static bool isConnected() { return deviceConnected; }
};

#endif  // CUSTOM_SERVER_CALLBACKS_HH