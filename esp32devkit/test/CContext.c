#include "CContext.h"
#include "CState.h"

void Context_TransitionTo(Context *context, State *state) {
  Serial.println("Transitioning");
  if (context->state_ != nullptr)
    delete context->state_;
  context->state_ = state;
  context->state_->set_context(context);
}

void Context_Connect(Context *context) {
  context->state_->Connect();
}

void Context_CheckConnection(Context *context) {
  context->state_->CheckConnection();
}

void Context_setMyAttribute(Context *context, float x) {
  context->state_->setMyAttribute(x);
}
