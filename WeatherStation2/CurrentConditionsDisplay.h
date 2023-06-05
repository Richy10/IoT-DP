#include "IDisplayElement.h"
#include "Observer.h"
#include "Sensor.h"

class CurrentConditionsDisplay : public IObserver , public IDisplayElement 
{  
  private:
      float temperature;
      float humidity;
      float pressure;
      WeatherData *weatherData;
  
  public:
  
    CurrentConditionsDisplay( WeatherData *weatherData ) 
    {
   
      this->weatherData = weatherData;
      weatherData->registerObserver( this );

    }
  
    void update() override 
    {  
        this->temperature = weatherData->getDataSensor(DHT11,TEMP,0);
        this->humidity = weatherData->getDataSensor(DHT11,HUM,0);
        this->pressure = weatherData->getDataSensor(PRESSURE,DEFAULT,0);
        display();
    }
  
    void display() override 
    {  
        Serial.print("Current conditions: " + String( temperature ) );
        Serial.print(" *C degrees with " + String( humidity ) + " % humidity and ");
        Serial.println(String( pressure ) + " % of pressure");
    } 
};
