// Including all external lib
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <ModbusMaster.h>
#include <ArduinoJson.h>

// Including HTML PAGE
#include "webpage.h"

// Defining UART PINS for MODBUS Receiver
#define RXD_PIN 21
#define TXD_PIN 22

// Max adress up to find
#define MAX_ADDRESS 5 

// Maximum registers to be read at once
#define MAX_REG_VALUES 20

// Defining an array containing all possible baudrates. 
const int32_t baudsBuffer[2] = {9600, 19200};


// WiFi Credentials
const char* ssid = "UAB";
const char* password = "";

// Booleans for starting searching 
bool findIDs = false;
bool readRegisters = false;

// Defining a struct for found MB device
struct deviceMB{
  uint8_t ID;
  uint32_t BAUDRATE;
};

struct searchConfig{
  uint8_t startAdd;
  uint8_t endAdd;
};

// Defining a struct for reading MB device
struct deviceConfig{
  uint8_t ID, QUANT, OPT; 
  uint16_t STARTADD;
  uint32_t BAUDRATE;
};
// Array to store discovered devices
deviceMB discoveredDevice[10];

// Modbus instance
ModbusMaster node;

searchConfig webDevice;

// Modbus configuration
deviceConfig mbConfig;

// Server instance on port 80
AsyncWebServer server(80);

// Websocket instance on /websocket location (the same as in webpage.h)
AsyncWebSocket websocket("/websocket");

// Declarations of used functions
void searchAvailableIDs(uint8_t start, uint8_t end,int16_t startRegisterAddress, int8_t quantity);
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void searchRegisters(uint8_t deviceID, uint32_t baudRate, uint16_t startRegisterAddress, uint8_t quantity, uint8_t opt);
void wifiConnect();

