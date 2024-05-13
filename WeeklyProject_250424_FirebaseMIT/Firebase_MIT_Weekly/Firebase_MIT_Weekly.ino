#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Mendefinisikan pin dan tipe sensor DHT
#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht11(DHTPIN, DHTTYPE);

int led = D5;

// Isikan sesuai pada Firebase
#define FIREBASE_HOST "fir-x-mit-weekly-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "4FlEjSyNVHUuv7mKMiquUJsfsygIpyzOLP5GlIHA"

// Nama WiFi
#define WIFI_SSID "home sweet home"
#define WIFI_PASSWORD "anakbaik"

// Mendeklarasikan objek data dari FirebaseESP8266
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);
  dht11.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); // Nilai awal relay akan off

  // Koneksi WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Konfigurasi Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
}

void loop() {
  // Sensor DHT11 membaca suhu dan kelembaban
  float t = dht11.readTemperature();
  float h = dht11.readHumidity();

  // Memeriksa apakah sensor berhasil membaca suhu dan kelembaban
  if (isnan(t) || isnan(h)) {
    Serial.println("Gagal membaca sensor DHT11");
    delay(1000);
    return;
  }

  // Menampilkan suhu dan kelembaban ke serial monitor
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Kelembaban: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println();

  // Memberikan status suhu kepada Firebase
  if (Firebase.setFloat(firebaseData, "/Data/suhu", t)) {
    Serial.println("Suhu terkirim");
  } else {
    Serial.println("Suhu tidak terkirim");
    Serial.println("Karena: " + firebaseData.errorReason());
  }

  // Memberikan status kelembaban kepada Firebase
  if (Firebase.setFloat(firebaseData, "/Data/kelembaban", h)) {
    Serial.println("Kelembaban terkirim");
    Serial.println();
  } else {
    Serial.println("Kelembaban tidak terkirim");
    Serial.println("Karena: " + firebaseData.errorReason());
  }

  // Mengendalikan LED berdasarkan kelembaban
  if (Firebase.getInt(firebaseData, "Data/LED")) {
  if (h >= 90) {
    digitalWrite(led, HIGH);
    Firebase.setInt(firebaseData, "Data/LED", 1);
  } else {
    digitalWrite(led, LOW); // LED2 mati jika suhu kurang dari 35 derajat Celsius
    Firebase.setInt(firebaseData, "Data/LED", 0);
   }
  }
  delay(1000);
}
