  #include "Context.h"
  #include "State.h"
  //Singleton state
  void Context::TransitionTo(State *state) {
    Serial.println("Transitioning");
    if (this->state_ != nullptr)
      delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
  }

   void Context::Connect() {
    this->state_->Connect();
  }

    void Context::CheckConnection() {
    this->state_->CheckConnection();
  }

  
  void Context::setMyAttribute(float x){
    this->state_->setMyAttribute(x);
  }
