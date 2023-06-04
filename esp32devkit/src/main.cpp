#include <iostream>
#include <typeinfo>
#include "Context.h"
#include "State.h"
#include "OfflineState.h"

// The base State class declares methods that all Concrete State should
// implement and also provides a backreference to the Context object, associated
// with the State. This backreference can be used by States to transition the
// Context to another State.


unsigned long lastTime = 0;
const unsigned long timerDelay = 15000;

// The Context defines the interface of interest to clients. It also maintains a
// reference to an instance of a State subclass, which represents the current
// state of the Context.

Context *context = new Context(new OfflineState);


// Concrete States implement various behaviors, associated with a state of the
// Context.


void setup() {

    WiFi.mode(WIFI_STA);
    lastTime = millis();
    Serial.begin(115200);
    context->Connect();
    context->CheckConnection();
    //context->
    //delete context;
}

void loop(){
      if(millis() > (lastTime + timerDelay)){
        
        context->CheckConnection();
        lastTime = millis();
      }
}