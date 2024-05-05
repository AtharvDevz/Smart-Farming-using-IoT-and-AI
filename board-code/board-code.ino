
#include <WiFi.h>
#include <HTTPClient.h>

#include "DHT.h"
#define DHTTYPE DHT11 
const int DHTPin = 14; 
DHT dht(DHTPin, DHTTYPE); 

const int soilMoisturePin = 33; 

const int airQualityPin = 35;
const char* sensorType = "MQ-135";
float Rclean = 10; 
float Vheat = 5; 
 
const char* ssid = ""; // Your wifi name or SSID.
const char* password = ""; // Your wifi password.
 
const char* host = "script.google.com";
const int httpsPort = 443;
 
String GAS_ID = ""; // spreadsheet script ID
 
void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  delay(500);
 
  dht.begin(); 
  delay(500);
  
  WiFi.begin(ssid, password); // Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
 
void loop() {
  Serial.print("MQ-135");
  int airQuality = analogRead(airQualityPin);

  Serial.print("AIR Quality : ");
  Serial.println(airQuality);
  float Rs = (float)(Rclean * (1023.0 - airQuality) / airQuality);

 
  float VOC = (Vheat / Rs - Vheat / Rclean) / Vheat * 1000; 
  Serial.print("Estimated VOC concentration: ");
  Serial.print(VOC);
  Serial.println(" ppm");

  Serial.print("DHT");
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("°C, Humidity: ");
  Serial.println(hum);
  Serial.println("%");

  Serial.print("Soil Moisture : ");
  int moistValue = analogRead(soilMoisturePin);
  float moisturePercentage = map(moistValue, 0, 4095, 100, 0);
  Serial.print("Moisture (%): ");
  Serial.println(moisturePercentage);

  
  sendData(temp, hum, moisturePercentage, airQuality,  VOC);
}
 
// Subroutine for sending data to Google Sheets
void sendData(float temp, float hum, float moistPercent, int airQuality, float voc) {
  String scriptUrl = "https://script.google.com/macros/s//exec?";
//  Data Will be Appended by get request at this url
  scriptUrl += "?temperature=" + String(temp);
  scriptUrl += "&humidity=" + String(hum);
  scriptUrl += "&moisture=" + String(moistPercent);
  scriptUrl += "&airQuality=" + String(airQuality);
  scriptUrl += "&voc=" + String(voc);
  scriptUrl += "&temperature=" + String(temp);
  Serial.print(scriptUrl);
  HTTPClient https;
  https.begin(scriptUrl);
  
  int httpResponseCode = https.GET();
  if (httpResponseCode > 0) {
    String payload = https.getString();
  } else {
    Serial.print("Error code: ");
  }

} 
