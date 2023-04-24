#include "IDisplayElement.h"
#include "Observer.h"
#include "Sensor.h"

struct_message myData;

class CurrentConditionsDisplay : public IObserver , public IDisplayElement 
{  
  private:
      float temperature;
      float humidity;
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
        display();
    }
  
    void display() override 
    {  
        strcpy(myData.a, "Message !");
        //d_sensor->read_sensor();
        myData.b = this->temperature;

        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
        
        if (result == ESP_OK) {
            Serial.println("Sent with success");
        }
        else {
            Serial.println("Error sending the data");
        }

    } 
};