#define NODE_NAME "32BatS"
#define VERSION   "V 1.16"

#pragma region Module_Definitions
//#define MODULE_C3

#define MODULE_3AMP_1VOLT_NOADC
//#define MODULE_4AMP_1VOLT_NOADC
//#define MODULE_SWITCH_2
//#define MODULE_SWITCH_4
//#define MODULE_4AMP_1VOLT

#ifdef MODULE_SWITCH_4
  #define NODE_TYPE SWITCH_4_WAY
  #define RELAY_TYPE     1 // -1 bei reversed
 
  #define NAME_SENSOR_0 "M3-SW0"
  #define TYPE_SENSOR_0  SENS_TYPE_SWITCH
  #define IOPORT_0       1
  
  #define NAME_SENSOR_1 "M3-SW1"
  #define TYPE_SENSOR_1  SENS_TYPE_SWITCH
  #define IOPORT_1      2
  
  #define NAME_SENSOR_2 "M3-SW2"
  #define TYPE_SENSOR_2  SENS_TYPE_SWITCH
  #define IOPORT_2       3
  
  #define NAME_SENSOR_3 "M3-SW3"
  #define TYPE_SENSOR_3  SENS_TYPE_SWITCH
  #define IOPORT_3       4
#endif
#ifdef MODULE_SWITCH_2
  #define NODE_TYPE SWITCH_2_WAY
  #define RELAY_TYPE    -1 // 1-normal, -1 bei reversed
 
  #define NAME_SENSOR_0 "SW-0"
  #define TYPE_SENSOR_0  SENS_TYPE_SWITCH
  #define IOPORT_0       1
  
  #define NAME_SENSOR_1 "SW-1"
  #define TYPE_SENSOR_1  SENS_TYPE_SWITCH
  #define IOPORT_1       2
#endif
#ifdef MODULE_4AMP_1VOLT
  #define NODE_TYPE BATTERY_SENSOR
  #define ADC_USED 
  #define RELAY_TYPE     1 // 1-normal, -1 bei reversed      
 
  #define NAME_SENSOR_0 "Extern"
  #define TYPE_SENSOR_0  SENS_TYPE_AMP
  #define NULL_SENSOR_0  3134
  #define SENS_SENSOR_0  0.066
  #define IOPORT_0       0

  #define NAME_SENSOR_1 "In-Car"
  #define TYPE_SENSOR_1  SENS_TYPE_AMP
  #define NULL_SENSOR_1  3134
  #define SENS_SENSOR_1  0.066
  #define IOPORT_1       1
  
  #define NAME_SENSOR_2 "Solar"
  #define TYPE_SENSOR_2  SENS_TYPE_AMP
  #define NULL_SENSOR_2  3150
  #define SENS_SENSOR_2  0.066
  #define IOPORT_2       2
  
  #define NAME_SENSOR_3 "Load"
  #define TYPE_SENSOR_3  SENS_TYPE_AMP
  #define NULL_SENSOR_3  3150
  #define SENS_SENSOR_3  0.066
  #define IOPORT_3       3
  
  #define NAME_SENSOR_4  "Lipo"
  #define TYPE_SENSOR_4  SENS_TYPE_VOLT
  #define VIN_SENSOR_4   200
  #define IOPORT_4       PIN_A0
#endif
#ifdef MODULE_4AMP_1VOLT_NOADC
  #define NODE_TYPE BATTERY_SENSOR
  #define RELAY_TYPE     1 // 1-normal, -1 bei reversed
  #define VOLT_DEVIDER   1

  #define NAME_SENSOR_0 "Sol1"
  #define TYPE_SENSOR_0  SENS_TYPE_AMP
  #define NULL_SENSOR_0  3134
  #define SENS_SENSOR_0  0.066
  #define IOPORT_0       0 //34

  #define NAME_SENSOR_1 "Int1"
  #define TYPE_SENSOR_1  SENS_TYPE_AMP
  #define NULL_SENSOR_1  3134
  #define SENS_SENSOR_1  0.066
  #define IOPORT_1       1 //35
  
  #define NAME_SENSOR_2 "Ext1"
  #define TYPE_SENSOR_2  SENS_TYPE_AMP
  #define NULL_SENSOR_2  3150
  #define SENS_SENSOR_2  0.066
  #define IOPORT_2       3 //32
  
  #define NAME_SENSOR_3 "Load1"
  #define TYPE_SENSOR_3  SENS_TYPE_AMP
  #define NULL_SENSOR_3  3150
  #define SENS_SENSOR_3  0.066
  #define IOPORT_3       4 //33
  
  #define NAME_SENSOR_4  "LiPo1"
  #define TYPE_SENSOR_4  SENS_TYPE_VOLT
  #define VIN_SENSOR_4   200
  #define IOPORT_4       5 //39
