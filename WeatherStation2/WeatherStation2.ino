#include "SensorDHT.h"
#include "SensorPressure.h"
#include "SensorLight.h"

#include "WeatherData.h"
#include "CurrentConditionsDisplay.h"
#include "StatisticsDisplay.h"
#include "ForecastDisplay.h"

//Clear una Clase/interfaz para los sensores: <Sensor>
//Definir metodos de para realizar lecturas y obtener los datos
//Cambiar la declaracion del metodo update<Observer.h>
//Eliminar las variables float en <WeatherData.h> y remplazarlas con una lista de objetos del tipo <Sensors>
//Cambiar la declaracion setMeasurements <WeatherData.h> y que su implementacion sea con <Sensors>.
//Eliminar los metodos Get de <WeatherData.h> y remplazar con un metodo que reciba parametros para obtener los datos de un sensor dentro de la lista de objetos del tipo <Sensors>.
//Crear Clases que implementen la interfaz <Sensors>
//Cambiar la implemetacion del metodo update deacuerdo con las clases que implementaron la interfaz <Sensors> y <WeatherData.h> 
//Falta Validar en los observadores cuando un sensor no existe o fue removido


WeatherData *weatherData;
CurrentConditionsDisplay *currentConditions;
StatisticsDisplay *statisticsDisplay;
ForecastDisplay *forecastDisplay;

std::list<ISensor *> Sensors;

SensorDHT *d_sensor;
SensorLight * l_sensor;
SensorPressure * p_sensor1;
SensorPressure * p_sensor2;


void setup ()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\Start\n");
  
  d_sensor= new SensorDHT(DHT11,4);
  l_sensor= new SensorLight(LIGHT,5);
  p_sensor1= new SensorPressure(PRESSURE,3);
  p_sensor2= new SensorPressure(PRESSURE,6);
  Sensors.push_back( d_sensor );  
  Sensors.push_back( l_sensor );  
  Sensors.push_back( p_sensor1 );    
  Sensors.push_back( p_sensor2 );  

  
  weatherData = new WeatherData(&Sensors);  
  currentConditions = new CurrentConditionsDisplay( weatherData ) ;
  statisticsDisplay = new StatisticsDisplay( weatherData );
  forecastDisplay = new ForecastDisplay( weatherData );
}

void loop() 
{
  weatherData->setMeasurements(); //Cambia los parametros a una lista de CustomSensors
}
