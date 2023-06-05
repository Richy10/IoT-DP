#include "Sensor.h"

class SensorPressure : public ISensor
{
  private:
    float data;
    int gpio_connect;
    byte sensor;
    
  public:
    SensorPressure(byte sensor,int gpio_connect)
    {
      this->sensor=sensor;
      this->gpio_connect=gpio_connect;
      this->data=32;
    }

    void read_sensor()
    { 
      data+=1;   
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
