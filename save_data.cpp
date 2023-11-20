#include "save_data.h"
//#include "config_data.h"


int initialice_SD_card_HANDLER()
{
  int maxRetries = 15;
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  
  for (int retryCount = 0; retryCount < maxRetries; retryCount++) {
    // Verifica la conexión antes de cada intento
    if (digitalRead(SD_CS) == LOW) {
      Serial.println("Error: Tarjeta SD no insertada correctamente.");
      return -1;
    }
    
    if (SD.begin(SD_CS)) {
      // Verifica si la tarjeta existe en el sistema de archivos
      if (SD.exists("/")) {
        return 1; // Inicialización exitosa
      } else {
        Serial.println("Error: Tarjeta SD no encontrada o vacía.");
        delay(1000); // Espera antes de intentar nuevamente
      }
    } else {
      Serial.println("Error: No se pudo inicializar la tarjeta SD.");
      delay(1000); // Espera antes de intentar nuevamente
    }
  }

  Serial.println("Error: Fallaron todos los intentos de inicialización.");
  return -1;
      
}
void check_buffer_archive_day()
{
//heck the day in buffer_config.txt of the last day of backup. TIs is not the same day go in and change the data of buffer to day file

  //readFile(SD,"config.txt");
  
int month =0, day=0, year=0;
int month_rtc =0, day_rtc=0, year_rtc=0;
String year_ ;
String month_ ;
String day_;;

File file = SD.open("/buffer_config.txt");
if(!file){
  Serial.println("Failed to open file for reading  buffer_config.xt ____");
  //return -1;
}

  //Serial.print("Read from file: ");
while (file.available()) {
  String data_ = file.readStringUntil('\n'); // Lee una línea completa del archivo
  Serial.println("Leido del archivo ____");
    Serial.println(data_);

  // Inicializa variables para almacenar los valores
  //int year, month, day;
  // Utiliza sscanf para extraer los valores de la cadena
  if (sscanf(data_.c_str(), "%d/%d/%d", &day, &month, &year) == 3) {
    // Los valores se han leído correctamente, ahora puedes usar year, month y day
    year_=String(year);
    month_=String(month);
    day_=String(day);

    Serial.print("Año: ");
    Serial.println(year);
    Serial.print("Mes: ");
    Serial.println(month);
    Serial.print("Día: ");
    Serial.println(day);
  } else {
    // Maneja el caso en el que los valores no se pudieron leer correctamente
    Serial.println("Error al leer los valores desde el archivo.");
  }
}
file.close();
  //ya se tienen lso datos del ultimo dia que el archivo ha sido modificado

  ///seprocede  obtener qye dia es hoy
  char buffer [25] = "";
  
  get_timer_return(buffer);
  //String buffer_mystring(buffer);  
  if (sscanf(buffer, "%2d/%2d/%4d", &day_rtc, &month_rtc, &year_rtc) == 3) {
    // Los valores se han leído correctamente
    Serial.print("-Leido de RTC.txt-");
    Serial.println(buffer);
  } else {
    // Manejar el caso en el que no se puedan leer los valores correctamente
    Serial.println("Error al leer los valores desde el texto.");
  }

  Serial.print("-Leido de RTC.txt-");
  Serial.println(buffer);

  printf("Fecha: %02d/%02d/%04d RTC: %02d/%02d/%04d\n", day, month, year, day_rtc, month_rtc, year_rtc);

    if((year_rtc!=year )||(day_rtc!=day)||(month_rtc!=month))
    {
        Serial.print("Son dias disintos");

        //procedemos a subir el archivo 
      int sub_doc = subida_documento();
      // char buffer_nombre_nuevo_archivo [25] = "2022/12/04.txt";
      String nombre_archivo_dia="/"+day_+"_"+month_+"_"+year_+".csv";
      //se procede a cambiar el nombre del archivo de texto ed buffer
      Serial.print("El nuevo nombpe de archivo");
      Serial.println(nombre_archivo_dia);
      char nombre_archivo_dia_aux [25] = "";
      nombre_archivo_dia.toCharArray(nombre_archivo_dia_aux, 16);
      //buffer_data.txt se ha decambiar de nombre ed archivo
      renameFile(SD,"/buffer_data.csv",nombre_archivo_dia_aux);
      //guardar el nuevo dia en el archivo de configuración
        delay(5);
        writeFile(SD,"/buffer_data.csv","MAC,temp_front,pression_front,humidity_front,temp_back,pression_back,humidity_back,temp_der,pression_der,humidity_der,temp_iz,pression_iz,humidity_iz,temp_tapa,pression_tapa,humidity_tapa,temp_ext,pression_ext,humidity_ext,lluvia,UV,CO2,fecha,hora,fecha_hora,AUX");

        String contenido_archivo_dia=String(day_rtc)+"/"+String(month_rtc)+"/"+String(year_rtc);
        Serial.print("El nuevo contenido a escribir");
      Serial.println(contenido_archivo_dia);
        char nombre_archivo_dia_aux_2 [25] = "";
          contenido_archivo_dia.toCharArray(nombre_archivo_dia_aux_2, 11);
      writeFile(SD,"/buffer_config.txt",nombre_archivo_dia_aux_2);
        //String aux_buffer= buffer.substring(0,10);
      if(sub_doc==1)
      {
        //subida ok
      }
      else
      {
          //error de subida
          if (!SD.exists("/pendiente_subida")) {
            SD.mkdir("/pendiente_subida");
          }
  
           // Copia el archivo renombrado al directorio "/pendiente_subida"
          String pathDestino = String("/pendiente_subida") + String("/") + String(nombre_archivo_dia_aux);
          copiarArchivo(nombre_archivo_dia_aux, pathDestino.c_str());
      }
      
    }
    else
    {
      //no se hace nada
          Serial.println("-Es el mismo dia-");

    }
}



