#include "Observer.h"
#include "Subject.h"
#include "Sensor.h"

#include <list>;
#include <ranges>;


class WeatherData : public ISubject 
{
 private:
 
    std::list<IObserver *> Observers;
    std::list<ISensor *> *Sensors;
    float temperature;
    float humidity;
    float pressure;
    
 public:
  
  WeatherData(std::list<ISensor *>* Sensors)
  {
    this->Sensors=Sensors;    
  }

  void registerObserver( IObserver *o ) override 
  {   
      Observers.push_back( o );  
  }
  
  void removeObserver( IObserver *o ) override 
  {
      Observers.remove( o );
  }
  
  void notifyObservers( ) override 
  {
      std::list<IObserver *>::iterator observer; 
    
      for( observer = Observers.begin(); observer != Observers.end(); ++observer) 
      { 
          (*observer)->update( );
      }
  }


  void measurementsChanged() 
  {
      notifyObservers();
  }

  void setMeasurements() 
  {
    std::list<ISensor *>::iterator sensor; 
    for( sensor = (*Sensors).begin(); sensor != (*Sensors).end(); ++sensor) 
    { 
      (*sensor)->read_sensor();
    }
    measurementsChanged();
  }

  float getDataSensor(byte sensorType,int index_data, int index)
  {    
    std::list<ISensor *>::iterator sensor; 
    std::list<ISensor*> matches= getSensorsByType(sensorType);
    int i=0;
    if(matches.size()>0)
    {
      for( sensor = matches.begin(); sensor != matches.end(); ++sensor)
      { 
          if(i==index)
          {
            return (*sensor)->get_data(index_data);            
          }
          i++;
      }    
    }  
    return 0;  
  } 
  
  std::list<ISensor *> getSensorsByType(byte sensorType)
  { 
    std::list<ISensor*> matches;
    std::copy_if((*Sensors).begin(), (*Sensors).end(), std::back_inserter(matches), [&](ISensor* s) 
    {
        return s->get_type() == sensorType;
    });
    return matches;  
  }
};
