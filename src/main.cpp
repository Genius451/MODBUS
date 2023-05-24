#include "definitions.h"

void setup() {
  Serial.begin(115200);

  Serial.println("Initializing device");

  wifiConnect();
  //searchAvailableIDs(24,27, 0,2);
}

void loop() {

  if(findIDs){
    searchAvailableIDs(webDevice.startAdd, webDevice.endAdd, 0, 2);
  }

  if(readRegisters){
    searchRegisters(mbConfig.ID, mbConfig.BAUDRATE, mbConfig.STARTADD, mbConfig.QUANT, mbConfig.OPT);
  }        
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.println("WebSocket client connected");
      break;
    case WS_EVT_DISCONNECT:
      Serial.println("WebSocket client disconnected");
      break;
    case WS_EVT_DATA:
      Serial.println("WebSocket data received: " + String((char*) data));

      String result = (char*) data;

      if(result.indexOf("scanID") != -1){
        Serial.println("Scanning for IDs");
        findIDs = true;

        char *p;

        p = strtok((char*)data, ";");
        String buff[6];
        uint8_t i = 0;

        while (p != NULL) {
          buff[i] = p;
          p = strtok(NULL, ";");
          i++;
        }
        webDevice.startAdd = buff[1].toInt();
        webDevice.endAdd = buff[2].toInt();
      }

      if(result.indexOf("scanRegs") != -1){
        Serial.println("Scanning for Regs");
        char *p;

        p = strtok((char*)data, ";");
        String buff[6];
        uint8_t i = 0;

        while (p != NULL) {
          buff[i] = p;
          p = strtok(NULL, ";");
          i++;
        }
        mbConfig.ID = buff[1].toInt();
        mbConfig.BAUDRATE = buff[2].toInt();
        mbConfig.STARTADD = buff[3].toInt();
        mbConfig.QUANT = buff[4].toInt();
        mbConfig.OPT = buff[5].toInt();
        readRegisters = true;
       
      }
      break;
  }
}

void searchAvailableIDs(uint8_t start, uint8_t end,int16_t startRegisterAddress, int8_t quantity){
  
  findIDs = false;
  uint8_t indexofDevice = 0;
  
  Serial.println("Starting scanning");

  for(int j=0; j < sizeof(baudsBuffer) / sizeof (uint32_t); j++){

    Serial2.begin(baudsBuffer[j], SERIAL_8N1, RXD_PIN, TXD_PIN);
  
    for(int i=start; i <= end; i++){
      node.begin(i, Serial2);
    
      uint8_t result = node.readHoldingRegisters(0,2);
      if (result == node.ku8MBSuccess) {
          Serial.print("Device found at:");
          Serial.println(i);
          discoveredDevice[indexofDevice].ID = i;
          discoveredDevice[indexofDevice].BAUDRATE = baudsBuffer[j];
          indexofDevice++;
          delay(200);
      }
    }
  
    Serial2.end();
    delay(100);
  }

  StaticJsonDocument<500> doc;
  doc[0]["iden"] = "ids";

  if(indexofDevice > 0){
    doc[1]["err"] = 0;
  }

  else{
    doc[1]["err"] = -1;
  }

  JsonObject name = doc.createNestedObject();

  String output;
  for(uint8_t i = 0; i < indexofDevice; i++){
    Serial.print(i);
    String iden = "dev" + (String)i;
    char buffer[40];
    sprintf(buffer, "%u;%u",discoveredDevice[i].ID, discoveredDevice[i].BAUDRATE);
    Serial.println(buffer);
    name[iden] = (String) buffer;
}

  serializeJson(doc, output);
 
  websocket.textAll(output);
  Serial.println(output);
  Serial.println("Finished");
  
}

void searchRegisters(uint8_t deviceID, uint32_t baudRate, uint16_t startRegisterAddress, uint8_t quantity, uint8_t opt){
  readRegisters = false;
  // starting the 2nd Hardware Serial.
  Serial2.begin(baudRate, SERIAL_8N1, RXD_PIN, TXD_PIN);
  // Starting the Modbus Communication
  node.begin(deviceID, Serial2);

  int16_t resultBuffer[quantity];

  

  StaticJsonDocument<500> doc;
  doc[0]["iden"] = "regs";
  doc[1]["err"] = 0;
      
  JsonObject doc_0 = doc.createNestedObject();
  String output = "";

  if(quantity <= MAX_REG_VALUES){

     uint8_t resultData;
    if(opt == 1 ){
       resultData = node.readInputRegisters(startRegisterAddress, quantity);
    }

    if(opt == 0 ){
       resultData = node.readHoldingRegisters(startRegisterAddress, quantity);
    }


    if(resultData == node.ku8MBSuccess){

      // reading all values
      for(uint8_t i = 0; i < quantity; i++){
        resultBuffer[i] = node.getResponseBuffer(i);
        String name = "val" + (String)i;
        doc_0[name] = resultBuffer[i];
      }

      doc[1]["err"] = 0;
      
      
    }
    else{
      Serial.println("Error reading");
      doc[1]["err"] = -1;
    }
  }
  else{
      Serial.println("Reduce the number of registers.");
      doc[1]["err"] = -2;
  }
  serializeJson(doc, output);
  Serial.println(output);
  websocket.textAll(output);
}

void wifiConnect(){
   // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi, please browse to: ");
  Serial.println(WiFi.localIP());

  // Route for homepage
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", web);
  });

  // WebSocket handler
  websocket.onEvent(onWsEvent);
  server.addHandler(&websocket);

  server.begin();
}