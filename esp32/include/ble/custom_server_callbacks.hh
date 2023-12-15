#ifndef CUSTOM_SERVER_CALLBACKS_HH
#define CUSTOM_SERVER_CALLBACKS_HH

#include <helpers/config.hh>
#include <ble/ble_service_handler.hh>

class CustomServerCallbacks : public BLEServerCallbacks {
   private:
    static bool deviceConnected;

    inline void onConnect(BLEServer* pServer) {
        log_i("BLE :: Device connected");
        deviceConnected = true;
    }

    inline void onDisconnect(BLEServer* pServer) {
        log_i("BLE :: disconnected");
        deviceConnected = false;
        reconnect(pServer);
    }

    inline void reconnect(BLEServer* pServer) {
        // reconnect endlessly
        while (!deviceConnected) {
            pServer->getAdvertising()->start();
            delay(100);
        }
    }

   public:
    static inline bool isConnected() { return deviceConnected; }
};

bool CustomServerCallbacks::deviceConnected = false;

#endif  // CUSTOM_SERVER_CALLBACKS_HH