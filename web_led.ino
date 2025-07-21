/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-controls-led-via-web
 */

#include <WiFi.h>
#include <WebServer.h>
#include "index.h"  // Include the index.h file containing the HTML

#define LED_PIN 2  // ESP32 pin GPIO2 connected to LED

const char *ssid = "AMS";     // CHANGE IT
const char *password = "0505522619";  // CHANGE IT

WebServer server(80);

int LED_state = LOW;

String getHTML() {
  String html = webpage;                                  // Use the HTML content from the index.h file
  html.replace("%LED_STATE%", LED_state ? "ON" : "OFF");  // Update the LED state in the HTML
  return html;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_state);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32's IP address
  Serial.print("ESP32 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  // Home page route
  server.on("/", HTTP_GET, []() {
    Serial.println("ESP32 Web Server: New request received:");
    Serial.println("GET /");
    server.send(200, "text/html", getHTML());
  });

  // Route to control the LED (Turn it ON)
  server.on("/led1/on", HTTP_GET, []() {
    Serial.println("ESP32 Web Server: New request received:");
    Serial.println("GET /led1/on");
    LED_state = HIGH;
    digitalWrite(LED_PIN, LED_state);
    server.send(200, "text/html", getHTML());
  });

  // Route to control the LED (Turn it OFF)
  server.on("/led1/off", HTTP_GET, []() {
    Serial.println("ESP32 Web Server: New request received:");
    Serial.println("GET /led1/off");
    LED_state = LOW;
    digitalWrite(LED_PIN, LED_state);
    server.send(200, "text/html", getHTML());
  });

  // Start the server
  server.begin();
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
