#include  "error_controler.h"
int guardar_error_log(String error)
{
  
  char timestamp_ISO[25];
  get_timer_return_ISO(timestamp_ISO);
  String timestampStr_ISO = String(timestamp_ISO);
  File file = SD.open("/error_logs.csv", FILE_APPEND);
  
  if (!file) {
    // Si el archivo no se pudo abrir, intentar crearlo.
    file = SD.open("/error_logs.csv", FILE_WRITE);
    if (!file) {
      Serial.println("Error al abrir/crear el archivo");
      return -1;  // Regresa -1 si hay un error
    }
  }
  String aux_str = error +","+ timestampStr_ISO;
  file.println(aux_str);  // Escribe el error y añade un salto de línea al final
  file.close();  // Cierra el archivo
  
  return 1;  // Éxito
}

