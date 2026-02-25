#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LED_PIN 6
#define LED_COUNT 1
#define LDR_PIN A0
#define BUTTON_PIN 5

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Updated reference values
struct ColorRef {
  const char* name;
  int value;
};

ColorRef colorDB[] = {
  { "Black", 285 },  //problem1
  { "Green", 333 },
  { "Blue", 270 },  //problem1
  { "Gray", 405 },  //problem2
  { "Red", 433 },
  { "Orange", 419 },  //problem2
  { "Yellow", 485 },
  { "White", 500 }
};

const int COLOR_COUNT = sizeof(colorDB) / sizeof(colorDB[0]);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true)
      ;
  }

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 20);
  display.println("Hola");
  display.display();
  delay(1000);

  strip.begin();
  strip.show();
}

void loop() {
  waitForButton();

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("Measuring");
  display.display();

  // Illuminate surface
  strip.setPixelColor(0, strip.Color(255, 255, 255));
  strip.show();
  delay(500);

  // Take 5 LDR readings
  int readings = 0;
  for (int i = 0; i < 5; i++) {
    int value = analogRead(LDR_PIN);
    readings += value;
    Serial.print("Reading ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(value);
    delay(200);
  }

  int average = readings / 5;
  Serial.println("---------------------------");
  Serial.print("Average LDR value: ");
  Serial.println(average);

  const char* detectedColor = detectColor(average);
  Serial.print("Detected Color: ");
  Serial.println(detectedColor);
  Serial.println("---------------------------");

  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(5, 20);
  display.print(detectedColor);
  display.display();

  strip.clear();
  strip.show();

  delay(500);
}

// Waits for button press and release
void waitForButton() {
  Serial.println("Waiting for button press...");
  while (digitalRead(BUTTON_PIN) == HIGH)
    ;
  delay(50);
  while (digitalRead(BUTTON_PIN) == LOW)
    ;
  delay(50);
}

// Finds the closest matching color by absolute difference
const char* detectColor(int value) {
  long minSquareDiff = 999999;
  const char* bestMatch = "Unknown";

  for (int i = 0; i < COLOR_COUNT; i++) {
    long diff = value - colorDB[i].value;
    long squareDiff = diff * diff;

    if (squareDiff < minSquareDiff) {
      minSquareDiff = squareDiff;
      bestMatch = colorDB[i].name;
    }
  }

  return bestMatch;
}