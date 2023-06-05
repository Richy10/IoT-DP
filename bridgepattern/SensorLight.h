#include "Sensor.h"

class SensorLight : public ISensor
{
  private:
    float data;
    int gpio_connect;
    byte sensor;
    
  public:
    SensorLight(byte sensor,int gpio_connect)
    {
      this->sensor=sensor;
      this->gpio_connect=gpio_connect;
    }

    void read_sensor()
    { 
      data= (analogRead(gpio_connect)) / 4;   
    }
    
    float get_data(int index)
    {
      if(index<1)
      {
        return data;
      }      
      return 0;
    }
    
    byte get_type()
    {
      return sensor;
    }
};
