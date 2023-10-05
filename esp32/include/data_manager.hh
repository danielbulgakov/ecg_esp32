#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

class DataManager {
   private:
    static DataManager* instance;
    bool deviceConnected;

    DataManager() : deviceConnected(false) {}

   public:
    // Functions to handle Singleton and events of connect/disconnect to device
    static DataManager* getInstance() {
        if (!instance) {
            instance = new DataManager();
        }
        return instance;
    }

    static void deviceIsConnected() { getInstance()->deviceConnected = true; }

    static void deviceIsDisconnected() { getInstance()->deviceConnected = false; }

    bool isDeviceConnected() { return deviceConnected; }
    // Main functions
    void PushData(uint16_t* arr, uint16_t num, uint16_t size) {
        if (deviceConnected) {
            
        }
    }

};

// Define static members of classes

DataManager* DataManager::instance = nullptr;

#endif  // DATA_MANAGER_H