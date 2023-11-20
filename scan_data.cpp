#include "scan_data.h"


int sensor_multiplexor_1_INF = 11;
int sensor_multiplexor_2_INF = 12;
int sensor_multiplexor_3_INF = 13;


void scan_data_sensors() {
  //struc_datos_temperatura_hum data_ = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  struc_datos_totales data_total;

  data_total.temp_der = read_BMP280_temp(0);
  data_total.pression_der = read_BMP280_pression(0);

  data_total.humidity_der = read_humidity_HDC1080(1);//read_hum_SHT21(3); //int read_tem_SHT21(int sensor)read_hum_SHT21
  /*int  xin_c=read_tem_SHT21(3);
  Serial.print("Leido humedad SHT21 ");
  Serial.println( data_total.humidity_der);
  Serial.print("Leido temperatura de SHT21 ");
  Serial.println( xin_c);
  delay (10000);

  data_total.humidity_der = read_hum_SHT21(0); //int read_tem_SHT21(int sensor)read_hum_SHT21
   xin_c=read_tem_SHT21(0);
  Serial.print("Leido humedad SHT21 ");
  Serial.println( data_total.humidity_der);
  Serial.print("Leido temperatura de SHT21 ");
  Serial.println( xin_c);
  delay (10000);*/

  data_total.temp_front  = read_BMP280_temp(1);
  data_total.pression_front = read_BMP280_pression(1);
  data_total.humidity_front = read_humidity_HDC1080(1);

  data_total.temp_iz  = read_BMP280_temp(2);
    data_total.pression_iz = read_BMP280_pression(2);
data_total.humidity_iz = read_humidity_HDC1080(2);

    data_total.temp_back  =read_BMP280_temp(3);
    data_total.pression_back = read_BMP280_pression(3);
    data_total.humidity_back = read_humidity_HDC1080(2);

    data_total.temp_tapa  = read_BMP280_temp(7);//-1;//read_BMP280_temp(4);
   // Serial.print("dato____-----____");
   // Serial.println(data_total.temp_tapa );
    data_total.pression_tapa = read_BMP280_pression(7);//-1;//read_BMP280_pression(4);
    data_total.humidity_tapa = read_humidity_HDC1080(7);//read_humidity_HDC1080(4);

       data_total.temp_ext  = read_Adafruit_AHTX0_temp();//read_BMP280_temp(5);
    data_total.pression_ext =  -1;//read_BMP280_pression(5);
    data_total.humidity_ext =  read_Adafruit_AHTX0_press();//read_humidity_HDC1080(5);
  

  int UV = read_UV();
  int lluvia = read_rain();
  int CO2_ = read_CO2();
  Serial.print("Lectura de UV = ");
  Serial.println(UV);
  Serial.print("Lectura de lluvia = ");
  Serial.println(lluvia);
Serial.print("Lectura de CO2 = ");
  Serial.println(CO2_);

  data_total.lluvia = lluvia;
  data_total.UV = UV;
  data_total.CO2 = CO2_;

/// read_presion();
  String datosComoCadena = estructuraAString(data_total);
  Serial.print("Datos leidos:");
  Serial.println(datosComoCadena);
  const char* nombreArchivo = datosComoCadena.c_str();
  int state = appendFile_state(SD, "/buffer_data.csv", nombreArchivo);
  if(state != -1)
  {
    Serial.print("Guardado OK ");
    Serial.println(datosComoCadena);
  }
  else //error
  {
      Serial.print("ERROR de guardado");
  }
  //save_struct(data_);
  Serial.println("SCAN data SENSOR");
  datosComoCadena.clear();
}

