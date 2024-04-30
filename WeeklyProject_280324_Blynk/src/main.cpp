#define BLYNK_TEMPLATE_ID "TMPL6jhUoEiwA"
#define BLYNK_TEMPLATE_NAME "LED BUZZER DHT11"
#define BLYNK_AUTH_TOKEN "-hXoH9yMAaJKBeGiOh_xV9yV9LlTNaz0"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "home sweet home";
char pass[] = "anakbaik";

BlynkTimer timer;

// Pin to which the LED is connected
#define BUZZ_PIN_AKTIF D6
#define LED_PIN_AKTIF D5
#define DHTPIN D7
#define BUZZ_PIN_PASIF 5
#define LED_PIN_PASIF 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void KirimSensor()
{
   int h = dht.readHumidity();
   int t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal Membaca Nilai Sensor DHT");
    return;
  }

  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);

  // Condition
  if (h > 90){
    digitalWrite(BUZZ_PIN_PASIF, HIGH);
    digitalWrite(LED_PIN_PASIF, HIGH);
  } else {
    digitalWrite(BUZZ_PIN_PASIF, LOW);
    digitalWrite(LED_PIN_PASIF, LOW);
  }
}

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  
  // Update state
  digitalWrite(BUZZ_PIN_AKTIF, value); // Negasi nilai karena pull-up resistor aktif
}

BLYNK_WRITE(V1)
{
  // Set incoming value from pin V1 to a variable
  int value = param.asInt();
  
  // Update state
  digitalWrite(LED_PIN_AKTIF, value); // Negasi nilai karena pull-up resistor aktif
}

void setup()
{
  pinMode(BUZZ_PIN_AKTIF, OUTPUT);
  pinMode(LED_PIN_AKTIF, OUTPUT);
  pinMode(BUZZ_PIN_PASIF, OUTPUT);
  pinMode(LED_PIN_PASIF, OUTPUT);

  // Debug console
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
 
  // Setup a function to be called every second
  timer.setInterval(1000L, KirimSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
