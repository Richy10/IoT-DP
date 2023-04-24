#ifndef STATE_H
#define STATE_H

#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "Context.h"
class Context;
static const TickType_t connectionDelay = 1500 / portTICK_PERIOD_MS;
static WiFiClientSecure client;

static const char* ssid = "INFINITUM3E5F_2.4";
static const char* password = "ffzWfUzD73";


class State
{
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
#endif
