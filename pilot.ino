#include <ArduinoBLE.h>

// Define the service and characteristic UUIDs
const char* serviceUuid = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
const char* charUuid    = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";
const char* deviceName  = "L7161";

void setup() {
  // Begin serial communication
  Serial.begin(9600);
  
  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE. Restarting...");
    while (1);
  }
  
  Serial.println("BLE initialized. Scanning...");
  
  // Start scanning for peripherals
  BLE.scanForName(deviceName); 
}

void loop() {
  // Check for a peripheral
  BLEDevice peripheral = BLE.available();
  
  if (peripheral) {
    Serial.print("Found peripheral: ");
    Serial.println(peripheral.address());
    
    // Stop scanning
    BLE.stopScan();

    
    
    // Connect to the peripheral
    if (peripheral.connect()) {
      Serial.println("Connected to peripheral");

      Serial.print("Discover Attributes:");
      Serial.println(peripheral.discoverAttributes()); // For some reason always 0

      Serial.print("Discover Service:");
      Serial.println(peripheral.discoverService(serviceUuid));

      BLEService nusService = peripheral.service(serviceUuid);
      if (nusService) {
        Serial.print("Discovered Characteristics:");
        Serial.println(nusService.characteristicCount());
        if ( nusService.characteristicCount() ) {
          BLECharacteristic nusChar = nusService.characteristic(charUuid);

          if ( nusChar ) {
            Serial.println("Fully connect to the RX characterostics");

            while(1) {
              Serial.println("Waiting for input!");
              while (Serial.available() == 0) {}
              String colorHex = Serial.readString();

              Serial.print("Value: ");
              Serial.println(colorHex);

              byte r = (byte)strtol(colorHex.substring(0, 2).c_str(), NULL, 16);
              byte g = (byte)strtol(colorHex.substring(2, 4).c_str(), NULL, 16);
              byte b = (byte)strtol(colorHex.substring(4, 6).c_str(), NULL, 16);

              byte colorCommand[] = {0x55, 0x07, 0x00, r, g, b};
              nusChar.writeValue(colorCommand, sizeof(colorCommand));
              Serial.println("RGB data sent.");
            }
          }
        }
      }
      
      // Disconnect from the peripheral
      peripheral.disconnect();
    } else {
      Serial.println("Failed to connect to peripheral");
    }
    
    // Resume scanning
    Serial.println("Starting rescan..");
    BLE.scanForName(deviceName);
  }
}