/*********
  Marcelo Ferrarotti 2021

  BMP280 por I2C
  OLED SPI
*********/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_D1   23
#define OLED_D0   18
#define OLED_DC   16
#define OLED_CS   5
#define OLED_RES  17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_D1, OLED_D0, OLED_DC, OLED_RES, OLED_CS);


#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

#define SEALEVELPRESSURE_HPA (1025.00)

Adafruit_BMP280 bmp; // I2C
float temperature;
float pressure;

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  pinMode(32,INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Set values to send
  getReadings();
  Clima_display();
  //Serial.print("Temperatura: ");
  //Serial.println(temperature);
  //Serial.print("Presión: ");
  //Serial.println(pressure);
  //Serial.println();
  delay(500);
}

void Clima_display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE, 0);
  display.setCursor(0,0);
  display.print("Estado del clima:");
  display.setCursor(0, 10);
  display.print("Temp: ");
  display.setTextSize(2);
  display.print(temperature);
  display.print(" C");
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Pres: ");
  display.setTextSize(2);
  display.println(pressure);
  display.setTextSize(1);
  display.print("Pulsador: ");
  display.print(!digitalRead(32));
  display.display();
}

void getReadings() {
  temperature = bmp.readTemperature();
  pressure = (bmp.readPressure() / 100.0F);
}
