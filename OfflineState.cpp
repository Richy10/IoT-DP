#include "OfflineState.h"
#include "OnlineState.h"

void OfflineState::Connect(){
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
            this->context_->TransitionTo(new OnlineState);
        }
    }
  }

   void OfflineState::CheckConnection(){

    Serial.println("Check connection from offlinestate called");

    //std::cout << "OfflineState: Connection is inactive.\n";
  }

    void OfflineState::setMyAttribute(float x){
    this->context_->setMyAttribute(3);
  }
