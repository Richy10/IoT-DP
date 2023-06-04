#ifndef CCONTEXT_H
#define CCONTEXT_H


#include "State.h"
typedef struct State State;

typedef struct Context Context;
struct Context {
  // @var State A reference to the current state of the Context.
  State *state_;
  float sensorData;

  Context(State *state) : state_(nullptr) {
    this->TransitionTo(state);
  }
  ~Context() {
    delete state_;
  }

  // The Context allows changing the State object at runtime.
  void TransitionTo(Context *context, State *state);

  // The Context delegates part of its behavior to the current State object.
  void Connect(Context *context);

  void CheckConnection(Context *context);
  
  void setMyAttribute(Context *context, float x);
};

#endif