#endif
#ifdef MODULE_3AMP_1VOLT_NOADC // kleines esp32 mit extra display
  #define NODE_TYPE BATTERY_SENSOR
  #define RELAY_TYPE     1 // 1-normal, -1 bei reversed
  #define VOLT_DEVIDER   1.5

  #define NAME_SENSOR_0 "klA1"
  #define TYPE_SENSOR_0  SENS_TYPE_AMP
  #define NULL_SENSOR_0  2.2991
  #define SENS_SENSOR_0  0.066
  #define IOPORT_0       35

  #define NAME_SENSOR_1 "klA2"
  #define TYPE_SENSOR_1  SENS_TYPE_AMP
  #define NULL_SENSOR_1  2.2991
  #define SENS_SENSOR_1  0.066
  #define IOPORT_1       32
  
  #define NAME_SENSOR_2 "klA3"
  #define TYPE_SENSOR_2  SENS_TYPE_AMP
  #define NULL_SENSOR_2  2.2875
  #define SENS_SENSOR_2  0.066
  #define IOPORT_2       33
  
  #define NAME_SENSOR_3  "klV1"
  #define TYPE_SENSOR_3  SENS_TYPE_VOLT
  #define VIN_SENSOR_3   200
  #define IOPORT_3       34
#endif
#pragma endregion Module_Definitions
#pragma region Board_specific(ADC, TFT, TOUCH, BUTTONS)
#define BOOT_BUTTON 9 // ESP-C3 SuperMini

#ifdef ADC_USED
  #include <Adafruit_ADS1X15.h>
  #include <Wire.h>
  #include <Spi.h>
  Adafruit_ADS1115 ads;
#endif
#ifdef TFT_USED
  #include <TFT_eSPI.h>
  #include "NotoSansBold15.h"
  #include "NotoSansBold36.h"
  #include "NotoSansMonoSCB20.h"

  TFT_eSPI TFT = TFT_eSPI();
#endif
#ifdef TOUCH911_USED
  #include "TAMC_GT911.h"
  int TouchRead();
  TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);
#endif
#ifndef MODULE_C3 // wenn c3 dann kein MRD
#ifdef ESP8266 // ESP8266_MRD_USE_RTC false
  #define ESP8266_MRD_USE_RTC   false  
#endif
#define ESP_MRD_USE_LITTLEFS           true
#define MULTIRESETDETECTOR_DEBUG       true  //false
#define MRD_TIMES               3
#define MRD_TIMEOUT             10
#define MRD_ADDRESS             0

#include <ESP_MultiResetDetector.h>

MultiResetDetector* mrd;
#endif
#pragma endregion Board_specific(ADC, TFT, TOUCH)
#pragma region LED-setup
#ifdef ESP32 
  #ifndef LED_BUILTIN
    #define LED_BUILTIN 2         
  #endif
  #define LED_OFF     HIGH
  #define LED_ON      LOW
#else
  #define LED_ON      LOW
  #define LED_OFF     HIGH
#endif
#pragma endregion LED-setup
#pragma region Includes
#include <Arduino.h>
#include "../../jeepify.h"
#include <ArduinoJson.h>
#include <Preferences.h>
#pragma region ESP_NOW
#ifdef ESP32
  #include <esp_now.h>
  #include <WiFi.h>
  #include <nvs_flash.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <espnow.h>
#endif 
#pragma endregion ESP_NOW
#pragma endregion Includes
#pragma region Globals
#ifndef D5
  #define D5 14
#endif
#ifndef D6
  #define D6 12
#endif

struct struct_Status {
  String    Msg;
  uint32_t  TSMsg;
};

struct_Peer   P[MAX_PEERS];
struct_Touch Touch;
struct_Status Status[MAX_STATUS];

volatile u_int8_t TempBroadcast[6];

bool DebugMode     = true;
bool SleepMode     = false;
bool DemoMode      = false;
bool ReadyToPair   = true;
bool ScreenChanged = false;

int  Mode          = S_STATUS;
int  OldMode       = 0;
int  PeerCount = 0;

volatile uint32_t TSLastSend      = 0;
volatile uint32_t TSLastContact   = 0;
volatile uint32_t TSScreenRefresh = 0;
volatile uint32_t TSBootButton    = 0;
volatile uint32_t TSSend  = 0;
volatile uint32_t TSPair  = 0;
volatile uint32_t TSTouch = 0;
volatile uint32_t TSLed   = 0;

Preferences preferences;

#ifdef ESP32
  RTC_DATA_ATTR struct_Periph S[MAX_PERIPHERALS];
#elif defined(ESP8266)
  struct_Periph S[MAX_PERIPHERALS];
#endif 
#pragma endregion Globals
#pragma region Function_Definitions
#ifdef ESP32 // void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  #elif defined(ESP8266)
    void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);
    void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);
#endif  
float  ReadAmp (int A);
float  ReadVolt(int V);
void   SendMessage();
void   SendPairingRequest();

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
void   ShowMessage(String Msg);
void   UpdateSwitches();

void   SetSleepMode(bool Mode);
void   SetDebugModeMode(bool Mode);
void   AddStatus(String Msg);
void   ShowStatus();

void   PrintMAC(const uint8_t * mac_addr);

bool   isPeerEmpty(int PNr);
bool   isSensorEmpty(int SNr);
void   GoToSleep();
#pragma endregion Function_Definitions

