#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <U8g2lib.h>
#include <Wire.h>

// 👉 Reemplaza con los datos de tu red
const char* ssid = "Nombre de La Red WiFi";
const char* password = "Contraseña de La Red WiFi";

// Configuración del reloj NTP
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;      // Ajusta a tu zona horaria (3600 = UTC+1)
const int daylightOffset_sec = 3600;  // Verano = 3600, invierno = 0

// Configuración de la pantalla OLED en este caso es una SSD1306
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Configuración de la wifi
void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ¡Conectado!");
}

// Configuración del reloj NTP
// Esta función se encarga de sincronizar la hora con el servidor NTP
void setupTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Sincronizando hora...");
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" ¡Hora obtenida!");
}

// Esta función se encarga de dibujar la hora en la pantalla OLED
// La hora se obtiene del reloj NTP y se muestra en formato hh:mm:ss
void drawClock() {
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    char timeStr[9]; // hh:mm:ss
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont29_tn); // Fuente grande
    int x = (128 - u8g2.getStrWidth(timeStr)) / 2;  // Centrado horizontal
    u8g2.drawStr(x, 42, timeStr);
    u8g2.sendBuffer();
  } else {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x13_tr);
    u8g2.drawStr(10, 30, "Error NTP");
    u8g2.sendBuffer();
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);  // Espera a que el monitor serie esté listo
  setupWiFi();
  u8g2.begin();
  setupTime();
}

void loop() {
  drawClock();
  delay(1000);  // Actualiza cada segundo
}
