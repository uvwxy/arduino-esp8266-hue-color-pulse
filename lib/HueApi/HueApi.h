#ifndef HUE_API_H
#define HUE_API_H

void sendBody(String body, uint8_t light, String hueBridge, String hueApiKey);
void sendHSB(bool on, uint16_t hue, uint8_t sat, uint8_t bri, uint8_t light,
             String hueBridge, String hueApiKey);
void sendRGBSB(bool on, uint8_t r, uint8_t g, uint8_t b, uint8_t sat,
               uint8_t bri, uint8_t light, String hueBridge, String hueApiKey);

#endif