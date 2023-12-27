//#define MODULE_4AMP_1VOLT
#define MODULE_SWITCH_4

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include "../../jeepify.h"
#include <ArduinoJson.h>
#include <Preferences.h>
#include <Wire.h>
#include <Spi.h>

#ifdef ESP32
  #include <esp_now.h>
  #include <WiFi.h>
  #define D5 14
  #define D6 12
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <espnow.h>
#endif  // ESP32

#define NODE_NAME "Jeep_V2-SW"
#define VERSION   "V 0.51"

#ifdef MODULE_SWITCH_4
  #define NODE_TYPE SWITCH_4_WAY
 
  #define NAME_SENSOR_0 "SW-0"
  #define TYPE_SENSOR_0  SENS_TYPE_SWITCH
  #define IOPORT_0       1
  
  #define NAME_SENSOR_1 "SW-1"
  #define TYPE_SENSOR_1  SENS_TYPE_SWITCH
  #define IOPORT_1       2
  
  #define NAME_SENSOR_2 "SW-2"
  #define TYPE_SENSOR_2  SENS_TYPE_SWITCH
  #define IOPORT_2       3
  
  #define NAME_SENSOR_3 "SW-3"
  #define TYPE_SENSOR_3  SENS_TYPE_SWITCH
  #define IOPORT_3       4
  
#endif

#ifdef MODULE_4AMP_1VOLT
  #define NODE_TYPE BATTERY_SENSOR
  
  #define NAME_SENSOR_0 "v2-0"
  #define TYPE_SENSOR_0  SENS_TYPE_AMP
  #define NULL_SENSOR_0  3134
  #define SENS_SENSOR_0  0.066

  #define NAME_SENSOR_1 "v2-1"
  #define TYPE_SENSOR_1  SENS_TYPE_AMP
  #define NULL_SENSOR_1  3134
  #define SENS_SENSOR_1  0.066
  
  #define NAME_SENSOR_2 "v2-2"
  #define TYPE_SENSOR_2  SENS_TYPE_AMP
  #define NULL_SENSOR_2  3150
  #define SENS_SENSOR_2  0.066

  #define NAME_SENSOR_3 "v2-3"
  #define TYPE_SENSOR_3  SENS_TYPE_AMP
  #define NULL_SENSOR_3  3150
  #define SENS_SENSOR_3  0.066

  #define NAME_SENSOR_4  "v2-Volt"
  #define TYPE_SENSOR_4  SENS_TYPE_VOLT
  #define VIN_SENSOR_4   200

  #define IOPORT_4       5
#endif

//Adafruit_ADS1115 ads;

RTC_DATA_ATTR struct_Periph S[MAX_PERIPHERALS];
struct_Peer   P[MAX_PEERS];

struct_Touch Touch;

StaticJsonDocument<500> doc;
String jsondata;

struct struct_Status {
  String    Msg;
  uint32_t  TSMsg;
};

struct_Status Status[MAX_STATUS];
u_int8_t TempBroadcast[6];

int PeerCount = 0;

bool Debug         = true;
bool SleepMode     = false;
bool ReadyToPair   = false;

int  Mode          = S_STATUS;
int  OldMode       = 0;

uint32_t TSLastSend    = 0;
uint32_t TSLastContact = 0;
uint32_t TSSend = 0;
uint32_t TSPair = 0;

Preferences preferences;

float  ReadAmp (int A);
float  ReadVolt(int V);
void   SendMessage();
void   SendPairingRequest();

#ifdef ESP32 
    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  #elif defined(ESP8266)
    void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);
    void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);
#endif  // ESP32

void   InitModule();
void   SavePeers();
void   GetPeers();
void   ReportPeers();
void   RegisterPeers();
void   ClearPeers();
void   ClearInit();

void   ShowPairingScreen();
void   ShowEichen();
void   ShowVoltCalib(float V);
void   UpdateSwitches();

void   SetSleepMode(bool Mode);
void   SetDebugMode(bool Mode);
void   AddStatus(String Msg);
void   ShowStatus();

void   Eichen();
void   PrintMAC(const uint8_t * mac_addr);

bool   isPeerEmpty(int PNr);
bool   isSensorEmpty(int SNr);
void   GoToSleep();


