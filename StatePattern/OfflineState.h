#ifndef OFFLINESTATE_H
#define OFFLINESTATE_H

#include "State.h"

class OfflineState : public State {
 public:
  virtual void Connect() override;

  void CheckConnection() override;
  void setMyAttribute(float x) override;
};

#endif
