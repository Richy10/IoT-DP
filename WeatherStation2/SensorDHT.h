#include "Sensor.h"

#define DATA_SIZE 2

//TIPO DE DATO PARA RECIBIR EL FRAME DE DATOS DEL SENSOR
typedef union{
  uint64_t data;
  uint8_t frame[8];
}Frame;

class SensorDHT : public ISensor
{
  private:
    volatile uint32_t duracion,tiempo_Fin,tiempo_Ini;
    volatile uint8_t i;
    Frame data_frame;
    float data[DATA_SIZE]; // 0:Temperatura  1:Humedad    
    float temp,hum;
    float divisor;
    int flag;/*BANDERA DE VALIDACION DE DATOS*/
    int gpio_connect;
    byte sensor;
    
  public:
    SensorDHT(byte sensor,int gpio_connect)
    {
      this->sensor=sensor;
      this->gpio_connect=gpio_connect;
    }

    void read_sensor()
    { 
      i=0;
      data_frame.data=0;  
      delay(1500);  
      start_host();
      get_frame();      
    }
    
    void start_host()
    {  
      //ESTABLECER EL PIN COMO SALIDA SIN PULL_UP  
      //pullUpDnControl(gpio_connect,PUD_OFF);
      pinMode(gpio_connect,OUTPUT);   
      //18 ms EN BAJO 
      digitalWrite(gpio_connect,LOW);
      delay(18);  
      //20-40us EN ALTO
      digitalWrite(gpio_connect,HIGH);
      delayMicroseconds(22 ); 
    }

    void get_frame()
    {
      pinMode(gpio_connect, INPUT);
      //pullUpDnControl(gpio_connect,PUD_UP);  
      //ESPERAR HASTA QUE EL SENSOR RESPONDA
      while(digitalRead(gpio_connect));  
      // 80us EN BAJO
      while(!digitalRead(gpio_connect));   
      // 80us EN ALTO
      while(digitalRead(gpio_connect));
      //INICIA FRAME DE DATOS
      //Serial.printf("\n\r START FRAME");  
      while(i<40)
      {
        while(!digitalRead(gpio_connect));    
        tiempo_Ini=micros();
        while(digitalRead(gpio_connect));
        tiempo_Fin=micros();
        duracion= tiempo_Fin-tiempo_Ini;
        data_frame.data<<=1;
        if(duracion>=10 && duracion<=35)
        {
          //0
        }
        else
        {
          if(duracion>35 && duracion<=110){data_frame.data+=1;}
          else{
          //Frame Error
          }
        }
        i++;      
      }
      write_data();
    }

    void write_data(){
      //DESPLEGAR EN CONSOLA LA CANTIDAD DE BITS DEL FRAME, 40BITS    
      /*
            +-------+-------+
            | DHT11 | DHTXX |
            +-------+-------+
      Temp C| 0-50  |-40-125|
            +-------+-------+
      RH%   | 20-80 | 0-100 |
            +-------+-------+  
             0      1      2      3      4
            +------+------+------+------+------+
      DHT11 |check-| 0    | temp |  0   | RH%  |
            |sum   |      |      |      |      |
            +------+------+------+------+------+
      DHT21 |check-| temp | temp | RH%  | RH%  |
      DHT22 |sum   | LSB  | MSB  | LSB  | MSB  |
            +------+------+------+------+------+
      */   
      //FRAME[0]==CHECKSUM
      //COMPARAR SI EL CHECKSUM ES CORRECTO
      if(data_frame.frame[0]==((data_frame.frame[1]+data_frame.frame[2]+data_frame.frame[3]+data_frame.frame[4])&0xFF)){
        if(sensor==DHT11)
        {
          //DHT11        
          flag=1;  
          hum=(float)(data_frame.frame[4]); 
          temp=(data_frame.frame[2]);        
          if((hum < 10.0) || (hum > 90.0)){flag=0;}
          if(temp > 60.0){flag=0;}                             
        }
        if(sensor==DHT22)
        {
          //DHT22
          flag=1;       
          //AJUSTE DE DATOS
          hum=((float)((data_frame.frame[4]<<8)+data_frame.frame[3]))/10.0; 
          divisor=(data_frame.frame[2]&128) ? -10.0 :10.0;
          temp=(((data_frame.frame[2]&127)<<8)+data_frame.frame[1])/divisor;        
          //VERIFICACION LOS RESULTADOS, 0 IGUAL A INVALIDO/INCORRECTO
          if(hum>110.0){flag=0;}
          if((temp<-50.0) || (temp>135.0)){flag=0;}            
        }
        if(flag)
        {
          data[0]=(float)temp;
          data[1]=(float)hum;
        }
      }
      else{
        //FAIL CHECKSUM
      }
    }
    
    float get_data(int index)
    {
      if(index<DATA_SIZE)
      {
        return data[index];
      }      
      return 0;
    }
    
    byte get_type()
    {
      return sensor;
    }
};
