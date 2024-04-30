#define BLYNK_TEMPLATE_ID "TMPL6GmE8T7dO"
#define BLYNK_TEMPLATE_NAME "OTA"

#define BLYNK_FIRMWARE_VERSION        "0.1.3"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#include <DHT.h> //Library untuk DHT
#define DHTPIN D7 //deklarasi pin D3 untuk output dari DHT11
#define DHTTYPE DHT11 //Tipe DHT11
DHT dht(DHTPIN, DHTTYPE);
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

#define ledPin D5
BlynkTimer timer;

BLYNK_WRITE(V1){
  int pinValue = param.asInt();
  if(pinValue == 1){
    digitalWrite(ledPin, HIGH);
  }
  if(pinValue == 0){
    digitalWrite(ledPin, LOW);
  }
}

void sendSensor()
{
  float t = dht.readTemperature(); //pembacaan sensor (perhatikan perubahan tipe data menjadi float)
  float h = dht.readHumidity(); //perhatikan perubahan tipe data menjadi float

  if (isnan(t) || isnan(h)) { // periksa apakah nilai suhu dan kelembaban valid
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //menampilkan temperature dan humidity pada Serial monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("C ");
  Serial.print("Kelembaban: ");
  Serial.print(h);
  Serial.println("% ");

  Blynk.virtualWrite(V2, t); //mengirimkan data temperatur ke Virtual pin V2 di Blynk Cloud
  Blynk.virtualWrite(V3, h); //mengirimkan data kelembaban ke Virtual pin V3 di Blynk Cloud
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(ledPin, OUTPUT);
  dht.begin(); //mengaktifkan DHT11
  BlynkEdgent.begin();
  
  // Setup a timed function to send sensor data every 2 seconds
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}
