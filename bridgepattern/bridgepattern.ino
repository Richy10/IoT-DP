/*
 * Decouple an abstraction from its implementation so that the two can vary independently.
 * Use the Bridge pattern when
· you want to avoid a permanent binding between an abstraction and its
  implementation. This might be the case, for example, when the implementation
  must be selected or switched at run-time.

 * both the abstractions and their implementations should be extensible by
  subclassing. In this case, the Bridge pattern lets you combine the different
  abstractions and implementations and extend them independently.
  
·* changes in the implementation of an abstraction should have no impact on
  clients; that is, their code should not have to be recompiled.\
  
·* (C++) you want to hide the implementation of an abstraction completely from
  clients. In C++ the representation of a class is visible in the class
    interface.

 */
#include "SensorDHT.h"
#include "SensorLight.h"
#include <list>

std::list<ISensor *> Sensors;

SensorDHT   *d_sensor;
SensorLight *l_sensor;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\Start\n");
  
 // d_sensor = new SensorDHT(DHT11,4); this is for ESP?
//  l_sensor = new SensorLight(LIGHT,2);
  //d_sensor = new SensorDHT(DHT11,14);
  l_sensor = new SensorLight(LIGHT,26);
  
}

void loop() {
  
  delay(3000);
  //d_sensor->read_sensor();
  Serial.println("Im Alive");
  //Serial.println("Current temp: " + String( d_sensor->get_data(0) ) );
  l_sensor->read_sensor();
  Serial.println("Current light: " + String( l_sensor->get_data(0) ) );
  

}
