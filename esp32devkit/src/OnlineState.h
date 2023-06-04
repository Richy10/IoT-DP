#ifndef ONLINESTATE_H
#define ONLINESTATE_H

#include "State.h"

class OnlineState : public State {
 public:
  void Connect() override;

  void CheckConnection() override;
  
  void setMyAttribute(float x) override;


};

#endif
