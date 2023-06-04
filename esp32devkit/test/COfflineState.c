#include "COfflineState.h"
#include "COnlineState.h"

void OfflineState_Connect(OfflineState *offlineState) {
  Serial.println("connect from offlineState called");
  WiFi.begin(ssid, password);
  Serial.print("Connecting to wifi...");
  for(int i = 0; i<10;i++){
    if(WiFi.status() != WL_CONNECTED){
      Serial.print('.');
      vTaskDelay(connectionDelay);
    }
    else {
      i = 10;
      Serial.println();
      Serial.println("Connected !");
      offlineState->context_->TransitionTo(new OnlineState);
    }
  }
}

void OfflineState_CheckConnection(OfflineState *offlineState) {
  Serial.println("Check connection from offlinestate called");

  //std::cout << "OfflineState: Connection is inactive.\n";
}

void OfflineState_setMyAttribute(OfflineState *offlineState, float x) {
  offlineState->context_->setMyAttribute(3);
}