#include "read_sensors.h"
Adafruit_BMP280 bmp; // Crea una instancia de la clase BMP280

//#include <Wire.h>
//#include <Adafruit_BMP085.h>
//Adafruit_BMP085 bmp;
int time_delay_process = 1;
int time_delay_process_Multi = 1;
Adafruit_AHTX0 aht;//sensor temperatura 
const uint8_t Addr_SHT21 = 0x40;


void read_HDC1080()
{
  
}
void read_BMP280(int sensor)
{
  TCA9548A(sensor);
  delay_multi();
  if (!bmp.begin(0x76)) { // La dirección I2C del BMP280 puede ser 0x76 o 0x77, dependiendo de cómo hayas conectado los pines SDO
    Serial.println("No se ha encontrado un sensor BMP280. Verifica las conexiones.");
  }
  else
  { 
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure() / 100.0F; // La presión se suele dar en hPa
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Presión: ");
    Serial.print(pressure);
    Serial.println(" hPa");

    delay(1000);
  }
}
int read_BMP280_temp(int sensor)
{
  TCA9548A(sensor);
  delay_multi();
  if (!bmp.begin(0x76)) { // La dirección I2C del BMP280 puede ser 0x76 o 0x77, dependiendo de cómo hayas conectado los pines SDO
    Serial.println("No se ha encontrado un sensor BMP280. Verifica las conexiones.");
  }
  else
  { 
    float temperature = bmp.readTemperature();
          
    delay(10);
    return (int)(temperature*100);
  }
  return -1;
}
int read_BMP280_pression(int sensor)
{
  TCA9548A(sensor);
  delay_multi();
  if (!bmp.begin(0x76)) { // La dirección I2C del BMP280 puede ser 0x76 o 0x77, dependiendo de cómo hayas conectado los pines SDO
    Serial.println("No se ha encontrado un sensor BMP280. Verifica las conexiones.");
  }
  else
  { 
    //float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure() / 100.0F; // La presión se suele dar en hPa
         
    delay(10);
    return (int)(pressure*100);
  }
  return -1;
}
void delay_i2c()
{
  //delay(time_delay_process);
}
void delay_multi()
{
 delay(time_delay_process_Multi);
}
void TCA9548A(uint8_t bus){

  Wire.begin();
  Wire.setClock(100000);//{10000, 100000, 400000, 1000000};
  Wire.beginTransmission(0x70);  // TCA9548A address L L L
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.println(bus);
}

void configure_HDC1080()
{
//Wire.begin();
  
   Wire.beginTransmission(Addr_HDC1080);
    // Select configuration register
    Wire.write(0x02);
    // Temperature, humidity enabled, resolultion = 14-bits, heater on
    Wire.write(0x30);
    // Stop I2C Transmission
    Wire.endTransmission();
}

