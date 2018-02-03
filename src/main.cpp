#include <Arduino.h>
#include <BuildInfo.h>

#include "config.h" // create from config.h.example!

#include <ESP8266WiFi.h>

#include <HueApi.h>

void setup() {
  pinMode(D4, OUTPUT);

  Serial.begin(9600);

  Serial.println("Starting");

  uint8_t tries = 0;
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WIFI");
    if (tries % 10 == 0) {
      WiFi.begin(WIFI_SSID, WIFI_PASS);
    }
    delay(1000);

    tries++;
  }

  Serial.println("Connected to WIFI");
}

uint8_t diff = 0;
bool up = true;

uint8_t smallDiff = 0;
bool smallUp = true;

void loop(void) {
  smallDiff = smallUp ? smallDiff + 1 : smallDiff - 1;
  smallUp = (diff == 20 || diff == 0) ? !smallUp : smallUp;

  diff = up ? diff + 1 : diff - 1;
  up = (diff == 255 || diff == 0) ? !up : up;

  // enable led when sending
  digitalWrite(D4, LOW);

  // hue pulse
  sendHSB(true, 255 * diff, 195 + ((smallDiff % 20) * 3), 0.8 * 255, HUE_LIGHT,
          HUE_BRIDGE, HUE_API_KEY);

  digitalWrite(D4, HIGH);

  delay(4 * 1000);
}