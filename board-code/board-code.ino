
#include <WiFi.h>
#include <HTTPClient.h>

#include "DHT.h"
#define DHTTYPE DHT11 // type of the temperature sensor
const int DHTPin = 14; //--> The pin used for the DHT11 sensor is Pin D1 = GPIO5
DHT dht(DHTPin, DHTTYPE); //--> Initialize DHT sensor, DHT dht(Pin_used, Type_of_DHT_Sensor);

const int soilMoisturePin = 33; 

const int airQualityPin = 35;
const char* sensorType = "MQ-135";
float Rclean = 10; // Rclean in Kilo Ohms (adjust based on your sensor datasheet and setup)
float Vheat = 5; // Heating voltage (adjust based on your sensor datasheet)
 
const char* ssid = "Galaxy M12 F160"; //--> Your wifi name or SSID.
const char* password = "sfkl8292"; //--> Your wifi password.
 
const char* host = "script.google.com";
const int httpsPort = 443;
 
String GAS_ID = "AKfycbxiXWms2R8jJ0_COniT6llxUh9bKeLpN60auMmkV-Z8-_bJLhxx3lDQmWUbUHHsXlHFeA"; //--> spreadsheet script ID
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting...");
  delay(500);
 
  dht.begin();  //--> Start reading DHT11 sensors
  delay(500);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
  //----------------------------------------Wait for connection
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
  float Rs = (float)(Rclean * (1023.0 - airQuality) / airQuality); // Calculate sensor resistance

  // Equation for estimating VOC concentration (adjust based on sensor datasheet and calibration)
  float VOC = (Vheat / Rs - Vheat / Rclean) / Vheat * 1000; // VOC in ppm (assuming a linear relationship)
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
  String scriptUrl = "https://script.google.com/macros/s/AKfycbyraPOk5wQ8zDMTv9JYYOWDd0Qp2kyXGRt4OjuJ-pSsZqe2eUgfn6uJ-PNwmVqDT6p3Yw/exec?";
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
