#include "config_txt_handeler.h"



int load_freq_get_datas() {
  File file = SD.open("/config.txt");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return -1;
  }

  int myInt = -1; // Valor predeterminado en caso de que no se encuentre "freq:"

  while (file.available()) {
    String data_ = file.readStringUntil('\n');
    if (data_.startsWith("freq:")) {
      String sub = data_.substring(5); // Omitir "freq:"
      myInt = sub.toInt();
      break; // Rompe el bucle una vez que se ha encontrado "freq:"
    }
  }

  file.close();
  return myInt;
}


int load_hour_endpoint_get_datas() {
  File file = SD.open("/config.txt");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return -1;
  }

  int myInt = -1; // Valor predeterminado en caso de que no se encuentre "endpoint:"

  while (file.available()) {
    String data_ = file.readStringUntil('\n');
    int index = data_.indexOf("endpoint:");
    if (index != -1) {
      String sub = data_.substring(index + 9, index + 11); // Tomar los dos caracteres después de "endpoint:"
      myInt = sub.toInt();
      break; // Rompe el bucle una vez que se ha encontrado "endpoint:"
    }
  }

  file.close();
  return myInt;
}



String load_MAC_get_datas() {
  File file = SD.open("/config.txt");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return "MK0";
  }

  String myInt = "MK0"; // Valor predeterminado en caso de que no se encuentre "MAC:"

  while (file.available()) {
    String data_ = file.readStringUntil('\n');
    int index = data_.indexOf("MAC:");
    if (index != -1) {
      String sub = data_.substring(index + 4, index + 7); // Tomar los tres caracteres después de "MAC:"
      myInt = sub;
      break; // Rompe el bucle una vez que se ha encontrado "MAC:"
    }
  }

  file.close();
  return myInt;
}
