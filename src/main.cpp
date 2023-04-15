#include <Arduino.h>
#include <NeoPixelBus.h>

const uint16_t PixelCount = 100;
const uint8_t PixelPin = 27;

#define colorSaturation 128

NeoPixelBus<NeoGrbFeature, NeoWs2811Method> strip(PixelCount, PixelPin);

uint32_t rainbow_speed = 10;

RgbColor color_wheel(uint8_t pos);
void fill_rainbow(uint8_t offset);
void rainbow();


void setup()
{
  Serial.begin(115200);
  
  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();
}

void loop()
{
  rainbow();
}

RgbColor color_wheel(uint8_t pos)
{
  uint16_t p = (uint8_t)pos;

  if (p < 85)
  {
    return RgbColor((uint8_t)(255 - p * 3), (uint8_t)(p * 3), (uint8_t)0);
  }
  else if (p < 170)
  {
    p -= 85;
    return RgbColor((uint8_t)0, (uint8_t)(255 - p * 3), (uint8_t)(p * 3));
  }
  else
  {
    p -= 170;
    return RgbColor((uint8_t)(p * 3), (uint8_t)0, (uint8_t)(255 - p * 3));
  }
}

void fill_rainbow(uint8_t offset) {
  uint16_t color_index = 0;
  for (uint16_t i = 0; i < PixelCount; i++)
  {
    color_index = (i + (uint16_t)offset) % 256;
    strip.SetPixelColor(i, color_wheel(color_index));
  }
}

void rainbow()
{
  for (int i = 0; i < 256; i++)
  {
    fill_rainbow(i);
    strip.Show();
    vTaskDelay(rainbow_speed / portTICK_PERIOD_MS);
  }
}
