#ifndef CONLINESTATE_H
#define CONLINESTATE_H

#include "CState.h"

typedef struct OnlineState OnlineState;
struct OnlineState {
  State state;

  void (*Connect)(OnlineState *onlineState);
  void (*CheckConnection)(OnlineState *onlineState);
  void (*setMyAttribute)(OnlineState *onlineState, float x);
};

#endif
