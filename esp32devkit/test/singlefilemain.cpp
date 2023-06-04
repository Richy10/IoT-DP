#include <iostream>
#include <typeinfo>
#include <WiFi.h>
#include <WiFiClientSecure.h>

// The base State class declares methods that all Concrete State should
// implement and also provides a backreference to the Context object, associated
// with the State. This backreference can be used by States to transition the
// Context to another State.

const char* ssid = "INFINITUM3E5F_2.4";
const char* password = "ffzWfUzD73";
unsigned long lastTime = 0;
const unsigned long timerDelay = 15000;
int flag = 0;
const TickType_t connectionDelay = 1500 / portTICK_PERIOD_MS;

WiFiClientSecure client;

class State {
  // @var Context
 protected:
  Context *context_;

 public:
  virtual ~State() {}

  void set_context(Context *context) {
    this->context_ = context;
  }

  virtual void Connect() = 0;
  virtual void CheckConnection() = 0;
  virtual void setMyAttribute(float x) = 0;
  //virtual void Measure() = 0;
  //virtual void setMeasurement(float x) = 0;

};

// The Context defines the interface of interest to clients. It also maintains a
// reference to an instance of a State subclass, which represents the current
// state of the Context.

class Context {
  // @var State A reference to the current state of the Context.
 private:
  State *state_;

 public:
 float sensorData = 0;

  Context(State *state) : state_(nullptr) {
    this->TransitionTo(state);
  }
  ~Context() {
    delete state_;
  }

  // The Context allows changing the State object at runtime.
  void TransitionTo(State *state) {
    Serial.println("Transitioning");
    if (this->state_ != nullptr)
      delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
  }

  // The Context delegates part of its behavior to the current State object.
  void Connect() {
    this->state_->Connect();
  }
  void CheckConnection() {
    this->state_->CheckConnection();
  }

  void setMyAttribute(float x){
    this->state_->setMyAttribute(x);
  }

};

// Concrete States implement various behaviors, associated with a state of the
// Context.

class OfflineState : public State {
 public:
  virtual void Connect() override {
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

  void CheckConnection() override {

    Serial.println("Check connection from offlinestate called");

    //std::cout << "OfflineState: Connection is inactive.\n";
  }

  void setMyAttribute(float x) override {
    CheckConnection();
  }

};

class OnlineState : public State {
 public:
  void Connect() override{
    Serial.println("Already connected");

    //std::cout << "OnlineState: .\n";
  }

  void CheckConnection() override {
    Serial.println("Check connection from onlineState called");
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("Disconnected!");
        this->context_->TransitionTo(new OfflineState);
    }
  }
  
  void setMyAttribute(float x) override {
    CheckConnection();

  }


};

//void OfflineState::

Context *context = new Context(new OfflineState);

/*
void OnlineState::Connect() {
  {
    std::cout << "OnlineState: Already connected.\n";
  }
}
*/
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