#ifndef IOBSERVER_h
#define IOBSERVER_h
#include "Sensor.h"
#include <esp_now.h>

typedef struct struct_message {
  char a[32];
  float b;
} struct_message;

typedef struct struct_subscribe{
  char a[32];
}struct_subscribe;

uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x38, 0x53, 0x5C};

esp_now_peer_info_t peerInfo;
class IObserver 
{
 public:
  virtual void update( ) = 0;
};

#endif