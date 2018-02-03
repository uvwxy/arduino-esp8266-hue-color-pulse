#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <RGBConverter.h>

WiFiClient client;
RGBConverter conv;

void sendBody(String body, uint8_t light, String hueBridge, String hueApiKey) {
  if (client.connect(hueBridge, 80)) {

    String path =
        "PUT /api/" + hueApiKey + "/lights/" + String(light) + "/state";
    client.print(path);
    client.println(" HTTP/1.1");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(body.length());
    client.println();
    client.print(body);

    unsigned long currentMillis = millis(), previousMillis = millis();
    long interval = 2000;

    while (!client.available()) {

      if ((currentMillis - previousMillis) > interval) {

        Serial.println("Timeout");
        client.stop();
        return;
      }
      currentMillis = millis();
    }

    while (client.connected()) {
      if (client.available()) {
        char str = client.read();
        Serial.print(str);
      }
    }
    delay(100);
    client.stop();
  }
}

void sendHSB(bool on, uint16_t hue, uint8_t sat, uint8_t bri, uint8_t light,
             String hueBridge, String hueApiKey) {
  String body = String("{\"on\": ") + (on ? "true" : "false") +
                ", \"hue\": " + String(hue) + ", \"bri\": " + String(bri) +
                ", \"sat\": " + String(sat) + "}";

  Serial.println("H" + String(hue) + " S" + String(sat) + " B" + String(bri));
  sendBody(body, light, hueBridge, hueApiKey);
}

void sendRGBSB(bool on, uint8_t r, uint8_t g, uint8_t b, uint8_t sat,
               uint8_t bri, uint8_t light, String hueBridge, String hueApiKey) {
  double hsl[3];
  conv.rgbToHsl((byte)r, (byte)g, (byte)b, hsl);
  uint16_t hue = (uint16_t)(hsl[0] * 65535);

  String body = String("{\"on\": ") + (on ? "true" : "false") +
                ", \"hue\": " + String(hue) + ", \"bri\": " + String(bri) +
                ", \"sat\": " + String(sat) + "}";

  Serial.println("R" + String(r) + " G" + String(g) + " B" + String(b) + " S" +
                 String(sat) + " B" + String(bri));
  sendBody(body, light, hueBridge, hueApiKey);
}