void InitModule() {
  preferences.begin("JeepifyInit", true);
  DebugMode = preferences.getBool("DebugMode", true);
  SleepMode = preferences.getBool("SleepMode", false);
  DemoMode  = preferences.getBool("DemoMode", false);
  preferences.end();
  
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
  
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++)  { // PinMode
    switch (S[SNr].Type) {
      case SENS_TYPE_SWITCH: pinMode(S[SNr].IOPort, OUTPUT); break;
      case SENS_TYPE_VOLT:   pinMode(S[SNr].IOPort, INPUT ); break;
      case SENS_TYPE_AMP:    pinMode(S[SNr].IOPort, INPUT ); break;
    }
  }
  pinMode(BOOT_BUTTON, INPUT);

  #ifdef ADC_USED
    Wire.begin(D5, D6);
    ads.setGain(GAIN_TWOTHIRDS);  // 0.1875 mV/Bit .... +- 6,144V
    ads.begin();
  #endif
  #ifdef TOUCH911_USED
    tp.begin();
    tp.setRotation(ROTATION_LEFT);
  #endif
  #ifdef TFT_USED
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
    TFT.init();
    TFT.setRotation(3);
    TFT.fillScreen(TFT_BLACK);
  #endif
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(74880);

  #ifndef MODULE_C3
  mrd = new MultiResetDetector(MRD_TIMEOUT, MRD_ADDRESS);

  if (mrd->detectMultiReset()) {
    Serial.println("Multi Reset Detected");
    digitalWrite(LED_BUILTIN, LED_ON);
    ClearPeers();
    SetSleepMode(false);
    ReadyToPair = true; TSPair = millis();
  }
  else {
    Serial.println("No Multi Reset Detected");
    digitalWrite(LED_BUILTIN, LED_OFF);
  }
  #endif

  WiFi.mode(WIFI_STA);
  
  #ifdef ESP32
    if (esp_now_init() != ESP_OK) { Serial.println("Error initializing ESP-NOW"); return; }
  #elif defined(ESP8266)
    if (esp_now_init() != 0)      { Serial.println("Error initializing ESP-NOW"); return; }
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  #endif  // ESP32
  
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);    

  InitModule();     AddStatus("Init Module");
  GetPeers();       AddStatus("Get Peers");
  ReportPeers();    
  RegisterPeers();  AddStatus("Init fertig");
  
  if (PeerCount == 0) { AddStatus("Pairing beginnt"); ReadyToPair = true; TSPair = millis(); }
  
  TSLastContact = millis();

  #ifdef ESP32
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) if (S[SNr].Type == SENS_TYPE_SWITCH) gpio_hold_dis((gpio_num_t)S[SNr].IOPort);  
  gpio_deep_sleep_hold_dis(); 
  #endif 
  
  UpdateSwitches();
}
void loop() {
  if  ((millis() - TSTouch) > TOUCH_INTERVAL) {
    TSTouch = millis();

    int BB = !digitalRead(BOOT_BUTTON);
    //Serial.println(BB);
    if (BB == 1) {
      if (!TSBootButton) TSBootButton = millis();
      else {
        if ((millis() - TSBootButton) > 3000) {
          Serial.println("Button pressed... Clearing Peers and Reset");
          AddStatus("Clearing Peers and Reset");
          #ifdef ESP32
            nvs_flash_erase(); nvs_flash_init();
          #elif defined(ESP8266)
            ClearPeers();
          #endif 
           ESP.restart();
        }
      }
    }
    else TSBootButton = 0;

    #ifdef TOUCH911_USED
    int G;
    G = TouchRead();

    switch (Mode) {
      case S_PAIRING:
        switch (G) {
          case CLICK:      Mode = S_STATUS; break;
        }
        break;
      case S_STATUS:
        switch (G) {
          case CLICK:      Mode = S_PAIRING; break;
          case LONG_PRESS: ClearPeers(); ESP.restart(); break;
        }
        break;
      }
      #endif
  }
  
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
  int Diff = millis() - TSLastContact;
  //Serial.println(Diff);
  if (Diff > SLEEP_INTERVAL) {
    if (SleepMode) {
      Serial.print("Going to sleep at: "); Serial.println(millis());
      Serial.print("LastContact    at: "); Serial.println(TSLastContact);
      GoToSleep();
    }
  }
  if  (((millis() - TSLed) > 300) and (TSLed)) {
    TSLed = 0;
    digitalWrite(LED_BUILTIN, LED_OFF);
  }
  
  #ifdef TFT_USED
  switch (Mode) {
    case S_PAIRING: ShowPairingScreen(); break;
    case S_STATUS:  ShowStatus();        break;
    case M_Menu:    break;
  }
  #endif
}
#pragma region Peer-Things
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
      snprintf(Buf, sizeof(Buf), "Type-%d", Pi); 
      preferences.putInt(Buf, P[Pi].Type);
      Serial.print("schreibe "); Serial.print(Buf); Serial.print(" = "); Serial.println(P[Pi].Type);

      //P.Name
      snprintf(Buf, sizeof(Buf), "Name-%d", Pi); 
      BufS = P[Pi].Name;
      preferences.putString(Buf, BufS);
      Serial.print("schreibe "); Serial.print(Buf); Serial.print(" = "); Serial.println(BufS);
      
      //P.BroadcastAdress
      snprintf(Buf, sizeof(Buf), "MAC-%d", Pi); 
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
    snprintf(Buf, sizeof(Buf), "Type-%d", Pi); 
    if (preferences.getInt(Buf,0) > 0) {
      PeerCount++;

      // Type-0
      snprintf(Buf, sizeof(Buf), "Type-%d", Pi); 
      P[Pi].Type = preferences.getInt(Buf);
      
      // Name-0
      snprintf(Buf, sizeof(Buf), "Name-%d", Pi); 
      BufS = preferences.getString(Buf);
      strcpy(P[Pi].Name, BufS.c_str());
      
      // MAC-0
      snprintf(Buf, sizeof(Buf), "MAC-%d", Pi); 
      preferences.getBytes(Buf, P[Pi].BroadcastAddress, 6);
      
      P[Pi].TSLastSeen = millis();

      if (DebugMode) {
        Serial.print("GetPeers: P["); Serial.print(Pi); Serial.print("]: Type="); Serial.print(P[Pi].Type); 
        Serial.print(", Name="); Serial.print(P[Pi].Name);
        Serial.print(", MAC="); PrintMAC(P[Pi].BroadcastAddress); Serial.println();
      }
    }
  }
  if (PeerCount ==0) { ReadyToPair = true; TSPair = millis(); }

  float TempFloat = 0;
      
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) {
    if (S[SNr].Type == SENS_TYPE_AMP) {
      snprintf(Buf, sizeof(Buf), "Null-%d", SNr); 
      TempFloat = preferences.getFloat(Buf, 0);
      if (TempFloat  > 0) S[SNr].NullWert = TempFloat;

      if (DebugMode) {
        Serial.print("Lese "); Serial.print(Buf); Serial.print(" = "); Serial.println(S[SNr].NullWert); 
      }
    }
    if (S[SNr].Type == SENS_TYPE_VOLT) {
      snprintf(Buf, sizeof(Buf), "Vin-%d", SNr); 
      TempFloat = preferences.getFloat(Buf, 0);
      if (TempFloat > 0) S[SNr].Vin = TempFloat;

      if (DebugMode) {
        Serial.print("Lese "); Serial.print(Buf); Serial.print(" = "); Serial.println(S[SNr].Vin); 
      }
    }
  }
  preferences.end();
}
void ReportPeers() {
  char Buf[200]; String ZName;

  switch (NODE_TYPE) {
          case SWITCH_1_WAY:   ZName = "1-way PDC";   break;
          case SWITCH_2_WAY:   ZName = "2-way PDC";   break;
          case SWITCH_4_WAY:   ZName = "4-way PDC";   break;
          case SWITCH_8_WAY:   ZName = "8-way PDC";   break;
          case PDC_SENSOR_MIX: ZName = "PDC-MIX";     break;
          case BATTERY_SENSOR: ZName = "Batt.-Sens."; break;
  }

  Serial.println(); Serial.print(NODE_NAME); Serial.print(", I am a "); Serial.println(ZName);
  Serial.println("Report-Peers:");
  for (int PNr=0; PNr<MAX_PEERS; PNr++) {
    if (DebugMode) {
      snprintf(Buf, sizeof(Buf), "%s (Type: %d) - MAC:", P[PNr].Name, P[PNr].Type);
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
#pragma endregion Peer-Things
#pragma region Send-Things
void SendMessage () {
  //sendet NAME0:Value0, NAME1:Value1, SLEEP:Status, Debug:Status
  TSLed = millis();
  digitalWrite(LED_BUILTIN, LED_ON);

  StaticJsonDocument<500> doc; String jsondata; doc.clear(); jsondata = "";
  char buf[100]; 

  doc["Node"] = NODE_NAME;   

  for (int SNr=0; SNr<MAX_PERIPHERALS ; SNr++) {
    if (S[SNr].Type == SENS_TYPE_SWITCH) {
      doc[S[SNr].Name] = S[SNr].Value;
    }
    if (S[SNr].Type == SENS_TYPE_AMP) {
      if (DemoMode) S[SNr].Value = random(0,30);
      else          S[SNr].Value = ReadAmp(SNr);
    	
      if (abs(S[SNr].Value) > 99) S[SNr].Value = -99;
      dtostrf(S[SNr].Value, 0, 2, buf);
      
      if (S[SNr].Value != S[SNr].OldValue) {
        S[SNr].OldValue = S[SNr].Value;
        S[SNr].Changed = true;
      }
      else {
        S[SNr].OldValue = S[SNr].Value;
        S[SNr].Changed = false;
      }

      if (S[SNr].Changed) doc[S[SNr].Name] = buf;
    }

    if (S[SNr].Type == SENS_TYPE_VOLT) {
      if (DemoMode) S[SNr].Value = random(10,15);
      else          S[SNr].Value = ReadVolt(SNr);

      dtostrf(S[SNr].Value, 0, 2, buf);
      
      if (S[SNr].Value != S[SNr].OldValue) {
        S[SNr].OldValue = S[SNr].Value;
        S[SNr].Changed = true;
      }
      else {
        S[SNr].OldValue = S[SNr].Value;
        S[SNr].Changed = false;
      }

      if (S[SNr].Changed) doc[S[SNr].Name] = buf;
    }
  }
  
  // Status bit1 DebugMode, bit2 Sleep, bit3 Demo, bit4 RTP
  int Status = 0;
  if (DebugMode)   bitSet(Status, 0);
  if (SleepMode)   bitSet(Status, 1);
  if (DemoMode)    bitSet(Status, 2);
  if (ReadyToPair) bitSet(Status, 3);
  
  doc["Status"]  = Status;

  serializeJson(doc, jsondata);  

  for (int PNr=0; PNr<MAX_PEERS; PNr++) {
    if (P[PNr].Type >= MONITOR_ROUND) {
      Serial.print("Sending to: "); Serial.print(P[PNr].Name); 
      if (esp_now_send(P[PNr].BroadcastAddress, (uint8_t *) jsondata.c_str(), 200) == 0) Serial.println("ESP_OK");  //Sending "jsondata"  
      else Serial.println("ESP_ERROR"); 
      Serial.println(jsondata);
    }
  }

  AddStatus("SendStatus");
}
void SendPairingRequest() {
  // sendet auf Broadcast: "addme", T0:Type, N0:Name, T1:Type, N1:Name...
  TSLed = millis();
  digitalWrite(LED_BUILTIN, LED_ON);
  
  StaticJsonDocument<500> doc; String jsondata; jsondata = ""; doc.clear();
  char Buf[100] = {};
  
  doc["Node"]    = NODE_NAME;   
  doc["Type"]    = NODE_TYPE;
  doc["Pairing"] = "add me";
  
  for (int Si=0 ; Si<MAX_PERIPHERALS; Si++) {
    if (S[Si].Type) {
      snprintf(Buf, sizeof(Buf), "T%d", Si); 
      doc[Buf] = S[Si].Type;
      snprintf(Buf, sizeof(Buf), "N%d", Si); 
      doc[Buf] = S[Si].Name;
    }
  }
  serializeJson(doc, jsondata);  

  esp_now_send(broadcastAddressAll, (uint8_t *) jsondata.c_str(), 200);  //Sending "jsondata"  
  
  if (DebugMode) { Serial.print("\nSending: "); Serial.println(jsondata); }
  AddStatus("Send Pairing request...");                                     
}
#pragma endregion Send-Things
#pragma region System-Things
void SetDemoMode(bool Mode) {
  preferences.begin("JeepifyInit", false);
    DemoMode = Mode;
    if (preferences.getBool("DemoMode", false) != DemoMode) preferences.putBool("DemoMode", DemoMode);
  preferences.end();
}
void SetSleepMode(bool Mode) {
  preferences.begin("JeepifyInit", false);
    SleepMode = Mode;
    if (preferences.getBool("SleepMode", false) != SleepMode) preferences.putBool("SleepMode", SleepMode);
  preferences.end();
}
void SetDebugMode(bool Mode) {
  preferences.begin("JeepifyInit", false);
    DebugMode = Mode;
    if (preferences.getBool("DebugMode", false) != DebugMode) preferences.putBool("DebugMode", DebugMode);
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
void UpdateSwitches() {
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) if (S[SNr].Type == SENS_TYPE_SWITCH) digitalWrite(S[SNr].IOPort, S[SNr].Value*RELAY_TYPE);
  SendMessage();
}
float ReadAmp (int Si) {
  float TempVal      = 0;
  float TempVolt     = 0;
  float TempAmp      = 0;
  
  #ifdef ADC_USED // Werte auslesen
    TempVal  = ads.readADC_SingleEnded(S[Si].IOPort);
    TempVolt = ads.computeVolts(TempVal); 
    TempAmp  = (TempVolt - S[Si].NullWert) / S[Si].VperAmp;
    delay(10);
  #else
    float TempVoltOverNull = 0;
    TempVal  = analogRead(S[Si].IOPort);
    TempVolt = 3.3/4095*TempVal;
    TempAmp  = (TempVolt - S[Si].NullWert) / S[Si].VperAmp * VOLT_DEVIDER;// 1.5 wegen Voltage-Devider
    delay(10);
  #endif
  
  if (DebugMode) {
    Serial.print("TempVal:  "); Serial.println(TempVal,4);
    Serial.print("TempVolt: "); Serial.println(TempVolt,4);
    Serial.print("Nullwert: "); Serial.println(S[Si].NullWert,4);
    Serial.print("VperAmp:  "); Serial.println(S[Si].VperAmp,4);
    Serial.print("Amp (TempVolt - S[Si].NullWert) / S[Si].VperAmp * 1.5:  "); Serial.println(TempAmp,4);
  } 
  if (abs(TempAmp) < SCHWELLE) TempAmp = 0;
  
  return (TempAmp); //TempAmp;
}
float ReadVolt(int V) {
  if (!S[V].Vin) { Serial.println("Vin must not be zero !!!"); return 0; }
  
  float TempVal  = analogRead(S[V].IOPort);
  float TempVolt = TempVal / S[V].Vin;
  
  if (DebugMode) {
    Serial.print("TempVal:  "); Serial.println(TempVal,4);
    Serial.print("Vin:      "); Serial.println(S[V].Vin);
    Serial.print("Volt (TempVal / S[V].Vin)): ");     Serial.println(TempVolt,4);
    
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
  StaticJsonDocument<500> doc;
  String jsondata;

  jsondata = "";  //clearing String after data is being sent
  doc.clear();
  
  doc["Node"] = NODE_NAME;   
  doc["Type"] = NODE_TYPE;
  doc["Msg"]  = "GoodBye - going to sleep";
  
  serializeJson(doc, jsondata);  

  esp_now_send(broadcastAddressAll, (uint8_t *) jsondata.c_str(), 200);  //Sending "jsondata"  
  
  if (DebugMode) { Serial.print("\nSending: "); Serial.println(jsondata); }
  AddStatus("Send Going to sleep..."); 
  
  Serial.print("Going to sleep at: "); Serial.println(millis());
  Serial.print("LastContact    at: "); Serial.println(TSLastContact);
  
  #ifdef ESP32
  gpio_deep_sleep_hold_en();
  for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) if (S[SNr].Type == SENS_TYPE_SWITCH) gpio_hold_en((gpio_num_t)S[SNr].IOPort);  
  
  esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
  esp_deep_sleep_start();
  #elif defined(ESP8266)
  ESP.deepSleep(SLEEP_INTERVAL * 1000);
  #endif

}
void  PrintMAC(const uint8_t * mac_addr){
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
}
#pragma endregion System-Things
#pragma region Screens
void ShowVoltCalib(float V) {
  if (OldMode != Mode) { 
    TSScreenRefresh = millis(); 
    #ifdef TFT_USED
      TFT.fillScreen(TFT_BLACK); 
    #endif
  }
  if ((millis() - TSScreenRefresh > 1000) or (Mode != OldMode)) {
    OldMode = Mode;
    char Buf[100] = {}; char BufNr[10] = {}; 
  
    if (DebugMode) Serial.println("Volt-Messung kalibrieren...");
    
    preferences.begin("JeepifyInit", false);
    
    ScreenChanged = true;
    
    #ifdef TFT_USED
    TFT.fillScreen(TFT_BLACK);
    
    TFT.loadFont(AA_FONT_LARGE);
    
    TFT.setTextColor(TFT_RUBICON, TFT_BLACK);
    TFT.setTextPadding(469);
    TFT.setTextDatum(TL_DATUM);

    TFT.drawString("Volt-Messung kalibrieren...", 10, 10);
    TFT.unloadFont();
    #endif

    for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++){
      if (S[SNr].Type == SENS_TYPE_VOLT) {
        int TempRead = analogRead(S[SNr].IOPort);
        
        S[SNr].Vin = TempRead / V;
        
        if (DebugMode) {
          Serial.print("S["); Serial.print(SNr); Serial.print("].Vin = ");
          Serial.println(S[SNr].Vin, 4);
          Serial.print("Volt(nachher) = ");
          Serial.println(TempRead/S[SNr].Vin, 4);
        }
        
        preferences.begin("JeepifyInit", false);
        
        sprintf(Buf, "Vin-%d", SNr);
        preferences.putFloat(Buf, S[SNr].Vin);
        preferences.end();

        dtostrf(TempRead/S[SNr].Vin, 0, 2, BufNr);
        snprintf(Buf, sizeof(Buf), "[%d] %s (Type: %d): Spannung ist jetzt: %sV", SNr, S[SNr].Name, S[SNr].Type, BufNr);
        
        #ifdef TFT_USED
          int h=30;
          TFT.drawString(Buf, 10, 50+(SNr+1)*h);
        #endif
        AddStatus(Buf);

        break;
      }
  }
    delay(5000);
    
    Mode = S_MENU;
    
    TSScreenRefresh = millis();
  }
}
void ShowEichen() {
  if (1) { // OldMode != Mode) { 
    char Buf[100] = {}; char BufNr[10] = {};
    
    TSScreenRefresh = millis(); 
    
    #ifdef TFT_USED
    TFT.fillScreen(TFT_BLACK);
    TFT.loadFont(AA_FONT_LARGE);
    
    TFT.setTextColor(TFT_RUBICON, TFT_BLACK);
    TFT.setTextDatum(TC_DATUM);

    TFT.fillScreen(TFT_BLACK);
  
    TFT.drawString("Eichen...", 10, 30);
    TFT.unloadFont();
    #endif

    if (DebugMode) Serial.println("Eichen...");
    
    preferences.begin("JeepifyInit", false);

    for(int SNr=0; SNr<MAX_PERIPHERALS; SNr++) {
      if (S[SNr].Type == SENS_TYPE_AMP) {
        float TempVal  = 0;
        float TempVolt = 0;
        
        #ifdef ADC_USED
        TempVal  = ads.readADC_SingleEnded(S[SNr].IOPort);
        TempVolt = ads.computeVolts(TempVal);
        #else
        //Filter implementieren !!!
        TempVal  = analogRead(S[SNr].IOPort);
        TempVolt = 3.3/4095*TempVal; // 1.5???
        #endif      

        if (DebugMode) { 
          Serial.print("TempVal:");     Serial.println(TempVal);
          Serial.print(", TempVolt: "); Serial.println(TempVolt);
        }
        S[SNr].NullWert = TempVolt;
  
        snprintf(Buf, sizeof(Buf), "Null-%d", SNr); 
        preferences.putFloat(Buf, S[SNr].NullWert);
        if (DebugMode) {
          Serial.print("schreibe "); Serial.print(Buf); Serial.print(" = "); Serial.println(S[SNr].NullWert); 
        }

        dtostrf(TempVolt, 0, 2, BufNr);
        snprintf(Buf, sizeof(Buf), "Eichen fertig: [%d] %s (Type: %d): Gemessene Spannung bei Null: %sV", SNr, S[SNr].Name, S[SNr].Type, BufNr);
        
        #ifdef TFT_USED
        int h=20;
        TFT.loadFont(AA_FONT_SMALL);
        TFT.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        TFT.setTextDatum(TC_DATUM);
        TFT.drawString(Buf, 10, 30+(SNr+1)*h);
        TFT.unloadFont();
        #endif

        AddStatus(Buf);
      }
    }
    preferences.end();
  }
  
  if ((TSScreenRefresh - millis() > 1000) or (Mode != OldMode)) {
    OldMode = Mode;
    ScreenChanged = true;
    
    TSScreenRefresh = millis();
  }
}
void ShowMessage(String Msg) {
  if (OldMode != Mode) { 
    TSScreenRefresh = millis(); 
    #ifdef TFT_USED
      TFT.fillScreen(TFT_BLACK); 
    #endif
  }
  if ((TSScreenRefresh - millis() > 1000) or (Mode != OldMode)) {
    OldMode = Mode;

    #ifdef TFT_USED
    OldMode = Mode;
    ScreenChanged = true;

    TFT.loadFont(AA_FONT_LARGE);
    
    TFT.setTextColor(TFT_RUBICON, TFT_BLACK);
    TFT.setTextPadding(469);
    TFT.setTextDatum(TL_DATUM);

    TFT.drawString(MSg, 10, 10);
    TFT.unloadFont();

    TFT.setTextPadding(0);
    #endif
    
    TSScreenRefresh = millis();
  }
}
void ShowStatus() {
  if (OldMode != Mode) { 
    TSScreenRefresh = millis(); 
    #ifdef TFT_USED
      TFT.fillScreen(TFT_BLACK); 
    #endif

    for(int SNr=0; SNr<MAX_STATUS; SNr++) {
      char Buf[20];
      snprintf(Buf, sizeof(Buf), "%02d:%02d:%02d", (int)Status[SNr].TSMsg/360000%60, (int)Status[SNr].TSMsg/60000%60, (int)Status[SNr].TSMsg/1000%60);
      Serial.println(Buf);
    }
  }
  if ((TSScreenRefresh - millis() > 1000) or (Mode != OldMode)) {
    OldMode = Mode;

    #ifdef TFT_USED
    char Buf[100] = {}; char BufNr[10] = {};
  
    OldMode = Mode;
    ScreenChanged = true;

    TFT.loadFont(AA_FONT_LARGE);
    
    TFT.setTextColor(TFT_RUBICON, TFT_BLACK);
    TFT.setTextPadding(469);
    TFT.setTextDatum(TL_DATUM);

    TFT.drawString("Status...", 10, 10);
    TFT.unloadFont();

    TFT.loadFont(AA_FONT_SMALL);
    TFT.setTextColor(TFT_WHITE, TFT_BLACK);
    
    int h=20;
    for(int SNr=0; SNr<MAX_STATUS; SNr++) {
      char Buf[20];
      TFT.drawString(Buf, 10, 40+(SNr+1)*h);
      TFT.drawString(Status[SNr].Msg, 75, 40+(SNr+1)*h);
    }
    TFT.unloadFont();
    TFT.setTextPadding(0);
    #endif
    
    TSScreenRefresh = millis();
  }
}
#pragma endregion Screens
#pragma region Touch-Things
#ifdef TOUCH911_USED //int TouchRead()
int   TouchRead() {
  uint16_t TouchX, TouchY;
  uint8_t  Gesture;
  bool TouchContact;

  int ret = 0;

  tp.read();
  
  Touch.Touched = tp.isTouched;
  TouchX = tp.points[0].x;
  TouchY = tp.points[0].y;
  
  if(Touch.Touched && !Touch.TouchedOld) {
    Touch.x0 = TouchX;    // erste Berührung
    Touch.y0 = TouchY;
    Touch.TSFirstTouch = millis();
    Touch.TSReleaseTouch = 0;
    ret = TOUCHED;
  } 
  else if (Touch.Touched && Touch.TouchedOld) { 
    Touch.x1 = TouchX;     // gehalten
    Touch.y1 = TouchY;
    ret = HOLD;
  }
  else if (!Touch.Touched && Touch.TouchedOld) {
    Touch.x1 = TouchX;     // losgelassen
    Touch.y1 = TouchY;
    Touch.TSReleaseTouch = millis();
         if ((Touch.x1-Touch.x0) > 50)  { Touch.Gesture = SWIPE_RIGHT;  ret = SWIPE_RIGHT; }                      // swipe left
    else if ((Touch.x1-Touch.x0) < -50) { Touch.Gesture = SWIPE_LEFT; ret = SWIPE_LEFT; }                     // swipe right
    else if ((Touch.y1-Touch.y0) > 50)  { Touch.Gesture = SWIPE_DOWN;  ret = SWIPE_DOWN; }                      // swipe down
    else if ((Touch.y1-Touch.y0) < -50) { Touch.Gesture = SWIPE_UP;    ret = SWIPE_UP; }                        // swipe up
    else if ((Touch.TSReleaseTouch - Touch.TSFirstTouch) > LONG_PRESS_INTERVAL)                                 // longPress
                                        { Touch.Gesture = LONG_PRESS;  ret = LONG_PRESS; }
    else                                { Touch.Gesture = CLICK; ret = CLICK; }
  }
  else if (!Touch.Touched && !Touch.TouchedOld) {
    Touch.x0 = 0;    // nix
    Touch.y0 = 0;
    Touch.x1 = 0;
    Touch.y1 = 0;
    Touch.Gesture = 0;
    Touch.TSFirstTouch = 0;
    Touch.TSReleaseTouch = 0;
    ret = 0;
  }
  Touch.TouchedOld = Touch.Touched;  

  return ret;
}
#endif
#pragma endregion Touch-Things
#pragma region OnDataRecv
#ifdef ESP32  
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {  
#elif defined(ESP8266)
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
#endif
  char* buff = (char*) incomingData;        //char buffer
  StaticJsonDocument<500> doc;
  String jsondata;
  doc.clear();
  jsondata = "";
  bool PairingSuccess = false;
  
  jsondata = String(buff);                  //converting into STRING
  
  Serial.print("Recieved from: "); PrintMAC(mac); 
  
  DeserializationError error = deserializeJson(doc, jsondata);
  
  if (!error) {
    String TempName = doc["Node"];
    Serial.print("("); Serial.print(TempName); Serial.print(") - ");
    Serial.println(jsondata);    
    
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
            RegisterPeers();
            
            if (DebugMode) {
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
    if      (doc["Order"] == "stay alive")       { TSLastContact = millis();
                                                   if (DebugMode) { Serial.print("LastContact: "); Serial.println(TSLastContact); }
                                                 }
    else if (doc["Order"] == "SleepMode On")     { AddStatus("Sleep: on");  SetSleepMode(true);  SendMessage(); }
    else if (doc["Order"] == "SleepMode Off")    { AddStatus("Sleep: off"); SetSleepMode(false); SendMessage(); }
    else if (doc["Order"] == "SleepMode Toggle") { if (SleepMode) { AddStatus("Sleep: off");   SetSleepMode(false); SendMessage(); }
                                                             else { AddStatus("Sleep: on");    SetSleepMode(true);  SendMessage(); }
                                                 } 
    else if (doc["Order"] == "DebugMode on")     { AddStatus("DebugMode: on");  SetDebugMode(true);  SendMessage(); }
    else if (doc["Order"] == "DebugMode off")    { AddStatus("DebugMode: off"); SetDebugMode(false); SendMessage(); }
    else if (doc["Order"] == "Debug Toggle")     { if (DebugMode) { AddStatus("DebugMode: off");   SetDebugMode(false); SendMessage(); }
                                                             else { AddStatus("DebugMode: on");    SetDebugMode(true);  SendMessage(); }
                                                 }
    else if (doc["Order"] == "DemoMode on")      { AddStatus("Demo: on");   SetDemoMode(true);   SendMessage(); }
    else if (doc["Order"] == "DemoMode off")     { AddStatus("Demo: off");  SetDemoMode(false);  SendMessage(); }
    else if (doc["Order"] == "DemoMode Toggle")  { if (DemoMode) { AddStatus("DemoMode: off"); SetDemoMode(false); SendMessage(); }
                                                            else { AddStatus("DemoMode: on");  SetDemoMode(true);  SendMessage(); }
                                              }
    else if (doc["Order"] == "Reset")         { AddStatus("Clear all"); ClearPeers(); ClearInit(); ESP.restart(); }
    else if (doc["Order"] == "Restart")       { ESP.restart(); }
    else if (doc["Order"] == "Pair")          { TSPair = millis(); ReadyToPair = true; AddStatus("Pairing beginnt"); SendMessage(); }

    else if (doc["Order"] == "Eichen")        { Mode = S_EICHEN;  AddStatus("Eichen beginnt");    ShowEichen(); }
    else if (doc["Order"] == "VoltCalib")     { Mode = S_CAL_VOL; AddStatus("VoltCalib beginnt"); ShowVoltCalib((float)doc["Value"]); }
    else if (doc["Order"] == "ToggleSwitch")  { for (int SNr=0; SNr<MAX_PERIPHERALS; SNr++) {
                                                  if ((S[SNr].Name == doc["Value"]) and (S[SNr].Type == SENS_TYPE_SWITCH)) {
                                                    S[SNr].Value = !S[SNr].Value; 
                                                    String Nr = doc["Value"];
                                                    AddStatus("ToggleSwitch "+Nr);
                                                    UpdateSwitches();
                                                  }
                                                }
                                              }      
  } // end (!error)
  else {  // error
        Serial.print(F("deserializeJson() failed: "));  //Just in case of an ERROR of ArduinoJSon
        Serial.println(error.f_str());
  }
}
#pragma endregion OnDataRecv
#pragma region OnDataSent
#ifdef ESP32 //void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) { 
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
#elif defined(ESP8266)
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
#endif
#pragma endregion OnDataSent