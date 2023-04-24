//#include <esp_now.h>
#include <WiFi.h>
#include "SensorDHT.h"
#include "SensorLight.h"
#include "WeatherData.h"
#include "CurrentConditionsDisplay.h"

WeatherData *weatherData;
CurrentConditionsDisplay *currentConditions;
std::list<ISensor *> Sensors;

SensorDHT *d_sensor;
SensorLight * l_sensor;

// REPLACE WITH YOUR RECEIVER MAC Address

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 10000;        // Interval at which to publish sensor readings

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\n Packet Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
/*
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.println("DATA RECEIVEDDDD");
  memcpy(&myDataReceived, incomingData, sizeof(myDataReceived));
  Serial.print("Reception: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myDataReceived.a);
  Serial.println();
}*/
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Error");
    return;

  }
  
  d_sensor= new SensorDHT(DHT11,4);
  l_sensor= new SensorLight(LIGHT,2);
  Sensors.push_back( d_sensor );  
  Sensors.push_back( l_sensor );

  /*esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);*/
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
    
  weatherData = new WeatherData(&Sensors);  
  currentConditions = new CurrentConditionsDisplay( weatherData ) ;
}


void loop() {
  unsigned long currentMillis = millis();
  // Every X number of seconds (interval = 10 seconds) 
  // it publishes a new MQTT message
  if (currentMillis - previousMillis >= interval) {


  weatherData->setMeasurements(); //Cambia los parametros a una lista de CustomSensors

  strcpy(myData.a, "Message !");
  //d_sensor->read_sensor();
  myData.b = random(1,20);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
    previousMillis = currentMillis;
    }
}