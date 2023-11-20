#include  "DJANGO_REST.h"
const char* host = "3.223.84.85";
const char* url = "/abejas_app/upload_csv/";
int puerto=8077;
int tama_division=12800;//51200;//102400

int subida_documento() {
  // Suponiendo que estás conectado a Internet y que la SD está inicializada
 // String host = "http://tu-servidor.com";
 // const char* url = "/ruta/para/subir/csv/";
  connectToWiFi(); 
      if (testInternetConnectivity()) {
        Serial.println("Tienes acceso a Internet.");
      } else {
        Serial.println("No tienes acceso a Internet.");
        return -1;
      }
  String payload = "/buffer_data.csv";//readCSVFile("/buffer_data.csv");
  
  if (!payload.isEmpty()) {
    //uploadCSV(host, url, payload);
    //carga_CSV_multiple(host, url, payload);
    carga_CSV_multiple_split(host, url, payload);
    return 1;
  }
  else
  {
    Serial.println("Documento vacio");
    return -1;
  }
}





void carga_CSV_multiple(const String& host, const char* url, const String& filePath) {
    File myFile = SD.open(filePath);
  if (!myFile) {
    Serial.println("No se pudo abrir el archivo.");
    return;
  }

  HTTPClient http;
  http.begin(host, puerto, url);

  String bound = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
  http.addHeader("Content-Type", "multipart/form-data; boundary=" + bound);

  String start_request = "--" + bound + "\r\nContent-Disposition: form-data; name=\"file\"; filename=\"data.csv\"\r\nContent-Type: text/csv\r\n\r\n";
  String end_request = "\r\n--" + bound + "--\r\n";

  String payload;
  payload.reserve(start_request.length() + end_request.length() + myFile.size());
  payload += start_request;

  while (myFile.available()) {
    payload += (char) myFile.read();
  }

  payload += end_request;
  myFile.close();
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    Serial.println("Código de respuesta HTTP: " + String(httpResponseCode));
  } else {
    Serial.println("Error en el envío: " + http.errorToString(httpResponseCode));
    guardar_error_log("REST ERROR,"+http.errorToString(httpResponseCode)+",");

  }

  http.end();
  
  //Serial.println(payload);
  delay(30);
}






void carga_CSV_multiple_split(const String& host, const char* url, const String& filePath) {
    File myFile = SD.open(filePath);
  if (!myFile) {
    Serial.println("No se pudo abrir el archivo.");
    return;
  }
  size_t fileSize = myFile.size();
  Serial.println("Tamaño del archivo: " + String(fileSize) + " bytes");
  if (fileSize>tama_division)
  {
    Serial.println("El tamaño es mayor de lo normal.");
    splitFile(filePath.c_str());
    File dir = SD.open("/buffer_upload");//recorremos el directorio que se ha tenido que crear al dividir el archivo.
     Serial.println("SE abre el archivo buffer_upload");
      if (!dir) {
        Serial.println("Error al abrir el directorio /buffer_upload/");
        return;
      }
      
      File entry =  dir.openNextFile();
      while(entry) {
        if (!entry.isDirectory()) {
          String filePath = String("/buffer_upload/") + entry.name();
          Serial.println("Procesando archivo: " + filePath);
          carga_CSV_multiple(host, url, filePath);
        }
        entry.close();
        /*if (SD.remove(filePath.c_str())) {
            Serial.println("El archivo se ha eliminado con éxito");
        } else {
            Serial.println("Error al eliminar el archivo");
        }*/
        entry = dir.openNextFile();
      }
      
      dir.close();  
      /*if (SD.rmdir("/buffer_upload")) {
        Serial.println("Directorio /buffer_upload/ eliminado");
      } else {
        Serial.println("Error al eliminar el directorio /buffer_upload/");
      }*/
      

  }
  else
  {
    Serial.println("El tamaño es menor del maximo.");
    String payload = "/buffer_data.csv";
    carga_CSV_multiple(host, url, payload);
  }
  
  myFile.close();
  deleteFilesInDirectory("buffer_upload");
}








void splitFile(const char* filePath) {
  File originalFile = SD.open(filePath, FILE_READ);
  if (!originalFile) {
    Serial.println("Error al abrir el archivo original");
    return;
  }
  //comprobamos si el directorio existe, apra en tal caso borrar todo su contenido y así poder limpiarlo al 100%
  deleteFilesInDirectory("/buffer_upload");

  // Crear el directorio
  if (SD.mkdir("/buffer_upload")) {
    Serial.println("Directorio creado con éxito");
  } else {
    Serial.println("Error al crear el directorio");
  }

  String firstLine = "";
  boolean isFirstLine = true;
  int fileCount = 0;
  int fileSize = 0;
  File newFile;
  int first_file=0;
  while (originalFile.available()) {
    // Leer la línea actual
    String currentLine = originalFile.readStringUntil('\n') + '\n';

    // Guardar la primera línea para usarla en otros archivos
    if (first_file==0) {
      first_file+1;
      
    }
    if (isFirstLine) {
      firstLine = currentLine;
      isFirstLine = false;
    }

    // Crear un nuevo archivo si el tamaño excede 100 KB o es la primera línea
    if (fileSize + currentLine.length() > tama_division || fileSize == 0) {
      if (newFile) {
        newFile.close();
      }
      fileCount++;
      String newFilePath = "/buffer_upload/split_" + String(fileCount) + ".csv";
      newFile = SD.open(newFilePath.c_str(), FILE_WRITE);
      if (!newFile) {
        Serial.println("Error al crear un nuevo archivo");
        return;
      }
      if (first_file==0) {
        first_file=first_file+1;
      
      }
      else
      {
          newFile.print(firstLine);
      }
      fileSize = firstLine.length();
    }

    // Agregar la línea actual al nuevo archivo
    newFile.print(currentLine);
    fileSize += currentLine.length();
  }

  // Cerrar los archivos abiertos
  originalFile.close();
  if (newFile) {
    newFile.close();
  }
}

void deleteFilesInDirectory(const char * directory) {
  File root = SD.open("/");
  String filePath_aux = String("/") + String(directory);
  if (root) {
    File entry = root.openNextFile();
    Serial.println("Entry -- ");
    while (entry) {
      if (entry.isDirectory()) {
        String folder = String(entry.name());
        Serial.print("tratando de verificar si es igual a la referencia el folder: ");
        Serial.println(folder);
        Serial.print(" directorio: ");
        Serial.println(String(directory));
        if (folder.equals(directory)) {
          Serial.println("directorio encontrado");
          
          File dir = SD.open(filePath_aux.c_str());
          File fileEntry = dir.openNextFile();
          while (fileEntry) {
            String filePath = filePath_aux + String("/") + String(fileEntry.name());
            Serial.print("tratando de eliminar el archivo: ");
            Serial.println(filePath);
            if (SD.remove(filePath.c_str())) {
              Serial.println("Archivo eliminado con éxito: " + filePath);
            } else {
              Serial.println("Error al eliminar el archivo: " + filePath);
            }
            fileEntry.close();
            fileEntry = dir.openNextFile();
          }
          dir.close();
          if (SD.rmdir(filePath_aux.c_str())) {
            Serial.println("Directorio eliminado con éxito: " + String(directory));
          } else {
            Serial.println("Error al eliminar el directorio: " + String(directory));
          }
        }
      }
      entry.close();
      entry = root.openNextFile();
    }
    root.close();
  } else {
    Serial.println("Error al abrir la raíz de la SD");
  }
}
