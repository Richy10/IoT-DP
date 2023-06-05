#include "IDisplayElement.h"
#include "Observer.h"
#include "Sensor.h"

class ForecastDisplay  : public IObserver , public IDisplayElement 
{ 
  private:
    float currentPressure = 29.92;  
    float lastPressure;
    WeatherData *weatherData;

  public:
  
    ForecastDisplay(WeatherData *weatherData) 
    {
      this->weatherData = weatherData;
      weatherData->registerObserver(this);
    }
  
    void update() override
    {
      lastPressure = currentPressure;
      currentPressure = weatherData->getDataSensor(PRESSURE,DEFAULT,0);    
      display();
    }
  
    void display() override
    {
      Serial.print("Forecast: ");
      if      (currentPressure > lastPressure)  {  Serial.println("Improving weather on the way!");} 
      else if (currentPressure == lastPressure) {  Serial.println("More of the same");} 
      else if (currentPressure < lastPressure)  {  Serial.println("Watch out for cooler, rainy weather");}
    }
};
