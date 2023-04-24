#ifndef CONTEXT_H
#define CONTEXT_H


#include "State.h"
class State;

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
  void TransitionTo(State *state);

  // The Context delegates part of its behavior to the current State object.
  void Connect();

  void CheckConnection();
  
  void setMyAttribute(float x);
};

#endif
