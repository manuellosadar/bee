#include  "wifi_handler.h"
const char* ssid = "Lowi90AC";     // Cambia esto al nombre de tu red Wi-Fi
const char* password = "AC2ERNYDUM7WFN";  // Cambia esto a la contraseña de tu red Wi-Fi

void connectToWiFi() {
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a la red Wi-Fi");
}
int connectToWiFi_timeout() {
  unsigned long startTime = millis();
  unsigned long timeout = 60000; // 1 minuto en milisegundos

  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startTime > timeout) {
      Serial.println("Tiempo de espera agotado");
      guardar_error_log("WIFI ERROR,TIMEOUT,");
      return -1;
    }
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a la red Wi-Fi");
  return 1;
}
bool testInternetConnectivity() {
  IPAddress serverIP(8, 8, 8, 8); // Dirección IP de Google DNS (8.8.8.8)
  int port = 53; // Puerto para la prueba (DNS)

  WiFiClient client;
  if (!client.connect(serverIP, port)) {
    // No se pudo establecer conexión, lo que indica la falta de conectividad a Internet
    guardar_error_log("TEST ERROR CONNECTION,no connection to 8.8.8.8,");
    return false;
  }

  // Si te conectas con éxito, significa que tienes conectividad a Internet
  client.stop();
  return true;
}