String floatToString( float n, int l, int d, boolean z){
     char c[l+1];
     String s;
    
     dtostrf(n,l,d,c);
     s=String(c);
    
     if(z){
     s.replace(" ","0");
     }

 return s;
}






//listDir(SD, "/", 0);

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void removeDir(fs::FS &fs, const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

void readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.println(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.println(message)){
      Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
int appendFile_state(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  // Intenta abrir el archivo
  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");

    // Si falla la apertura, intenta renombrar el archivo original
    String  renamedPath = String(path) + getTimestamp_rename_file(); 
    if (fs.rename(path, renamedPath)) {
      Serial.printf("Renamed %s to %s\n", path, renamedPath);
      
    } else {
      Serial.println("Failed to rename file");
      //return -1;
    }
    // Crea un nuevo archivo con el nombre original y guarda el mensaje
      file = fs.open(path, FILE_WRITE);
      if(file.println(message)){
        Serial.println("Message appended");
        file.close();
        return 0;
      } else {
        Serial.println("Append failed");
        file.close();
        return -1;
      }
  } else {
    if(file.println(message)){
      Serial.println("Message appended");
      file.close();
      return 0;
    } else {
      Serial.println("Append failed");
      file.close();
      return -1;
    }
  }
}
void renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void testFileIO(fs::FS &fs, const char * path){
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if(file){
    len = file.size();
    size_t flen = len;
    start = millis();
    while(len){
      size_t toRead = len;
      if(toRead > 512){
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for(i=0; i<2048; i++){
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}


void registrarEvento(String mensaje) {
  // Intenta abrir el archivo de registro en modo de escritura (append)
  File archivoRegistro = SD.open("registro.txt", FILE_WRITE);
  
  // Verifica si el archivo se abrió correctamente
  if (archivoRegistro) {
    // Obtiene la hora actual para incluirla en el registro (puedes personalizar esto)
    String hora = get_timer_return();
    
    // Construye la línea de registro con la hora y el mensaje
    String lineaRegistro = hora + " - " + mensaje;
    
    // Escribe la línea de registro en el archivo
    archivoRegistro.println(lineaRegistro);
    archivoRegistro.close(); // Cierra el archivo
    
    // Muestra un mensaje en la consola serial
    Serial.println("Evento registrado: " + lineaRegistro);
  } else {
    // Si no se pudo abrir el archivo, intenta renombrarlo o crear uno nuevo
    if (SD.rename("/registro.txt", "/registro_antiguo.txt")) {
      // Se renombró con éxito, crea un nuevo archivo de registro
      archivoRegistro = SD.open("registro.txt", FILE_WRITE);
      if (archivoRegistro) {
        // Obtiene la hora actual para incluirla en el registro (puedes personalizar esto)
        String hora = get_timer_return();
        
        // Construye la línea de registro con la hora y el mensaje
        String lineaRegistro = hora + " - " + mensaje;
        
        // Escribe la línea de registro en el nuevo archivo
        archivoRegistro.println(lineaRegistro);
        archivoRegistro.close(); // Cierra el nuevo archivo
        
        // Muestra un mensaje en la consola serial
        Serial.println("Evento registrado en un nuevo archivo: " + lineaRegistro);
      } else {
        // Si no se pudo crear un nuevo archivo, muestra un mensaje de error
        Serial.println("Error al crear un nuevo archivo de registro.");
      }
    } else {
      // Si no se pudo renombrar el archivo, muestra un mensaje de error
      Serial.println("Error al renombrar el archivo de registro.");
    }
  }
}
void copiarArchivo(const char *rutaOrigen, const char *rutaDestino) {
  File archivoOrigen = SD.open(rutaOrigen, FILE_READ);
  if (!archivoOrigen) {
    Serial.println("Error al abrir el archivo origen");
    return;
  }

  File archivoDestino = SD.open(rutaDestino, FILE_WRITE);
  if (!archivoDestino) {
    Serial.println("Error al abrir/crear el archivo destino");
    archivoOrigen.close();
    return;
  }

  // Leer desde el archivo origen y escribir en el archivo destino
  byte buffer[128];  // buffer para copiar en bloques de 128 bytes
  while (archivoOrigen.available()) {
    int bytesRead = archivoOrigen.read(buffer, sizeof(buffer));
    archivoDestino.write(buffer, bytesRead);
  }

  archivoOrigen.close();
  archivoDestino.close();
}