int read_Adafruit_AHTX0()
{
  int aud=0;
   if (! aht.begin()) 
  {
    Serial.println("ERROR IN THE ATHX");
    return -1;
  }
  else
  {
    sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("ATX Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" degrees C");
  Serial.print("WTX Humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("% rH");
 
  delay(10);
  return 0;
  }
}
int read_Adafruit_AHTX0_temp()
{
  int aud=0;
   if (! aht.begin()) 
  {
    Serial.println("ERROR IN THE ATHX");
    return -1;
  }
  else
  {
    sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  /*Serial.print("ATX Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" degrees C");
  Serial.print("WTX Humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("% rH");*/
 
  delay(10);
  return (int)(temp.temperature*100);
  }
}
int read_Adafruit_AHTX0_press()
{
  int aud=0;
   if (! aht.begin()) 
  {
    Serial.println("ERROR IN THE ATHX");
    return -1;
  }
  else
  {
    sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  /*Serial.print("ATX Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" degrees C");
  Serial.print("WTX Humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("% rH");
 */
  delay(500);
  return (int)(humidity.relative_humidity*100);
  }
}
int read_humidity_HDC1080(int sensor)
{
Serial.print("SENSOR.*******    :");
   // Serial.print(sensor);
  TCA9548A(sensor);
  delay_multi();
  configure_HDC1080();
      unsigned int data[2]={0,0};
     
    // Starts I2C communication
    
       Wire.beginTransmission(Addr_HDC1080);
    
    // Send temp measurement command
    Wire.write(0x01);//00 E3 tenperatura del otro modulo
    // Stop I2C Transmission
    Wire.endTransmission();
   delay_i2c();
     
    // Request 2 bytes of data
    unsigned long time_0= millis();
     unsigned long time_1=millis();
     while((time_1-time_0)<1000)
     {
       Wire.requestFrom(Addr_HDC1080, 2);
    
       time_1=millis();
       if(Wire.available()==2)
        {
          data[0] = Wire.read();
          data[1] = Wire.read();
          //Serial.println("break");
          break;
        }
        else
        {
        }
     }
    // Convert the data
     //Serial.println("break 2");
    int temp = (data[0] * 256) + data[1];
    float cTemp = (temp / 65536.0) * 165.0 - 40;
 //   float fTemp = cTemp * 1.8 + 32;
     
     int tem_ = (int)(cTemp*100);
    // Output data to serial monitor
    
  /*  Serial.print("Relative Humidity :");
    Serial.print(humidity);
    Serial.println(" %RH");*/
    //Serial.print("humidity in Celsius :");
    //Serial.print(cTemp);
    //Serial.println(" C");
    
    //save_data( cTemp,  humidity);
    if(tem_==141936)
    {
      tem_=-1;
    }
    //delay(1000);
    return tem_;
}

int read_humidity_HDC1080_direct()
{

  
  
  configure_HDC1080();
      unsigned int data[2];
     
    
    // Starts I2C communication
    Wire.beginTransmission(Addr_HDC1080);
    // Send humidity measurement command
    Wire.write(0x01);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay_i2c();
     
    // Request 2 bytes of data
    Wire.requestFrom(Addr_HDC1080, 2);
     
    // Read 2 bytes of data
    // humidity msb, humidity lsb
    if (Wire.available() >= 2)
    {
    data[0] = Wire.read();
    data[1] = Wire.read();
    }
     
    // Convert the data
    float humidity = (data[0] * 256) + data[1];
    humidity = (humidity / 65536.0) * 100.0;
     int humidity_ = (int)(humidity*100);
    // Output data to serial monitor
    /*
    Serial.print("*************************************************************Relative Humidity :");
    Serial.print(humidity);
    Serial.println(" %RH");*/
    /*Serial.print("Temperature in Celsius :");
    Serial.print(cTemp);
    Serial.println(" C");*/
    
    //save_data( cTemp,  humidity);
    if(humidity_==89298)
    {
      humidity_=-1;
    }
    return humidity_;
}

int read_tem_HDC1080(int sensor)
{
 Serial.print("SENSOR.*******    :");
    Serial.print(sensor);
  TCA9548A(sensor);
  delay_multi();
  configure_HDC1080();
      unsigned int data[2]={0,0};
     
    // Starts I2C communication
    if(sensor==0)
    {
      Wire.beginTransmission(Addr_HDC1080_1);
    }
    else
    {
       Wire.beginTransmission(Addr_HDC1080);
    }
    // Send temp measurement command
    Wire.write(0x00);//00 E3 tenperatura del otro modulo
    // Stop I2C Transmission
    Wire.endTransmission();
   delay_i2c();
     
    // Request 2 bytes of data
    unsigned long time_0= millis();
     unsigned long time_1=millis();
     while((time_1-time_0)<1000)
     {
       Wire.requestFrom(Addr_HDC1080, 2);
    
       time_1=millis();
       if(Wire.available()==2)
        {
          data[0] = Wire.read();
          data[1] = Wire.read();
          Serial.println("break");
          break;
        }
        else
        {
        }
     }
    // Convert the data
     Serial.println("break 2");
    int temp = (data[0] * 256) + data[1];
    float cTemp = (temp / 65536.0) * 165.0 - 40;
 //   float fTemp = cTemp * 1.8 + 32;
     
     int tem_ = (int)(cTemp*100);
    // Output data to serial monitor
    
  /*  Serial.print("Relative Humidity :");
    Serial.print(humidity);
    Serial.println(" %RH");*/
    Serial.print("Temperature in Celsius :");
    Serial.print(cTemp);
    Serial.println(" C");
    
    //save_data( cTemp,  humidity);
    if(tem_==141936)
    {
      tem_=-1;
    }
    //delay(1000);
    return tem_;
}


int read_tem_SHT21(int sensor)
{
  // Declarar la variable data antes de usarla
unsigned int data[2] = {0, 0};

 Serial.print("SENSOR.*******    :");
    Serial.print(sensor);
  TCA9548A(sensor);
   delay_multi();
 // Suponiendo que Addr_SHT21 es la dirección I2C del SHT21
  Wire.beginTransmission(Addr_SHT21);
    
  // Enviar comando de medición de temperatura para SHT21
  Wire.write(0xF3); // 0xF3 es el comando de medición de temperatura en modo sin retención
  Wire.endTransmission();
  //delay_i2c();
    
  // Leer datos
  Wire.requestFrom(Addr_SHT21, 2);
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
    
  // Convertir los datos para el SHT21
  
  int rawTemp = ((data[0] << 8) | data[1]) & 0xFFFC;
  float cTemp = -46.85 + 175.72 * (rawTemp / 65536.0);

  int tem_ = (int)(cTemp * 100);


  //delay(1000);
    return tem_;
}

int read_hum_SHT21(int sensor)
{
  unsigned int data[2] = {0, 0};

 Serial.print("SENSOR.*******    :");
    Serial.print(sensor);
  TCA9548A(sensor);
   delay_multi();
 // Suponiendo que Addr_SHT21 es la dirección I2C del SHT21
  // Suponiendo que Addr_SHT21 y delay_i2c() ya están definidos
  Wire.beginTransmission(Addr_SHT21);

  // Enviar comando de medición de humedad para SHT21
  Wire.write(0xF5); // 0xF5 es el comando de medición de humedad en modo sin retención
  Wire.endTransmission();
 // delay_i2c();

  // Leer datos
  Wire.requestFrom(Addr_SHT21, 2);
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convertir los datos para el SHT21
  // Convertir los datos para el SHT21


  int rawHumidity = ((data[0] << 8) | data[1] ) & 0xFFFC;
  float humidity = -6 + 125 * (rawHumidity / 65536.0);

  int hum_ = (int)(humidity * 100);


    return hum_;
}
int read_tem_HDC1080_direct()
{

  
  configure_HDC1080();
      unsigned int data[2]={0,0};
     
    // Starts I2C communication
    Wire.beginTransmission(Addr_HDC1080);
    // Send temp measurement command
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay_i2c();
     
    // Request 2 bytes of data
    
 unsigned long time_0= millis();
     unsigned long time_1=millis();
     while((time_1-time_0)<1000)
     {
       Wire.requestFrom(Addr_HDC1080, 2);
    
       time_1=millis();
       if(Wire.available()==2)
        {
          data[0] = Wire.read();
          data[1] = Wire.read();
          Serial.println("break");
          break;
        }
        else
        {
            
        }
     }
    // Read 2 bytes of data
    // temp msb, temp lsb
    Serial.println("break 2");
    // Convert the data
    int temp = (data[0] * 256) + data[1];
    float cTemp = (temp / 65536.0) * 165.0 - 40;
 //   float fTemp = cTemp * 1.8 + 32;
     
     int tem_ = (int)(cTemp*100);
    // Output data to serial monitor
    
   /* Serial.print("Relative Humidity :");
    Serial.print(humidity);
    Serial.println(" %RH");*/
    Serial.print("*************************************************************Temperature in Celsius :");
    Serial.print(cTemp);
    Serial.println(" C");
    
    //save_data( cTemp,  humidity);
    if(tem_==141936)
    {
      tem_=-1;
    }
    return tem_;
}/*
int read_presion()
{
int aux=0;
 TCA9548A(7);
  delay(time_delay_process_Multi);
  int led_ESP32=2;

 if (!bmp.begin())//sda , scl
  {
    Serial.println("No se pudo inicializar el sensor BMP180");
    for(int i =0;i<30;i++)
        {
          digitalWrite(led_ESP32, HIGH);
          delay(50);
          digitalWrite(led_ESP32, LOW);
          delay(50);
        }
   aux=-1;
  }
  else
  {
    float pressure = bmp.readPressure();
    float temperature = bmp.readTemperature();
    Serial.println("Presion");
    Serial.println(pressure);
    Serial.println("temp:");
    Serial.println(temperature);
    aux=0;
  }
 

  return aux;
}
int read_presion_direct()
{
int aux=0;
 
  delay(time_delay_process);
  int led_ESP32=2;

 if (!bmp.begin())//sda , scl
  {
    Serial.println("No se pudo inicializar el sensor BMP180");
    for(int i =0;i<30;i++)
        {
          digitalWrite(led_ESP32, HIGH);
          delay(50);
          digitalWrite(led_ESP32, LOW);
          delay(50);
        }
   aux=-1;
  }
  else
  {
    float pressure = bmp.readPressure();
    float temperature = bmp.readTemperature();
    Serial.print("*****************************************************************Presion ");
    Serial.println(pressure);
    Serial.print("temp: ");
    Serial.println(temperature);
    aux=pressure;
  }
 

  return aux;
}*/
void configure_analog_sensors()
{
  pinMode(pin_CO2, INPUT);
  pinMode(pin_lluvia, INPUT);
  pinMode(pin_UV, INPUT);
}
int read_rain()
{
   unsigned int sensorValue = analogRead(pin_lluvia);
   return sensorValue;
}
int read_UV()
{
    unsigned int sensorValue = analogRead(pin_UV);
    unsigned int UV_value=0;
    if(sensorValue<10)//  >  <
    {
      return 0;
    }
    else if(sensorValue<=46)//  >  <
    {
      return 1;
    }
    else if(sensorValue<=65)//  >  <
    {
      return 2;
    }
    else if(sensorValue<=83)//  >  <
    {
      return 3;
    }
    else if(sensorValue<=103)//  >  <
    {
      return 4;
    }
    else if(sensorValue<=124)//  >  <
    {
      return 5;
    }
    else if(sensorValue<=142)//  >  <
    {
      return 6;
    }
    else if(sensorValue<=162)//  >  <
    {
      return 7;
    }
    else if(sensorValue<=180)//  >  <
    {
      return 8;
    }
    else if(sensorValue<=200)//  >  <
    {
      return 9;
    }
    else if(sensorValue<=221)//  >  <
    {
      return 10;
    }
    else //  >  <
    {
      return 11;
    }
}
int read_CO2()
{
    unsigned int sensorValue = analogRead(pin_CO2);

    return sensorValue;
}
