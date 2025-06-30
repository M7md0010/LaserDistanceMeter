#define REMOTEXY_MODE__WIFI_POINT
#include <WiFi.h>
#include <RemoteXY.h>

#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = {
  255,0,0,4,0,22,0,19,0,0,0,0,31,1,106,200,1,1,1,0,
  67,30,93,40,10,78,2,26,2
};

struct {
  float value_01;
  uint8_t connect_flag;
} RemoteXY;
#pragma pack(pop)

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int buzzer = 19;
int vibration = 4;
int buttonPin = 18;
int recorded[3] = {0, 0, 0};
int recordIndex = 0;
bool lastButtonState = HIGH;

void setup() {
  RemoteXY_Init();

  if (!lox.begin()) {
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("VL53L0X Ready");
  display.display();

  pinMode(buzzer, OUTPUT);
  pinMode(vibration, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  RemoteXY_Handler();

  // Read sensor for display and feedback
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  // Handle button press with fresh reading
  bool buttonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && buttonState == LOW && recordIndex < 3) {
    VL53L0X_RangingMeasurementData_t snapshot;
    lox.rangingTest(&snapshot, false);
    if (snapshot.RangeStatus != 4 && snapshot.RangeMilliMeter != 8191) {
      recorded[recordIndex++] = snapshot.RangeMilliMeter;
    }
  }
  lastButtonState = buttonState;

  display.clearDisplay();

  // Show recorded distances
  display.setTextSize(1);
  display.setCursor(0, 0);
  for (int i = 0; i < recordIndex; i++) {
    display.print("#");
    display.print(i + 1);
    display.print(":");
    display.print(recorded[i]);
    display.println("mm");
  }

  // Display live distance and feedback
  display.setTextSize(2);
  String mainText;
  if (measure.RangeStatus != 4 && measure.RangeMilliMeter != 8191) {
    int dist = measure.RangeMilliMeter;
    RemoteXY.value_01 = dist;
    mainText = String(dist) + " mm";
    digitalWrite(buzzer, LOW);
    digitalWrite(vibration, LOW);
  } else {
    RemoteXY.value_01 = 0;
    mainText = "Out of range";
    digitalWrite(buzzer, HIGH);
    digitalWrite(vibration, HIGH);
  }

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(mainText, 0, 0, &x1, &y1, &w, &h);
  int xCenter = (SCREEN_WIDTH - w) / 2;
  int yCenter = (SCREEN_HEIGHT - h) / 2;
  display.setCursor(xCenter, yCenter);
  display.println(mainText);

  display.display();
  RemoteXY_delay(300);
}
