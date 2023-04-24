#include "OnlineState.h"
#include "OfflineState.h"

void OnlineState::Connect() {
  {
   Serial.println("Already connected");
  }
}

void OnlineState::CheckConnection(){
    Serial.println("Check connection from onlineState called");
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("Disconnected!");
        this->context_->TransitionTo(new OfflineState);
    }
}


 void OnlineState::setMyAttribute(float x){
    CheckConnection();

  }