#include "IDisplayElement.h"
#include "Observer.h"
#include "Sensor.h"

class StatisticsDisplay : public IObserver , public IDisplayElement 
{
  private:
    float maxTemp = 0.0;
    float minTemp = 200;
    float tempSum= 0.0;
    float temp = 0.0;
    int numReadings= 0;
    WeatherData *weatherData;

  public:
    StatisticsDisplay(WeatherData *weatherData)
    {
      this->weatherData = weatherData;
      weatherData->registerObserver(this);
    }

    void update() override 
    {
      temp = weatherData->getDataSensor(DHT11,TEMP,0);
      tempSum += temp;
      numReadings++;
    
      if (temp > maxTemp) {
        maxTemp = temp;
      }    
      if (temp < minTemp) {
        minTemp = temp;
      }
    
      display();
    }
    
    void display() override 
    {
      Serial.println("Avg/Max/Min temperature = " + String(tempSum / numReadings) + "/" + String(maxTemp) + "/" + String(minTemp));
    }
};