void InitModule() {
  preferences.begin("JeepifyInit", true);
  Debug     = preferences.getBool("Debug", true);
  SleepMode = preferences.getBool("SleepMode", false);
  preferences.end();

  //for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) S[SNr].Type = 0;

  
#ifdef NAME_SENSOR_0
    strcpy(S[0].Name, NAME_SENSOR_0);
    S[0].Type     = TYPE_SENSOR_0;
    S[0].IOPort   = IOPORT_0;
    
    #ifdef NULL_SENSOR_0
      S[0].NullWert = NULL_SENSOR_0;
    #endif
    
    #ifdef SENS_SENSOR_0
      S[0].VperAmp  = SENS_SENSOR_0;
    #endif
    
    #ifdef VIN_SENSOR_0
      S[0].Vin = VIN_SENSOR_0;
    #endif 
#endif

#ifdef NAME_SENSOR_1
    strcpy(S[1].Name, NAME_SENSOR_1);
    S[1].Type     = TYPE_SENSOR_1;
    S[1].IOPort   = IOPORT_1;

    #ifdef NULL_SENSOR_1 
      S[1].NullWert = NULL_SENSOR_1;
    #endif
    
    #ifdef SENS_SENSOR_1
      S[1].VperAmp  = SENS_SENSOR_1;
    #endif
    
    #ifdef VIN_SENSOR_1
      S[1].Vin = VIN_SENSOR_1;
    #endif
#endif

#ifdef NAME_SENSOR_2
    strcpy(S[2].Name, NAME_SENSOR_2);
    S[2].Type     = TYPE_SENSOR_2;
    S[2].IOPort   = IOPORT_2;

    #ifdef NULL_SENSOR_2 
      S[2].NullWert = NULL_SENSOR_2;
    #endif
    
    #ifdef SENS_SENSOR_2
      S[2].VperAmp  = SENS_SENSOR_2;
    #endif
    
    #ifdef VIN_SENSOR_2
      S[2].Vin = VIN_SENSOR_2;
    #endif
#endif

#ifdef NAME_SENSOR_3
    strcpy(S[3].Name, NAME_SENSOR_3);
    S[3].Type     = TYPE_SENSOR_3;
    S[3].IOPort   = IOPORT_3;

    #ifdef NULL_SENSOR_3 
      S[3].NullWert = NULL_SENSOR_3;
    #endif
    
    #ifdef SENS_SENSOR_3
      S[3].VperAmp  = SENS_SENSOR_3;
    #endif
    
    #ifdef VIN_SENSOR_3
      S[3].Vin = VIN_SENSOR_3;
    #endif
#endif

#ifdef NAME_SENSOR_4
    strcpy(S[4].Name, NAME_SENSOR_4);
    S[4].Type     = TYPE_SENSOR_4;
    S[4].IOPort   = IOPORT_4;

    #ifdef NULL_SENSOR_4 
      S[4].NullWert = NULL_SENSOR_4;
    #endif
    
    #ifdef SENS_SENSOR_4
      S[4].VperAmp  = SENS_SENSOR_4;
    #endif
    
    #ifdef VIN_SENSOR_4
      S[4].Vin = VIN_SENSOR_4;
    #endif
#endif

#ifdef NAME_SENSOR_5
    strcpy(S[5].Name, NAME_SENSOR_5);
    S[5].Type     = TYPE_SENSOR_5;
    S[5].IOPort   = IOPORT_5;

    #ifdef NULL_SENSOR_5 
      S[5].NullWert = NULL_SENSOR_5;
    #endif
    
    #ifdef SENS_SENSOR_5
      S[5].VperAmp  = SENS_SENSOR_5;
    #endif
    
    #ifdef VIN_SENSOR_5
      S[5].Vin = VIN_SENSOR_5;
    #endif 
#endif

#ifdef NAME_SENSOR_6
    strcpy(S[6].Name, NAME_SENSOR_6);
    S[6].Type     = TYPE_SENSOR_6;
    S[6].IOPort   = IOPORT_6;

    #ifdef NULL_SENSOR_6 
      S[6].NullWert = NULL_SENSOR_6;
    #endif
    
    #ifdef SENS_SENSOR_6
      S[6].VperAmp  = SENS_SENSOR_6;
    #endif
    
    #ifdef VIN_SENSOR_6
      S[6].Vin = VIN_SENSOR_6;
    #endif
#endif

#ifdef NAME_SENSOR_7
    strcpy(S[7].Name, NAME_SENSOR_7);
    S[7].Type     = TYPE_SENSOR_7;
    S[7].IOPort   = IOPORT_7;

    #ifdef NULL_SENSOR_7 
      S[7].NullWert = NULL_SENSOR_7;
    #endif
    
    #ifdef SENS_SENSOR_7
      S[7].VperAmp  = SENS_SENSOR_7;
    #endif
    
    #ifdef VIN_SENSOR_7
      S[7].Vin = VIN_SENSOR_7;
    #endif 
#endif

  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++)  {
    switch (S[SNr].Type) {
      case SENS_TYPE_SWITCH: pinMode(S[SNr].IOPort, OUTPUT); break;
      case SENS_TYPE_VOLT:   pinMode(S[SNr].IOPort, INPUT ); break;
      case SENS_TYPE_AMP:    pinMode(S[SNr].IOPort, INPUT ); break;
    }
  }
  
  Serial.println("InitModule() fertig...");
}
void SavePeers() {
  // Speichert alle bekannten Peers
  // Type-0 (int)
  // Name-0 (String)
  // MAC-0  (6 Bytes)

  Serial.println("SavePeers...");
  preferences.begin("JeepifyPeers", false);
  preferences.clear();
  
  char Buf[50] = {}; String BufS;

  PeerCount = 0;

  for (int Pi=0; Pi< MAX_PEERS; Pi++) {                         
    if (!isPeerEmpty(Pi)) {
      PeerCount++;
      //P.Type...
      sprintf(Buf, "Type-%d", Pi); 
      preferences.putInt(Buf, P[Pi].Type);
      Serial.print("schreibe "); Serial.print(Buf); Serial.print(" = "); Serial.println(P[Pi].Type);

      //P.Name
      sprintf(Buf, "Name-%d", Pi); 
      BufS = P[Pi].Name;
      preferences.putString(Buf, BufS);
      Serial.print("schreibe "); Serial.print(Buf); Serial.print(" = "); Serial.println(BufS);
      
      //P.BroadcastAdress
      sprintf(Buf, "MAC-%d", Pi); 
      preferences.putBytes(Buf, P[Pi].BroadcastAddress, 6);
      Serial.print(Buf); Serial.print("="); PrintMAC(P[Pi].BroadcastAddress); Serial.println();
    }
  }
  preferences.putInt("PeerCount", PeerCount);

  preferences.end();
}
void GetPeers() {
  // liest alle nicht leeren (Type>0) bekannten Peers
  // Type-0 (int)
  // Name-0 (String)
  // MAC-0  (6 Bytes)

  preferences.begin("JeepifyPeers", true);
  
  char Buf[50] = {}; String BufS;
  
  PeerCount = 0;
  for (int Pi=0; Pi<MAX_PEERS; Pi++) {
  
    // Peer gefüllt?
    sprintf(Buf, "Type-%d", Pi); 
    if (preferences.getInt(Buf,0) > 0) {
      PeerCount++;

      // Type-0
      sprintf(Buf, "Type-%d", Pi); 
      P[Pi].Type = preferences.getInt(Buf);
      
      // Name-0
      sprintf(Buf, "Name-%d", Pi); 
      BufS = preferences.getString(Buf);
      strcpy(P[Pi].Name, BufS.c_str());
      
      // MAC-0
      sprintf(Buf, "MAC-%d", Pi); 
      preferences.getBytes(Buf, P[Pi].BroadcastAddress, 6);
      
      P[Pi].TSLastSeen = millis();

      if (Debug) {
        Serial.print("GetPeers: P["); Serial.print(Pi); Serial.print("]: Type="); Serial.print(P[Pi].Type); 
        Serial.print(", Name="); Serial.print(P[Pi].Name);
        Serial.print(", MAC="); PrintMAC(P[Pi].BroadcastAddress); Serial.println();
      }
    }
  }
  preferences.end();
}
void ReportPeers() {
  char Buf[200];
  Serial.println("Report-Peers:");
  for (int PNr=0; PNr<MAX_PEERS; PNr++) {
    if (Debug) {
      sprintf(Buf, "%s (Type: %d) - MAC:", P[PNr].Name, P[PNr].Type);
      Serial.print(Buf); PrintMAC(P[PNr].BroadcastAddress);
      Serial.println();
    }
  }
}
void RegisterPeers() {
  // Register BROADCAST ESP32
  #ifdef ESP32
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 1;
    peerInfo.encrypt = false;
    memset(&peerInfo, 0, sizeof(peerInfo));
    
    for (int b=0; b<6; b++) peerInfo.peer_addr[b] = (uint8_t) broadcastAddressAll[b];
      if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
      }
      else {
        Serial.print (" ("); PrintMAC(peerInfo.peer_addr);  Serial.println(") added...");
      }
