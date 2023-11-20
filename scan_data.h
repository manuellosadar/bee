
//#include <SD.h>
#include "config_txt_handeler.h"
//#include "save_data.h"
#include "read_sensors.h"
#include "HardwareSerial.h"


struct struc_datos_temperatura_hum
{
  
   int temp_1_INF;//0 no enviado el archivo, 1 enviado el archivo
   int hum_1_INF;
   int temp_2_INF;
    int hum_2_INF;
    int temp_3_INF;
    int hum_3_INF;
     int temp_1_SUP;//0 no enviado el archivo, 1 enviado el archivo
   int hum_1_SUP;
   int temp_2_SUP;
    int hum_2_SUP;
    int temp_3_SUP;
    int hum_3_SUP;
    int lluvia;
    int UV;
    int CO2;
   
};
struct struc_datos_totales
{
  
   int temp_front;//0 no enviado el archivo, 1 enviado el archivo
   int pression_front;
   int humidity_front;
  int temp_back;//0 no enviado el archivo, 1 enviado el archivo
   int pression_back;
   int humidity_back;
   int temp_der;//0 no enviado el archivo, 1 enviado el archivo
   int pression_der;
   int humidity_der;
   int temp_iz;//0 no enviado el archivo, 1 enviado el archivo
   int pression_iz;
   int humidity_iz;
   int temp_tapa;//0 no enviado el archivo, 1 enviado el archivo
   int pression_tapa;
   int humidity_tapa;
   int temp_ext;//0 no enviado el archivo, 1 enviado el archivo
   int pression_ext;
   int humidity_ext;
    int lluvia;
    int UV;
    int CO2;
   
};
struct struc_datos_temperatura_hum_char
{
  
   char temp_1_INF[7]="00000;";;//0 no enviado el archivo, 1 enviado el archivo
   char hum_1_INF[7]="00000;";;
   char temp_2_INF[7]="00000;";;
    char hum_2_INF[7]="00000;";;
    char temp_3_INF[7]="00000;";;
    char hum_3_INF[7]="00000;";;
     char temp_1_SUP[7]="00000;";;//0 no enviado el archivo, 1 enviado el archivo
   char hum_1_SUP[7]="00000;";;
   char temp_2_SUP[7]="00000;";;
    char hum_2_SUP[7]="00000;";;
    char temp_3_SUP[7]="00000;";;
    char hum_3_SUP[7]="00000;";;
     char UV[7]="00000;";;
      char CO2[7]="00000;";;
    char lluvia[7]="00000;";;
   
};


String estructuraAString( struc_datos_totales datos);
int save_struct(struc_datos_temperatura_hum dato);
void scan_data_sensors();
void convert_data_sensor_zeros(char* aux, int dato);
