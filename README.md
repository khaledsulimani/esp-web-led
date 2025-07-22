# ESP32 Web Server Project 🌐💡

This project demonstrates how to control the built-in LED on the *ESP32* using a simple *web interface*. The ESP32 creates a web server to control the LED via HTTP requests.

---

## Table of Contents 📝
- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)
- [Notes](#notes)
- [Troubleshooting](#troubleshooting)
- [Project Results](#Project-Results)
- [Code Explanation](#Code-Explanation)
- [Author](#Author)

---

## Project Overview 🚀
This project allows you to turn the built-in LED on and off using a web interface hosted by the *ESP32. The ESP32 connects to a Wi-Fi network and serves a webpage with buttons to control the LED. This is achieved using the **Arduino IDE* and a simple web server running on the ESP32.

---

## Hardware Requirements 🛠
- *ESP32* development board (e.g., ESP32 Dev Module)
  - *Built-in LED* (usually connected to GPIO2)
  
No external components such as resistors or jumper wires are required, as the LED is already integrated into the ESP32 board.

### *Built-in LED Pin*:
- The *built-in LED* is typically connected to *GPIO2* on most ESP32 boards.
  - *LED Anode (positive)* is connected to *GPIO2*.
  - *LED Cathode (negative)* is internally connected to *GND*.

---

## Software Requirements 💻
- *Arduino IDE* (or PlatformIO) installed
- *ESP32 core* for Arduino (download via *Arduino IDE > Tools > Board > Board Manager*)
- *Libraries*:
  - WiFi (comes with ESP32 core)
  - WebServer (comes with ESP32 core)

---

## Setup Instructions ⚙

1. *Install the ESP32 Core for Arduino*:
   - Go to *File > Preferences* in Arduino IDE.
   - Add the following URL to *Additional Boards Manager URLs*:
     
     https://dl.espressif.com/dl/package_esp32_index.json
     
   - Then go to *Tools > Board > Board Manager* and search for *ESP32. Install the **ESP32 by Espressif Systems*.

2. *Install the Necessary Libraries*:
   The required libraries are included with the ESP32 core. Make sure you have the *WiFi* and *WebServer* libraries available.

3. *Upload the Code*:
   - Download the project files to your local machine.
   - Open the web_led/web_led.ino file in *Arduino IDE*.
   - Connect your *ESP32* to your computer via USB.
   - In *Arduino IDE, select your ESP32 board under **Tools > Board > ESP32 Dev Module*.
   - Choose the correct *Port* from *Tools > Port*.
   - Upload the code to your ESP32.

4. *Connect to Wi-Fi*:
   - Modify the **ssid** and **password** in the code with your Wi-Fi credentials.
   - The ESP32 will connect to your Wi-Fi and display the IP address in the *Serial Monitor*.

---

## Usage 🌍

1. Once the ESP32 is connected to Wi-Fi, open the *Serial Monitor* to get the IP address of the ESP32.
2. Open a web browser and enter the IP address shown in the *Serial Monitor* (e.g., http://192.168.x.xxx).
3. The webpage will load with options to turn the built-in LED on or off.
4. Click the links to control the LED.

---

## Notes 📝
- Ensure that your device (computer, phone, etc.) is connected to the same Wi-Fi network as the ESP32.
- The IP address of the ESP32 may change each time it connects to the Wi-Fi, so check the *Serial Monitor* for the correct address.
- If you encounter issues, check the *Baud rate* in *Serial Monitor* is set to *9600* and ensure the ESP32 is properly connected.

---

## Troubleshooting ⚠
- If you face issues uploading the code, make sure the correct board and port are selected in *Arduino IDE*.
- If you are unable to see the ESP32's IP address, ensure that your Wi-Fi credentials are correct.
- If the LED doesn't turn on/off, check your browser and ensure you're entering the correct IP address.

---

## 📸 Project Results

### *simple video*:

https://github.com/user-attachments/assets/ea90deeb-d0d1-4539-a34d-5640dc0de959



---
## *Code Explanation* 📝💻

### *led define and web server*:
The code is designed to controll led and lunch webserver*.

```cpp
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

const char *ssid = "xxxxxx";     // CHANGE IT
const char *password = "xxxxxxxx";  // CHANGE IT

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
```
### *html code*:
The code is html code so we can use the buttons and chainge led status*.

```cpp
// محتويات ملف index.h
const char webpage[] PROGMEM = R"rawliteral(
  <html>
    <body>
      <h1>Control LED</h1>
      <p>LED is %LED_STATE%</p>
      <p><a href="/led1/on">Turn ON</a></p>
      <p><a href="/led1/off">Turn OFF</a></p>
    </body>
  </html>
)rawliteral";

```
---

## 🧑‍💻 Author
- **khaled mahmoud sulaimani** – [@khaledsulimani](https://github.com/khaledsulimani)

---

