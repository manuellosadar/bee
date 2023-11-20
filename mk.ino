


#include "config_data.h"
#include "config_txt_handeler.h"
#include "read_sensors.h"
#include "scan_data.h"
#include "low_energy_system.h"

//#include  "save_data.h"
RTC_DATA_ATTR int bootCount = 0;
int frecuencia_muestreo=05;
int hour_endpoint=0;
int led_ESP32=2;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
   Wire.begin();
   pinMode(led_ESP32, OUTPUT);
    digitalWrite(led_ESP32, HIGH);
    
    delay(1000);
     initialice_timer_RTC();
      Serial.println("+++++++++++++RTC ENDED");
     delay(10);
    
    int aux=  initialice_SD_card_HANDLER();
     
    if(aux==-1)
    {
      	for(int i =0;i<3;i++)
        {
          digitalWrite(led_ESP32, HIGH);
          delay(50);
          digitalWrite(led_ESP32, LOW);
          delay(50);
        }
        ESP.restart();
    }
     
     //setTime_date_static(21,15,0,12,11,2023);//(int Hour,int Min,int Sec,int Day, int Month,int Year)//Year, Month, Day, Hour, Min, Sec)
      Serial.println("++++++++++++++++++++++++++++++++++booter jumped +++++++++++++++++++++++++ configration ");
     Serial.println(bootCount);


     //carga de datos de configuración
     frecuencia_muestreo = load_freq_get_datas();
     Serial.print("freq muestreo ");
     Serial.println(frecuencia_muestreo);
     hour_endpoint=load_hour_endpoint_get_datas();
     Serial.print("hour_endpoint ");
     Serial.println(hour_endpoint);
     String MAC = load_MAC_get_datas();
     Serial.print("MAC ");
     Serial.println(MAC);
     configure_analog_sensors();
     check_buffer_archive_day();

     //digitalWrite(led_ESP32, LOW);
  /*if (bootCount==0)
  {
    
  initialice_timer_RTC();
  Serial.println("RTC  +++++++++++++++++++++++++RTC+++++++++++++++++++++++++++++++++");
  initialice_SD_card();
   Serial.println("SD card  +++++++++++++++++++++++++sd CARD+++++++++++++++++++++++++++++++++");
  ++bootCount;
  }
  else
  {
     initialice_SD_card();
     initialice_timer_RTC();
      Serial.println("++++++++++++++++++++++++++++++++++booter jumped ");
     Serial.println(bootCount);


     //carga de datos de configuración
     frecuencia_muestreo = load_freq_get_datas();
     Serial.print("freq muestreo ");
     Serial.println(frecuencia_muestreo);
     hour_endpoint=load_hour_endpoint_get_datas();
     Serial.print("hour_endpoint ");
     Serial.println(hour_endpoint);
     String MAC = load_MAC_get_datas();
     Serial.print("MAC ");
     Serial.println(MAC);

     
     //termina de carga de cofiguración
     ++bootCount;
  }*/
}

void loop() {
  // put your main code here, to run repeatedly:
    //
     digitalWrite(led_ESP32, HIGH);
     delay(500);
     Serial.println("LOOP CAL");
     // check_buffer_archive_day();//funcionando
     scan_data_sensors();
     
      //get_timer_();
     // Serial.println("LOOP CAL 2");
    
      //Serial.println("LOOP CAL 3");
      /* connectToWiFi(); 
      if (testInternetConnectivity()) {
        Serial.println("Tienes acceso a Internet.");
      } else {
        Serial.println("No tienes acceso a Internet.");
      }*/
       digitalWrite(led_ESP32, LOW);
       sleep_seconds((frecuencia_muestreo*60)+10);
}
