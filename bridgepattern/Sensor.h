#ifndef ISENSOR_h
#define ISENSOR_h

#include <inttypes.h>
#define DHT11 0
#define DHT22 1
#define PRESSURE 2
#define LIGHT 3

#define DEFAULT 0
#define TEMP 0
#define HUM 1


class ISensor
{
 public:
  virtual void read_sensor() = 0;
  virtual float get_data(int index) = 0;
  virtual byte get_type() = 0;
};



#endif