String estructuraAString(struc_datos_totales datos) {
  String aux_MAC = "MK1";//load_MAC_get_datas();
   char timestamp[25];
   char timestamp_ISO[25];
  get_timer_return(timestamp); //
  get_timer_return_ISO(timestamp_ISO);
  String timestampStr = String(timestamp);
  String timestampStr_ISO = String(timestamp_ISO);
  String cadena = aux_MAC + "," +
                  String(datos.temp_front) + "," +
                  String(datos.pression_front) + "," +
                  String(datos.humidity_front) + "," +
                  String(datos.temp_back) + "," +
                  String(datos.pression_back) + "," +
                  String(datos.humidity_back) + "," +
                  String(datos.temp_der) + "," +
                  String(datos.pression_der) + "," +
                  String(datos.humidity_der) + "," +
                  String(datos.temp_iz) + "," +
                  String(datos.pression_iz) + "," +
                  String(datos.humidity_iz) + "," +
                  String(datos.temp_tapa) + "," +
                  String(datos.pression_tapa) + "," +
                  String(datos.humidity_tapa) + "," +
                  String(datos.temp_ext) + "," +
                  String(datos.pression_ext) + "," +
                  String(datos.humidity_ext) + "," +
                  String(datos.lluvia) + "," +
                  String(datos.UV) + "," +
                  String(datos.CO2) + "," +
                  timestampStr+ "," +
                  timestampStr_ISO+ "," +
                  +"AUX";
  return cadena;
}
/*int save_struct(struc_datos_temperatura_hum dato) {

  Serial.println("comenzando save struct----------------");

  char aux_dadtos_sensores[115] = "MK1;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;2022/12/03 14:05:00;";
  char relleno[2] = "\n";
  Serial.println("inicializacion");
  Serial.println(aux_dadtos_sensores);

  char fecha_char[20] = "2022/12/03 14:05:00";
  char MAC_char[3];
  // aux_dadtos_sensores[109]='\n';
  struc_datos_temperatura_hum_char aux;  //{"+00,00","+00,00","+00,00","+00,00","+00,00","+00,00","+00,00","+00,00","+00,00","+00,00","+00,00","+00,00"};
  String aux_MAC = load_MAC_get_datas();
  // aux_dadtos_sensores //char * strncpy ( char * destination, const char * source, size_t num );
  aux_MAC.toCharArray(MAC_char, 4);
  Serial.println("MAC a guardar");
  Serial.println(MAC_char);

  get_timer_return(fecha_char);

  Serial.println("fecha de RTS");
  Serial.println(fecha_char);

  //itoa(dato.hum_1_INF, aux.hum_1_INF, 6);
  convert_data_sensor_zeros(aux.hum_1_INF, dato.hum_1_INF);
  convert_data_sensor_zeros(aux.hum_1_SUP, dato.hum_1_SUP);
  convert_data_sensor_zeros(aux.hum_2_INF, dato.hum_2_INF);
  convert_data_sensor_zeros(aux.hum_2_SUP, dato.hum_2_SUP);
  convert_data_sensor_zeros(aux.hum_3_INF, dato.hum_3_INF);
  convert_data_sensor_zeros(aux.hum_3_SUP, dato.hum_3_SUP);

  convert_data_sensor_zeros(aux.temp_1_INF, dato.temp_1_INF);
  convert_data_sensor_zeros(aux.temp_1_SUP, dato.temp_1_SUP);
  convert_data_sensor_zeros(aux.temp_2_INF, dato.temp_2_INF);
  convert_data_sensor_zeros(aux.temp_2_SUP, dato.temp_2_SUP);
  convert_data_sensor_zeros(aux.temp_3_INF, dato.temp_3_INF);
  convert_data_sensor_zeros(aux.temp_3_SUP, dato.temp_3_SUP);
  convert_data_sensor_zeros(aux.UV, dato.UV);
  convert_data_sensor_zeros(aux.lluvia, dato.lluvia);
  convert_data_sensor_zeros(aux.CO2, dato.CO2);
  Serial.print("lluvia data: ");
  Serial.println(dato.lluvia);
  Serial.print("UV: ");
  Serial.println(dato.UV);

  /*
itoa(dato.hum_1_SUP, aux.hum_1_SUP, 10);
itoa(dato.hum_1_INF, aux.hum_2_INF, 10);
itoa(dato.hum_1_SUP, aux.hum_2_SUP, 10);
itoa(dato.hum_1_INF, aux.hum_3_INF, 10);
itoa(dato.hum_1_SUP, aux.hum_3_SUP, 10);

itoa(dato.temp_1_INF, aux.temp_1_INF, 10);
itoa(dato.temp_1_SUP, aux.temp_1_SUP, 10);
itoa(dato.temp_1_INF, aux.temp_2_INF, 10);
itoa(dato.temp_1_SUP, aux.temp_2_SUP, 10);
itoa(dato.temp_1_INF, aux.temp_3_INF, 10);
itoa(dato.temp_1_SUP, aux.temp_3_SUP, 10);
*/
  //strncpy (destination, source + start_index, number_of_chars);
  /*int num_char_temp = 6;  //el 1 es del punto y coma, no se copia ya que ha sido inicializado con los puntos y comas
  int num_char_temp_ = 6;
  int largo_MAC = 4;
  strncpy(aux_dadtos_sensores, MAC_char, 3);
  //memcpy(aux_dadtos_sensores+largo_MAC,aux.temp_1_INF,SIZEOF(CHAR)*num_char_temp);
  strncpy(aux_dadtos_sensores + (largo_MAC), aux.temp_1_INF, num_char_temp);

  strncpy(aux_dadtos_sensores + (largo_MAC + num_char_temp), aux.temp_1_SUP, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 2)), aux.temp_2_INF, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 3)), aux.temp_2_SUP, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 4)), aux.temp_3_INF, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 5)), aux.temp_3_SUP, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 6)), aux.hum_1_INF, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 7)), aux.hum_1_SUP, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 8)), aux.hum_2_INF, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 9)), aux.hum_2_SUP, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 10)), aux.hum_3_INF, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 11)), aux.hum_3_SUP, num_char_temp_);

  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 12)), aux.lluvia, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 13)), aux.CO2, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 14)), aux.UV, num_char_temp_);
  strncpy(aux_dadtos_sensores + (largo_MAC + (num_char_temp * 15)), fecha_char, 20);

  Serial.println("APPEND file");
  Serial.println(aux_dadtos_sensores);
  appendFile(SD, "/buffer_data.txt", aux_dadtos_sensores);
  appendFile(SD, "/buffer_data.txt", relleno);

  return 1;
}
void convert_data_sensor_zeros(char* aux, int dato) {
  //s procede a rellenar con ceros para dejarlo en base 000000 o 00005 o 00055
  char aux_[7] = "00000;";


  //itoa(dato, aux_, 10);
  sprintf(aux, "%05d;", dato);
}*/


//"MAC;temp_1_INF;temp_1_SUP;temp_2_INF;temp_2_SUP;temp_3_INF;temp_3_SUP;hum_1_INF;hum_1_SUP;hum_2_INF;hum_2_SUP;hum_3_INF;hum_3_SUP;fecha"
//  "MK1;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;00000;2022/12/03 14:05:00; "