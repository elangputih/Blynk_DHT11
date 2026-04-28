/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID   "MASUKKAN_TEMPLATE_ID_DISINI"
#define BLYNK_TEMPLATE_NAME "MASUKKAN_TEMPLATE_NAME_DISINI"
#define BLYNK_AUTH_TOKEN    "MASUKKAN_AUTH_TOKEN_DISINI"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// Pengaturan WiFi
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// Pengaturan DHT
#define DHTPIN 4          // GPIO 4
#define DHTTYPE DHT11     // Ubah ke DHT22 jika perlu
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// Fungsi untuk mengirim data sensor ke Blynk
void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  // Kirim ke Virtual Pin di Blynk Cloud
  Blynk.virtualWrite(V1, t); // V1 untuk Suhu
  Blynk.virtualWrite(V2, h); // V2 untuk Kelembapan

  Serial.print("Data Terkirim -> Suhu: ");
  Serial.print(t);
  Serial.print("C, Kelembapan: ");
  Serial.print(h);
  Serial.println("%");
}

void setup() {
  Serial.begin(115200);

  // Memulai Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Memulai Sensor
  dht.begin();

  // Atur interval pengiriman data (misal: setiap 2 detik)
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run(); // Menjalankan timer Blynk
}
