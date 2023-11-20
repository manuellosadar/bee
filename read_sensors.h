#include <Wire.h> // para utilizar I2C
//#include "save_data.h"
#include <Adafruit_AHTX0.h>
 #include <Adafruit_BMP280.h>


#define pin_CO2 12
#define pin_lluvia 10
#define pin_UV 11

#define Addr_HDC1080 0x40
#define Addr_HDC1080_1 0x40

void read_HDC1080();
void delay_i2c();
void delay_multi();
int read_humidity_HDC1080(int sensor);

int read_humidity_HDC1080_direct();
void read_BMP280(int sensor);
int read_BMP280_pression(int sensor);
int read_BMP280_temp(int sensor);
int read_tem_SHT21(int sensor);
int read_hum_SHT21(int sensor);

int read_tem_HDC1080(int sensor);
int read_tem_HDC1080_direct();
int read_Adafruit_AHTX0();
int read_Adafruit_AHTX0_press();
int read_Adafruit_AHTX0_temp();

int read_rain();
int read_UV();
int read_CO2();
/*int read_presion();
int read_presion_direct();*/
void configure_HDC1080();
void configure_analog_sensors();
void TCA9548A(uint8_t bus);

