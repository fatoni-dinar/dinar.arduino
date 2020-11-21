#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
//OTA
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

SimpleTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "TULIS KODE AUTH KAMU";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TULIS NAMA WIFI KAMU";
char pass[] = "TULIS PASS WIFI KAMU";

const int output16 = 16;
const int output5 = 5;
const int output4 = 4;
const int output0 = 0;
const int output2 = 2;
const int output14 = 14;
const int output12 = 12;
const int output13 = 13;
const int output15 = 15;
const int output3 = 3; //TX
const int output1 = 1; //RX

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //Blynk.begin(auth, ssid, pass);
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  Blynk.begin(auth, ssid, pass, IPAddress(66,96,233,186), 8080);
  
  delay(3000);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output13, OUTPUT);
  pinMode(output15, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output1, OUTPUT);


  // Set outputs to HIGH

  digitalWrite(output5, HIGH);
  digitalWrite(output4, HIGH);
  digitalWrite(output2, HIGH);
  digitalWrite(output14, HIGH);
  digitalWrite(output12, HIGH);
  digitalWrite(output13, HIGH);
  digitalWrite(output15, HIGH);
  digitalWrite(output3, HIGH);
  digitalWrite(output1, HIGH);

  pinMode(output0, OUTPUT);
  digitalWrite(output0, HIGH);
}

void loop()
{
  ArduinoOTA.handle();
  timer.run();
  Blynk.run();
}
