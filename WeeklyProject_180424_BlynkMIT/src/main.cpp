#define BLYNK_TEMPLATE_ID "TMPL6vZncTFe_"
#define BLYNK_TEMPLATE_NAME "Blynk API x MIT"
#define BLYNK_AUTH_TOKEN "Ew769hLpFvr_WiVbfXQZCLZiUhRCzDeJ"

#include <ESP8266WiFi.h> // include library
#include <BlynkSimpleEsp8266.h>
#include <DHT.h> //Library untuk DHT
#include <Adafruit_Sensor.h>

#define led1 D5
#define led2 D6
#define DHTPIN D7 //deklarasi pin D3 untuk output dari DHT11
#define DHTTYPE DHT11 //Tipe DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN ; //Auth Token

char ssid[] = "home sweet home"; //nama hotspot yang digunakan
char pass[] = "anakbaik"; //password hotspot yang digunakan

BLYNK_WRITE(V0)
{
int pinValue = param.asInt();
digitalWrite(led1,pinValue);
}
BLYNK_WRITE(V1)
{
int pinValue1 = param.asInt();
digitalWrite(led2,pinValue1);
}

//function untuk pengiriman sensor
void sendSensor()
{
float t = dht.readTemperature(); //pembacaan sensor
float h = dht.readHumidity();
Serial.print("% Temperature: ");
Serial.print(t);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(h);
Serial.println("% ");

Blynk.virtualWrite(V2, t); //mengirimkan data temperatur ke Virtual pin VO di Blynk Cloud
Blynk.virtualWrite(V3, h); //mengirimkan data kelemaban ke Virtual pin V1 di Blynk Cloud

}
void setup() {
Serial.begin(115200); //serial monitor menggunakan bautrate 9600
Blynk.begin(auth, ssid, pass); //memulai Blynk
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
dht.begin(); //mengaktifkan DHT11
timer.setInterval(1000L, sendSensor); //Mengaktifkan timer untuk pengiriman data 1000ms
}

void loop() {
Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}