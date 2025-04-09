#include <WiFi.h>
#include <HTTPClient.h>

const int ledPin = 33;
unsigned long lastSendTime = -15000;  // Track last send time and start with -15s so it sends immediately

// ThingSpeak Settings
const char* ssid = "your_ssid";
const char* password = "your_pw";
const char* apiKey = "your_APIkey";
const char* server = "http://api.thingspeak.com/update";

// Initialize UART
#define RX_PIN 3  // Default UART RX pin for ESP32-CAM
#define TX_PIN 1  // Default UART TX pin for ESP32-CAM

void setup() {
  Serial.begin(115200);  // USB Serial Monitor
  Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);  // UART for STM32

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
      delay(200);
      Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  pinMode(ledPin, OUTPUT);
  blinkLED(2, 200);
}

void loop() {
  
  if (Serial1.available()) {

    String receivedData = Serial1.readStringUntil('\n');  // Read UART data
    receivedData.trim();  // Remove extra spaces/newlines

    if (receivedData.length() > 0) {  // Ensure it's not empty
    
      String value = String(receivedData.toInt());  // Ensure it's a valid number
      blinkLED(1, 200);   
         
      if (millis() - lastSendTime >= 15000) {
         
        sendToThingSpeak(value);
        lastSendTime = millis();  // Update last send time         
      }
    }   
  }
}

void sendToThingSpeak(String value) {
  if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      String url = String(server) + "?api_key=" + apiKey + "&field1=" + value;  // Create the full URL

      Serial.println("Sending Data to ThingSpeak: " + url);
      http.begin(url);
      int httpResponseCode = http.GET();
      
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);  // Print HTTP Response

      http.end();

      if (httpResponseCode > 0) {
          blinkLED(2, 200);  // Blink 2 times on success
      } else {
          blinkLED(5, 200);  // Blink 5 times on error
      }
  } else {
      Serial.println("WiFi Disconnected! Cannot send data.");
      blinkLED(5, 1000);  // Blink 5 times if WiFi is disconnected
  }
}

void blinkLED(int times, int duration) {
  while (times--) {
      digitalWrite(ledPin, LOW);
      delay(duration);
      digitalWrite(ledPin, HIGH);
      delay(duration);
  }
}
