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
#include "SensorReader.h" // Include the new SensorReader.h
#include <list>

std::list<SensorReader *> SensorReaders; // list of SensorReader objects instead of ISensor

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\Start\n");
  
  // Create SensorReader objects for each sensor
  SensorReaders.push_back(new SensorReader(new SensorDHT(DHT11,14), "Temperature"));
  SensorReaders.push_back(new SensorReader(new SensorLight(LIGHT,26), "Light"));
}

void loop() {
  
  delay(3000);
  
  Serial.println("Im Alive");
  // Now you iterate over each SensorReader object and call their methods
  for (SensorReader *reader : SensorReaders) {
    reader->readSensor();
    Serial.println("Current " + reader->getName() + ": " + String(reader->getData(0)));
  }
}
