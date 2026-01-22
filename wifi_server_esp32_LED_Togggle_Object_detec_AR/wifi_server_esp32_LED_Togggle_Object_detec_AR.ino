#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "JioFiber-Suni";
const char* password = "3521@KiiT";

WebServer server(80);

#define LED_PIN 4   // Built-in LED

bool ledState = false;   // LED OFF initially

void toggleLED() {
  ledState = !ledState;              // Toggle state
  digitalWrite(LED_PIN, ledState);   // Apply state

  Serial.print("LED State: ");
  Serial.println(ledState ? "ON" : "OFF");

  server.send(200, "text/plain", ledState ? "LED ON" : "LED OFF");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nESP32 Connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.on("/toggle", toggleLED);
  server.begin();
}

void loop() {
  server.handleClient();
}
