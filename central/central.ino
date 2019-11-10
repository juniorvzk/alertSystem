#include <BLEDevice.h>
#include <WiFi.h>
#include <HTTPClient.h>

// The remote service we wish to connect to.
static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");


int countConnected = 0;
int countToConnect = 0;

// WIFI CREDENTIALS
const char* ssid = "My ASUS"; 
const char* password = "12344321";

// Server 
String serverURL = "http://35.239.9.88:1337/";

// Address and Client for each peripheral found. Considering max number of peripherals equals 10
BLEAddress* serversAddress[10];
BLEClient*  clients[10];

boolean connected = false;
BLERemoteCharacteristic* pRemoteCharacteristic;

// Called on any peripheral notification 
static void notifyCallback( BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

  Serial.printf("Received Value: %s \n",(char*) pData);

   if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    HTTPClient http;

    http.begin( serverURL+"alerts" );             //Specify destination for HTTP request
    http.addHeader("Content-Type", "text/plain");             //Specify content-type header

    int httpResponseCode = http.POST( (char*) pData );        //Send the actual POST request

    if( httpResponseCode > 0 ) {

     String response = http.getString();                       //Get the response to the request

     // Serial.println(httpResponseCode);   //Print return code
     // Serial.println(response);           //Print request answer

    } else {
     Serial.print("Error on sending POST: ");
     Serial.println(httpResponseCode);
    }
    http.end();  //Free resources
  } else {
     Serial.println("Error in WiFi connection");
  }
}
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  /**
  * Called for each advertising BLE device.
  */
  void onResult(BLEAdvertisedDevice advertisedDevice) {

    BLEClient* pClient;
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)) { // Found our peripheral
    
      if ( connected ) {      
        Serial.println("[connected] Found new devices - Refreshing ... ");
        delay(500);
        ESP.restart();
      } else {
        Serial.print("[!connected]BLE Advertised Device found: ");
        Serial.println(advertisedDevice.toString().c_str());

        pClient  = BLEDevice::createClient();
        serversAddress[countToConnect] = new BLEAddress( advertisedDevice.getAddress() );
        Serial.printf("- added Address[%d] ", countToConnect);

        clients[countToConnect] = pClient;
        Serial.printf("- added Client[%d] \n", countToConnect);

        countToConnect++;
      }
    } // Found our peripheral
  } // onResult
}; // MyAdvertisedDeviceCallbacks

void setup() {

  Serial.begin(9600);
  delay(4000);   //Delay needed before calling the WiFi.begin

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  
  BLEDevice::init("ESP32");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
}

int countLoop = 0;

void conectarPerifericos(){
  BLEAddress* deviceAddress;
  BLERemoteService* pRemoteService;
  BLEClient*  pClient;

  Serial.printf("Found %d device(s) during scan...\n", countToConnect );

  for (size_t i = 0; i < countToConnect; i++) {
    pClient  = clients[i];
    deviceAddress = serversAddress[i];

    Serial.print("Connecting to ");
    Serial.println( deviceAddress->toString().c_str());
    pClient->connect( *deviceAddress );
    Serial.println(" - Connected to server");
    pRemoteService = pClient->getService(serviceUUID);

    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      connected = false;
    }
    Serial.println(" - Found our service");

    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      connected = false;
    }
    Serial.println(" - Found our characteristic");

    pRemoteCharacteristic->registerForNotify(notifyCallback);
    Serial.println(" - Registered For Notify");

    countConnected++;
  }

  if (countConnected == countToConnect) {
    Serial.println("Connected successfully to all devices.");
    connected = true;
  } else {
    Serial.println("Could not connect to all devices.");
    connected = false;
  }
}

void loop() {
  Serial.printf("\n\nLoop: %d\n", countLoop);

  // Scan for devices
  BLEDevice::getScan()->start(15);

  if( !connected && countToConnect > 0 ){
    conectarPerifericos();
  }

   if ( connected ) {
     Serial.printf("Connected to %d devices\n", countConnected);
   }
   countLoop++;
   delay(2000);
}
