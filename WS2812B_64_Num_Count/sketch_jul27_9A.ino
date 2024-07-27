#include <NeoPixelBus.h>

#define LED_PIN 5      // Pin connected to the data input of WS2812B LED strip
#define LED_COUNT 64   // Number of LEDs in the strip

// Define the color order of the LEDs (e.g., GRB)
#define COLOR_ORDER RGB

// Create an instance of the NeoPixelBus for the LED strip
NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> strip(LED_COUNT, LED_PIN);

// Arrays for target LEDs
const int targetLED0[] = {51,43,35,27,19,11,3,4,5,13,21,29,37,45,53,52};
const int targetLED1[] = {11,4,12,20,28,36,44,51,52,53};
const int targetLED2[] = {3,4,5,13,21,29,28,27,35,43,51,52,53};
const int targetLED3[] = {3,4,5,13,21,29,28,27,37,45,51,52,53};
const int targetLED4[] = {3,11,19,27,28,29,37,45,53,5,13,21};
const int targetLED5[] = {5,4,3,11,19,27,28,29,37,45,53,52,51};
const int targetLED6[] = {5,4,3,11,19,27,35,43,45,51,52,53,37,29,28};
const int targetLED7[] = {3,4,5,13,21,29,37,45,53,28,27};
const int targetLED8[] = {3,4,5,13,21,29,37,45,53,52,51,43,35,27,19,11,28};
const int targetLED9[] = {28,27,19,11,3,4,5,13,21,29,37,45,53};

const int* targetLEDs[] = {targetLED0, targetLED1, targetLED2, targetLED3, targetLED4, targetLED5, targetLED6, targetLED7, targetLED8, targetLED9};
const int targetLEDCounts[] = {16, 10, 13, 13, 12, 13, 15, 11, 17, 13};  // The number of elements in each targetLED array

unsigned long lastUpdateTime = 0; // Last time the animation was updated

void setup() {
  // Initialize the LED strip
  strip.Begin();
  strip.Show();  // Initialize all pixels to 'off'
}

void turnOnLEDs(const int* targetLEDs, int count, RgbColor color) {
  for (int i = 0; i < count; i++) {
    strip.SetPixelColor(targetLEDs[i], color);
    delay(10);
  }
  strip.Show();
}

void turnOffLEDs(const int* targetLEDs, int count) {
  for (int i = 0; i < count; i++) {
    strip.SetPixelColor(targetLEDs[i], RgbColor(0, 0, 0));
    delay(10);
  }
  strip.Show();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= 2500) {  // Change 2500 to adjust timing between each step
    lastUpdateTime = currentTime;

    // Turn off all LEDs
    for (int i = 0; i < LED_COUNT; i++) {
      strip.SetPixelColor(i, RgbColor(0, 0, 0)); // Turn off color
    }
    strip.Show();

    for (int i = 0; i < 10; i++) {
      turnOnLEDs(targetLEDs[i], targetLEDCounts[i], RgbColor(100, 0, 0)); // Red
      delay(1000);
      turnOffLEDs(targetLEDs[i], targetLEDCounts[i]);
    }
  }
}
