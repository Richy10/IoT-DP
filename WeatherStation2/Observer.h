#ifndef IOBSERVER_h
#define IOBSERVER_h
#include "Sensor.h"

class IObserver 
{
 public:
  virtual void update( ) = 0;
};

#endif