/*for (int b=0; b<6; b++) peerInfo.peer_addr[b] = (uint8_t) broadcastAddressMonitor1[b];
      if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
      }
      else {
        Serial.print (" ("); PrintMAC(peerInfo.peer_addr);  Serial.println(") added...");
      }
for (int b=0; b<6; b++) peerInfo.peer_addr[b] = (uint8_t) broadcastAddressMonitor2[b];
      if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
      }
      else {
        Serial.print (" ("); PrintMAC(peerInfo.peer_addr);  Serial.println(") added...");
      }
*/
    // Register Peers
    for (int PNr=0; PNr<MAX_PEERS; PNr++) {
      if (!isPeerEmpty(PNr)) {
        for (int b=0; b<6; b++) peerInfo.peer_addr[b] = (uint8_t) P[PNr].BroadcastAddress[b];
          if (esp_now_add_peer(&peerInfo) != ESP_OK) {
            PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
          }
          else {
            Serial.print("Peer: "); Serial.print(P[PNr].Name); 
            Serial.print (" ("); PrintMAC(peerInfo.peer_addr); Serial.println(") added...");
          }
      }
    }
  #elif defined(ESP8266)
    if (esp_now_add_peer(broadcastAddressAll, ESP_NOW_ROLE_SLAVE, 1, NULL, 0) != 0) {
      PrintMAC(broadcastAddressAll); Serial.println(": Failed to add peer");
    }
    else {
      Serial.print (" ("); PrintMAC(broadcastAddressAll);  Serial.println(") added...");
    }
    for (int PNr=0; PNr<MAX_PEERS; PNr++) {
      if (!isPeerEmpty(PNr)) {
        if (esp_now_add_peer(P[PNr].BroadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0) != 0) {
          Serial.println(P[PNr].Name); Serial.println(": Failed to add peer");
        }
        else {
          Serial.print (" ("); PrintMAC(P[PNr].BroadcastAddress);  Serial.println(") added...");
        }
      }
    }
  #endif  // ESP8266

}
void ClearPeers() {
  preferences.begin("JeepifyPeers", false);
    preferences.clear();
    Serial.println("JeepifyPeers cleared...");
  preferences.end();
}
void ClearInit() {
  preferences.begin("JeepifyInit", false);
    preferences.clear();
    Serial.println("JeepifyInit cleared...");
  preferences.end();
}
void SendMessage () {
  //sendet NAME0:Value0, NAME1:Value1, SLEEP:Status, DEBUG:Status
  char buf[200];
  doc.clear();
  jsondata = "";

  doc["Node"] = NODE_NAME;   

  for (int SNr=0; SNr<MAX_PERIPHERALS ; SNr++) {
    if (S[SNr].Type == SENS_TYPE_SWITCH) {
      doc[S[SNr].Name] = S[SNr].Value;
    }
    if (S[SNr].Type == SENS_TYPE_AMP) {
      S[SNr].Value = ReadAmp(SNr);
      dtostrf(S[SNr].Value, 0, 2, buf);
      doc[S[SNr].Name] = buf;
    }
    if (S[SNr].Type == SENS_TYPE_VOLT) {
      S[SNr].Value = ReadVolt(SNr);
      dtostrf(S[SNr].Value, 0, 2, buf);
      doc[S[SNr].Name] = buf;
    }
  }
  doc["Sleep"] = SleepMode;
  doc["Debug"] = Debug;

  serializeJson(doc, jsondata);  
  //senden an alle Monitore
  ReportPeers();

  for (int PNr=0; PNr<MAX_PEERS; PNr++) {
    //Serial.println(P[PNr].Type);
    if (P[PNr].Type >= MONITOR_ROUND) {
      Serial.print("Sending to: "); Serial.println(P[PNr].Name); 
      Serial.print(" ("); PrintMAC(P[PNr].BroadcastAddress); Serial.println(")");
      esp_now_send(P[PNr].BroadcastAddress, (uint8_t *) jsondata.c_str(), 200);  //Sending "jsondata"  
      Serial.println(jsondata);
      Serial.println();
    }
  }

  if (Debug) { Serial.print("\nSending: "); Serial.println(jsondata); }
  AddStatus("SendStatus");
}
void SendPairingRequest() {
  // sendet auf Broadcast: "addme", T0:Type, N0:Name, T1:Type, N1:Name...
  char Buf[100] = {};

  jsondata = "";  //clearing String after data is being sent
  doc.clear();
  
  doc["Node"]    = NODE_NAME;   
  doc["Type"]    = NODE_TYPE;
  doc["Pairing"] = "add me";
  
  for (int Si=0 ; Si<MAX_PERIPHERALS; Si++) {
    if (S[Si].Type) {
      sprintf(Buf, "T%d", Si); 
      doc[Buf] = S[Si].Type;
      sprintf(Buf, "N%d", Si); 
      doc[Buf] = S[Si].Name;
    }
  }
  serializeJson(doc, jsondata);  

  esp_now_send(broadcastAddressAll, (uint8_t *) jsondata.c_str(), 200);  //Sending "jsondata"  
  
  if (Debug) { Serial.print("\nSending: "); Serial.println(jsondata); }
  AddStatus("Send Pairing request...");                                       
}
void SetSleepMode(bool Mode) {
  preferences.begin("JeepifyInit", false);
    SleepMode = Mode;
    if (preferences.getBool("SleepMode", false) != SleepMode) preferences.putBool("SleepMode", SleepMode);
  preferences.end();
}
void SetDebugMode(bool Mode) {
  preferences.begin("JeepifyInit", false);
    Debug = Mode;
    if (preferences.getBool("Debug", false) != Debug) preferences.putBool("Debug", Debug);
  preferences.end();
}
void ShowEichen() {
  char Buf[100] = {}; char BufNr[10] = {};
  
  if (Debug) Serial.println("Eichen...");
  preferences.begin("JeepifyInit", false);
  
  for(int SNr=0; SNr<MAX_PERIPHERALS; SNr++) {
    if (S[SNr].Type == SENS_TYPE_AMP) {
      float TempVal  = 10828; //ads.readADC_SingleEnded(S[SNr].IOPort);
      float TempVolt = 13;// ads.computeVolts(TempVal);
      if (Debug) { 
        Serial.print("TempVal:");     Serial.println(TempVal);
        Serial.print(", TempVolt: "); Serial.println(TempVolt);
      }
      S[SNr].NullWert = TempVolt;
      sprintf(Buf, "Null-%d", SNr); 
      preferences.putFloat(Buf, S[SNr].NullWert);
      if (Debug) {
        Serial.print("schreibe "); Serial.print(Buf); Serial.print(" = "); Serial.println(S[SNr].NullWert); 
      }

      dtostrf(TempVolt, 0, 2, BufNr);
      sprintf(Buf, "Eichen fertig: [%d] %s (Type: %d): Gemessene Spannung bei Null: %sV", SNr, S[SNr].Name, S[SNr].Type, BufNr);
      Serial.println(Buf);
      AddStatus(Buf);
    }
  }
  preferences.end();
}
void AddStatus(String Msg) {
  for (int Si=MAX_STATUS-1; Si>0; Si--) {
    Status[Si].Msg   = Status[Si-1].Msg;
    Status[Si].TSMsg = Status[Si-1].TSMsg;
  }
  Status[0].Msg = Msg;
  Status[0].TSMsg = millis();
}
void ShowStatus() {
  for(int SNr=0; SNr<MAX_STATUS; SNr++) {
      char Buf[20];
      sprintf(Buf, "%02d:%02d:%02d", (int)Status[SNr].TSMsg/360000%60, (int)Status[SNr].TSMsg/60000%60, (int)Status[SNr].TSMsg/1000%60);
      Serial.println(Buf);
  }
}
void ShowVoltCalib(float V) {
  char Buf[100] = {}; char BufNr[10] = {}; 
  if (Debug) Serial.println("Volt eichen...");
  preferences.begin("JeepifyInit", false);
  
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++){
    if (S[SNr].Type == SENS_TYPE_VOLT) {
      int TempRead = analogRead(S[SNr].IOPort);
      
      if (Debug) {
        Serial.print("S["); Serial.print(SNr); Serial.print("].Vin = ");
        Serial.println(S[SNr].Vin, 4);
        Serial.print("Volt(nachher) = ");
        Serial.println(TempRead/S[SNr].Vin, 4);
      }
      S[SNr].Vin = TempRead / V;
      
      preferences.begin("JeepifyInit", false);
      preferences.putFloat("Vin", S[SNr].Vin);
      preferences.end();

      dtostrf(TempRead/S[SNr].Vin, 0, 2, BufNr);
      sprintf(Buf, "[%d] %s (Type: %d): Spannung ist jetzt: %sV", SNr, S[SNr].Name, S[SNr].Type, BufNr);
      
      Serial.println(Buf);
      AddStatus(Buf);

      break;
    }
  }
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { //ESP32
//void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  char* buff = (char*) incomingData;        //char buffer
  bool PairingSuccess = false;
  jsondata = String(buff);                  //converting into STRING
  Serial.print("Recieved ");
  Serial.println(jsondata);    //Complete JSON data will be printed here
  
  DeserializationError error = deserializeJson(doc, jsondata);
  
  if (!error) {
    Serial.println("No Error");
    
    if ((doc["Pairing"] == "you are paired") and (doc["Peer"] == NODE_NAME)) { 
      Serial.println("in you are paired und node");
    
      bool exists = esp_now_is_peer_exist(mac);
      if (exists) { 
        PrintMAC(mac); Serial.println(" already exists...");
      }
      else {
        for (int PNr=0; PNr<MAX_PEERS; PNr++) {
          Serial.print("P["); Serial.print(PNr); Serial.print("].Type = "); Serial.println(P[PNr].Type);
          if ((P[PNr].Type == 0) and (!PairingSuccess)) {
            Serial.println("leerer Slot gefunden");
            P[PNr].Type = (int) doc["Type"];
            strcpy(P[PNr].Name, doc["Node"]);
            
            for (int b = 0; b < 6; b++ ) P[PNr].BroadcastAddress[b] = mac[b];
            P[PNr].TSLastSeen = millis();
            
            PairingSuccess = true; 
            SavePeers();
            //ShowAllPreferences();
            RegisterPeers();
            
            if (Debug) {
              Serial.print("Adding in slot: "); Serial.println(PNr);
              Serial.print("Name: "); Serial.print(P[PNr].Name);
              Serial.print(" (");PrintMAC(P[PNr].BroadcastAddress); Serial.println(")\n");
              Serial.print("Saving Peers after received new one...");
              ReportPeers();
            }
            ReadyToPair = false;
          }
        }
        if (!PairingSuccess) { PrintMAC(mac); Serial.println(" adding failed..."); } 
      }
    }
    if (doc["Order"] == "stay alive") {
      TSLastContact = millis();
      if (Debug) { Serial.print("LastContact: "); Serial.println(TSLastContact); }
    }
    if (doc["Order"] == "SleepMode On")  { AddStatus("Sleep: on");  SetSleepMode(true); }
    if (doc["Order"] == "SleepMode Off") { AddStatus("Sleep: off"); SetSleepMode(false); }
    if (doc["Order"] == "Debug on")      { AddStatus("Debug: on");  SetDebugMode(true); }
    if (doc["Order"] == "Debug off")     { AddStatus("Debug: off"); SetDebugMode(false); }
    if (doc["Order"] == "Reset")         { AddStatus("Clear all"); ClearPeers(); ClearInit(); }
    if (doc["Order"] == "Restart")       { ESP.restart(); }
    if (doc["Order"] == "Pair")          { TSPair = millis(); ReadyToPair = true; AddStatus("Pairing beginnt"); }

    // BatterySensor
    if (NODE_TYPE == BATTERY_SENSOR) {
      if (doc["Order"] == "Eichen")      { Mode = S_EICHEN;  AddStatus("Eichen beginnt"); ShowEichen(); }
      if (doc["Order"] == "VoltCalib")   { Mode = S_CAL_VOL; AddStatus("VoltCalib beginnt"); ShowVoltCalib((float)doc["Value"]); }
    }
    // PDC
    if ((NODE_TYPE == SWITCH_1_WAY) or (NODE_TYPE == SWITCH_2_WAY) or
        (NODE_TYPE == SWITCH_4_WAY) or (NODE_TYPE == SWITCH_8_WAY)) {
      if (doc["Order"]   == "ToggleSwitch") {
        for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) {
          if (S[SNr].Name == doc["Value"]) {
            S[SNr].Value = !S[SNr].Value; 
            String Nr = doc["Value"];
            AddStatus("ToggleSwitch "+Nr);
            UpdateSwitches();
          }
        }
      }      
    }
  } // end (!error)
  else {  // error
        Serial.print(F("deserializeJson() failed: "));  //Just in case of an ERROR of ArduinoJSon
        Serial.println(error.f_str());
        return;
  }
}
void UpdateSwitches() {
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) if (S[SNr].Type = SENS_TYPE_SWITCH) digitalWrite(S[SNr].IOPort, S[SNr].Value);
  SendMessage();
}
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) { 
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
  
  //8266
  /*void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0){
      Serial.println("Delivery success");
    }
    else{
      Serial.println("Delivery fail");
    }
  }
*/

void setup() {
  Serial.begin(74880);

  /*Wire.begin(D5, D6);
  ads.setGain(GAIN_TWOTHIRDS);  // 0.1875 mV/Bit .... +- 6,144V
  ads.begin();
  */
  WiFi.mode(WIFI_STA);
  
  #ifdef ESP32
    if (esp_now_init() != ESP_OK) { Serial.println("Error initializing ESP-NOW"); return; }
  #elif defined(ESP8266)
    if (esp_now_init() != 0)      { Serial.println("Error initializing ESP-NOW"); return; }
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  #endif  // ESP32
  
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);    

  //ClearPeers();
  InitModule();     AddStatus("Init Module");
  GetPeers();       AddStatus("Get Peers");
  ReportPeers();    
  RegisterPeers();  AddStatus("Init fertig");
  
  if (PeerCount == 0) { AddStatus("Pairing beginnt"); ReadyToPair = true; TSPair = millis(); }
  
  TSLastContact = millis();

  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) if (S[SNr].Type = SENS_TYPE_SWITCH) gpio_hold_dis((gpio_num_t)S[SNr].IOPort);  
  gpio_deep_sleep_hold_dis();

}
void loop() {
  if  ((millis() - TSSend ) > MSG_INTERVAL  ) {
    TSSend = millis();
    if (ReadyToPair) SendPairingRequest();
    else SendMessage();
  }
  if (((millis() - TSPair ) > PAIR_INTERVAL ) and (ReadyToPair)) {
    TSPair = 0;
    ReadyToPair = false;
    AddStatus("Pairing beendet...");
  }
  if  (((millis() - TSLastContact) > SLEEP_INTERVAL ) and (SleepMode)) GoToSleep();
}
float ReadAmp (int A) {
  float TempVal = 12; //ads.readADC_SingleEnded(S[A].IOPort);
  float TempVolt = 11;// ads.computeVolts(TempVal); 
  float TempAmp = (TempVolt - S[A].NullWert) / S[A].VperAmp;

  if (Debug) {
    Serial.print("TempVal:  "); Serial.println(TempVal,4);
    Serial.print("TempVolt: "); Serial.println(TempVolt,4);
    Serial.print("Nullwert: "); Serial.println(S[A].NullWert,4);
    Serial.print("VperAmp:  "); Serial.println(S[A].VperAmp,4);
    Serial.print("TempAmp:  "); Serial.println(TempAmp,4);
  } 
  if (abs(TempAmp) < SCHWELLE) TempAmp = 0;
  
  return (TempAmp); //TempAmp;
}
float ReadVolt(int V) {
  if (!S[V].Vin) { Serial.println("Vin must not be zero !!!"); return 0; }
  
  float TempVal  = analogRead(S[V].IOPort);
  float TempVolt = TempVal / S[V].Vin;
  
  if (Debug) {
    Serial.print("TempVal:  "); Serial.println(TempVal,4);
    Serial.print("Vin:      "); Serial.println(S[V].Vin);
    Serial.print("Volt: ");     Serial.println(TempVolt,4);
    
  } 
  return TempVolt;
}
bool  isPeerEmpty(int PNr) {
  return (P[PNr].Type == 0);
}
bool  isSensorEmpty(int SNr) {
  return (S[SNr].Type == 0);
}
void  GoToSleep() {
  gpio_deep_sleep_hold_en();
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) if (S[SNr].Type = SENS_TYPE_SWITCH) gpio_hold_en((gpio_num_t)S[SNr].IOPort);  
  esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
  esp_deep_sleep_start();
}
void  PrintMAC(const uint8_t * mac_addr){
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
}