#ifndef COFFLINESTATE_H
#define COFFLINESTATE_H

#include "CState.h"

typedef struct OfflineState OfflineState;
struct OfflineState {
State state;

void (*Connect)(OfflineState *offlineState);
void (*CheckConnection)(OfflineState *offlineState);
void (*setMyAttribute)(OfflineState *offlineState, float x);
};

#endif