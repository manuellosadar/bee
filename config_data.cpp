#include "config_data.h"



 RTC_DS3231 rtc;


String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };

char date_strcut_config[] = {"22:13:08 25/3/2022"};


int initialice_timer_RTC()
{
 if (!rtc.begin()) {
      Serial.println(F("ERROR +++++++++++++++++++++++++RTC+++++++++++++++++++++++++++++++++"));
      return -1;
   }
   else
   {
     Serial.println(F("SUCESS +++++++++++++++++++++++++RTC+++++++++++++++++++++++++++++++++"));
     /*DateTime now = rtc.now();
    struct tm newTime;
    newTime.tm_year = now.year() - 1900; // Año menos 1900
    newTime.tm_mon = now.month() - 1;    // Mes, desde 0 hasta 11
    newTime.tm_mday = now.day();         // Día del mes
    newTime.tm_hour = now.hour();        // Hora
    newTime.tm_min = now.minute();       // Minutos
    newTime.tm_sec = now.second();       // Segundos

    time_t t = mktime(&newTime);
    struct timeval nowTimeval = { .tv_sec = t };
    settimeofday(&nowTimeval, NULL);*/
     return 1;
   }
}
int initialice_SD_card()
{
  return -1;//77initialice_SD_card_HANDLER();

      
}

void inicilice_SD()
{

}


int setTime_date_static(int Hour,int Min,int Sec,int Day, int Month,int Year)
{
  Serial.println("Configurando hora");
  
 
   //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.adjust(DateTime(Year, Month, Day, Hour, Min, Sec)); // 21 de Enero de 2016 a las 03:00:00
  delay(100);
  //digitalWrite(16, LOW);//apagado de chip
  return 1;
  
}




void printDate(DateTime now_local)
{
  Serial.println("---------------------------------pint datetime--------------------------");
 /*// String aux2=now.toString();
  Serial.print("---------------------------------datetime in string--------------------------");
    Serial.println(aux2);
*/
  //String aux = String();
//  date_strcut_config = now_local.toString(date_strcut_config);
  Serial.println("---------------------------------2 pint datetime 2 --------------------------");
  //Serial.println;
  //
  //Serial.println(date_strcut_config);
    Serial.println("---------------------------------3 pint datetime 3 --------------------------");
   Serial.print(now_local.year(), DEC);
   Serial.print('/');
   Serial.print(now_local.month(), DEC);
   Serial.print('/');
   Serial.print(now_local.day(), DEC);
   Serial.print(" (");
   Serial.print(daysOfTheWeek[now_local.dayOfTheWeek()]);
   Serial.print(") ");
   Serial.print(now_local.hour(), DEC);
   Serial.print(':');
   Serial.print(now_local.minute(), DEC);
   Serial.print(':');
   Serial.print(now_local.second(), DEC);
   Serial.println();
}
void get_timer_()
{
 
  //delay(10000);
  Serial.println("---------------------------------before the rtc call--------------------------");

 DateTime now = rtc.now();
    //returned=now;
    char buffer [25] = "";
  
  sprintf(buffer, "%04d/%02d/%02d, %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  //dateTime = buffer;
     Serial.print("date");

   Serial.println(buffer);
   //printDate(returned);
 Serial.println("---------------------------------after the rtc call--------------------------");
  //digitalWrite(16, LOW);//apagado de chip
  //return returned;

   Serial.println("after return ");

}/*
void get_timer_return(char* buffer) {
    // Leer la hora del DS3231
    DateTime nowDS3231 = rtc.now();

    // Leer la hora del RTC interno del ESP32
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time from internal RTC");
        return;
    }

    // Asumir que el año actual es 2023
    int currentYear = 2023;

    // Comparar los años
    bool ds3231IsCorrect = (nowDS3231.year() == currentYear);
    bool internalRTCCorrect = (timeinfo.tm_year + 1900 == currentYear);

    // Elegir la fecha más probablemente correcta
    if (ds3231IsCorrect && !internalRTCCorrect) {
        // DS3231 es correcto
        sprintf(buffer, "%02d/%02d/%04d,%02d:%02d:%02d", nowDS3231.day(), nowDS3231.month(), nowDS3231.year(), nowDS3231.hour(), nowDS3231.minute(), nowDS3231.second());
    } else if (!ds3231IsCorrect && internalRTCCorrect) {
        // RTC interno es correcto
        sprintf(buffer, "%02d/%02d/%04d,%02d:%02d:%02d", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    } else {
        // Si ambos coinciden o no, preferir DS3231
        sprintf(buffer, "%02d/%02d/%04d,%02d:%02d:%02d", nowDS3231.day(), nowDS3231.month(), nowDS3231.year(), nowDS3231.hour(), nowDS3231.minute(), nowDS3231.second());
    }

    Serial.println(buffer);
}
*/
void get_timer_return(char* buffer )
{
 
  //delay(10000);
  Serial.println("---------------------------------before the rtc call--------------------------");

 DateTime now = rtc.now();
    //returned=now;
    //char buffer [25] = "";
  
  sprintf(buffer, "%02d/%02d/%04d,%02d:%02d:%02d", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
  //dateTime = buffer;
     Serial.print("date");

   Serial.println(buffer);
   //printDate(returned);
 Serial.println("---------------------------------after the rtc call--------------------------");
  //digitalWrite(16, LOW);//apagado de chip
  //return returned;

   Serial.println("after return ");

}

void get_timer_return_ISO(char* buffer)
{
  DateTime now = rtc.now();
  
  sprintf(buffer, "%04d-%02d-%02dT%02d:%02d:%02dZ", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  
  Serial.println("La fecha en formato ISO 8601 es: ");
  Serial.println(buffer);
}

String getTimestamp_rename_file() {
  char buffer[15]; // Buffer para la fecha y hora
  get_timer_return(buffer); // Obtiene la fecha y hora actual
  String timestamp = String(buffer);

  // Eliminar caracteres no válidos (por ejemplo, /, :, y espacios)
  timestamp.replace("/", "");
  timestamp.replace(":", "");
  timestamp.replace(" ", "");

  return timestamp;
}
