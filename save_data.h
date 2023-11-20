/*#include <Arduino.h>
#include <SPI.h>

#include "FS.h"*/


//#include "config_data.h"
#include "DJANGO_REST.h"

//#include <Wire.h>
//#include <TimeLib.h>
///#include <DS1307RTC.h>

int initialice_SD_card_HANDLER();

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void createDir(fs::FS &fs, const char * path);
void removeDir(fs::FS &fs, const char * path);
void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
int appendFile_state(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void registrarEvento(String mensaje);
void deleteFile(fs::FS &fs, const char * path);
void testFileIO(fs::FS &fs, const char * path);
void check_buffer_archive_day();
bool getCurrentDate(int& day, int& month, int& year);
bool readDateFromFile(const char* fileName, int& day, int& month, int& year);
void copiarArchivo(const char *rutaOrigen, const char *rutaDestino);
void print2digits(int number) ;
String floatToString( float n, int l, int d, boolean z);
