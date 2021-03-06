
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Ultrasonic.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define pTrigger 2
#define pEcho 4

Ultrasonic ultrasonic(pTrigger, pEcho);


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Disconnected");
    }
};



void setup() {
  Serial.begin(9600);

  // Create the BLE Device
  BLEDevice::init("ESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

String sensorType = "{\"sensorType\":\"distancia\",\"value\":\"";
std::string data;
float distCM = 0;
float lastDistCM = 0;

long microsec = 0;
unsigned long measuredAt;

void loop() {
  microsec = ultrasonic.timing();
  distCM = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  if ( distCM != lastDistCM ){
    measuredAt = millis();
    // Serial.printf("[%s]Distancia em cm: %d", measuredAt, distCM);
    data = (sensorType+distCM+"\",\"measuredAt\":\""+measuredAt+"\"}").c_str();
    Serial.printf("Distancia: %f \n", distCM);
    pCharacteristic->setValue(data);
    pCharacteristic->notify();
    lastDistCM = distCM;
    delay(2000);
    /* code */
  }

}
