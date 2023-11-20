
#include <SD.h>
#include <HTTPClient.h>
#include "wifi_handler.h"
//#include "save_data.h" //exist in the wifi_handler call
#include "config_data.h"
//#include <SD.h>
#include  "error_controler.h"


int subida_documento();
void carga_CSV_multiple(const String& host, const char* url, const String& filePath) ;
//void carga_CSV_multiple(const char* host, const char* url, const char* filePath) {
void deleteFilesInDirectory(const char * directory);
void splitFile(const char* filePath) ;
void carga_CSV_multiple_split(const String& host, const char* url, const String& filePath);
