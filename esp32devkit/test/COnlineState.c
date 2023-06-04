#include "COnlineState.h"
#include "COfflineState.h"

void OnlineState_Connect(OnlineState *onlineState) {
  {
   Serial.println("Already connected");
  }
}

void OnlineState_CheckConnection(OnlineState *onlineState){
  Serial.println("Check connection from onlineState called");
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Disconnected!");
    onlineState->context_->TransitionTo(new OfflineState);
  }
}

void OnlineState_setMyAttribute(OnlineState *onlineState, float x){
  OnlineState_CheckConnection(onlineState);
}
