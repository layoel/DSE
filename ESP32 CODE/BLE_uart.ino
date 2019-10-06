/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE" 
   Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   In this example rxValue is the data received (only accessible inside that function).
   And txValue is the data to be sent, in this example just a byte incremented every second. 
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

//HardwareSerial UART(2);
bool enviado=false;
char c;
char buff[16]; int enviados=-1;
BLEServer *pServer = NULL;
BLECharacteristic * pCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

const int readPin = 32; // Use GPIO number. See ESP32 board pinouts<br>
const int LED = 2; // Could be different depending on the dev board. I used the DOIT ESP32 dev board.

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {

        for (int i = 0; i < rxValue.length(); i++){
          //Serial.println(rxValue[i]);
          
          if (rxValue[i] == 'A') {
             //Serial.print("BOTON A ON");
             if(enviado==false){
              buff[0]='A';
              enviados=0;
               enviado=true;
             }
          }
          else if (rxValue[i] == 'C') {
            //Serial.print("BOTON B ON");
             if(enviado==false){
               buff[0]='c';
               buff[1]=rxValue[i+1];
               buff[2]=rxValue[i+2];
               buff[3]=rxValue[i+3];
               buff[4]='C';
               enviados=4;
               enviado=true;}
          }
          else if (rxValue[i] == 'P') {
            //Serial.print("BOTON C ON");
             if(enviado==false){
              buff[0]='P';
              enviados=0;
               enviado=true;}
            //digitalWrite(LED, LOW);
          }
          else if (rxValue[i] == 'p') {
            //Serial.print("BOTON A OFF");
             if(enviado==false){
              buff[0]='p';
              enviados=0;
               enviado=true;}
            //digitalWrite(LED, LOW);
          }
          else if (rxValue[i] == 'T') {
            //Serial.print("BOTON B OFF");
             if(enviado==false){
               buff[0]='T';
              enviados=0;
               enviado=true;}
            //digitalWrite(LED, LOW);
          }
          else if (rxValue[i] == 't') {
            //Serial.print("BOTON C OFF");
             if(enviado==false){
              buff[0]='t';
              enviados=0;
               enviado=true;}
            //digitalWrite(LED, LOW);
          }
          else if (rxValue[i] == 'F') {
            //Serial.print("BOTON B OFF");
             if(enviado==false){
               buff[0]='f';
               buff[1]=rxValue[i+1];
               buff[2]=rxValue[i+2];
               buff[3]='F';
               enviados=3;
               enviado=true;}
            //digitalWrite(LED, LOW);
          }
         else if (rxValue[i] == 'N') {
            //Serial.print("BOTON B OFF");
             if(enviado==false){
               buff[0]='n';
               buff[1]=rxValue[i+1];
               buff[2]='N';
               enviados=2;
               enviado=true;}
            //digitalWrite(LED, LOW);
          }          
          else if (rxValue[i] == 'S') {
            //Serial.print("BOTON C OFF");
             if(enviado==false){
              Serial.write('S');
              enviados=-1;
               enviado=true;}
            //digitalWrite(LED, LOW);
          }

        //Serial.println();
       // Serial.println("*********");
      }}
    }
};


void setup() {
  Serial.begin(115200);
  //Serial.begin(115200,SERIAL_8N1,40,41);
  // Create the BLE Device
  BLEDevice::init("ESP32 ostia");
buff[1]=0;
buff[2]=0;
buff[3]=0;
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
										CHARACTERISTIC_UUID_TX,
										BLECharacteristic::PROPERTY_NOTIFY
									);
                      
  pCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pCharacteristic = pService->createCharacteristic(
											 CHARACTERISTIC_UUID_RX,
											BLECharacteristic::PROPERTY_WRITE
										);

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  //Serial.println("Waiting a client connection to notify...");
}

void loop() {

    if (deviceConnected) {

       //    pCharacteristic->setValue(&txValue, 1); // To send the integer value
        //pCharacteristic->setValue(txString);
        pCharacteristic->notify();
        if(enviado==true){
            int contador=0;
            while(enviados!=-1){
              Serial.write(buff[enviados]);
              delay(1000);
              c=Serial.read();
              contador++;
              if(c=='A'){
                enviados--;
                contador=0;
            }
              if(enviados==-1){
                 pCharacteristic->setValue("A"); // Sending a test message
              }
              if(contador==4)          // 1 segundo
                enviados=-1;

              c=-1;
            }
              enviado=false;
             
            
            c=-1;
            
        }
        
    //Serial.print("*** Sent Value: ");
    //Serial.print(txString);
    //Serial.println(" ***");
		delay(1000); // bluetooth stack will go into congestion, if too many packets are sent
	
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        //Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
		// do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
