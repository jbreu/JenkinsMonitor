/*
   Basic ESP Client example, based on the ESP libraries examples
*/

#include <ESP8266WiFi.h>
//#include <ArduinoJson.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "data.h"
#include "config.h"

#define TFT_DC    D1     // TFT DC  pin is connected to NodeMCU pin D1 (GPIO5)
#define TFT_RST   D2     // TFT RST pin is connected to NodeMCU pin D2 (GPIO4)
#define TFT_CS    D8     // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)
#define LED       D4      // D4 declare LED pin on NodeMCU Dev Kit

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(LED, OUTPUT);   // Initialize the LED pin as an output
  digitalWrite(LED, LOW); // Turn the LED on
  Serial.begin(115200);
  delay(10);

  // Initialize Adafruit ST7789 TFT library
  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  digitalWrite(LED, HIGH); // Turn the LED off
}

void loop() {

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;

  //client.setFingerprint(fingerprint);
  client.setInsecure(); //the magic line, use with caution

  if (!client.connect(host, 443)) {
    digitalWrite(LED, LOW); // Turn the LED on
    Serial.println("connection failed");
    return;
  }
  digitalWrite(LED, HIGH); // Turn the LED on

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Authorization: Basic " + token + "\r\n" +
               "Connection: close\r\n\r\n");

  // Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('"result"');
    if (line == "result") {
      Serial.println("headers received");
      break;
    }
  }

  String line = client.readStringUntil('"timestamp"');
  line = client.readStringUntil('"timestamp"');

  Serial.println("==========");
  Serial.println("Result: ");
  Serial.println(line);
  Serial.println("==========");

  testdrawtext(line.c_str(), ST77XX_WHITE);

  delay(60000);
  //delay(600000);

}
void testdrawtext(const char *text, uint16_t color) {

  tft.setRotation(2);

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(25, 90);
  tft.setTextSize(6);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);

  tft.setCursor(25, 10);
  tft.setTextSize(5);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextWrap(true);
  tft.print("status");

  tft.setCursor(25, 160);
  tft.setTextSize(5);
  tft.setTextColor(ST77XX_RED);
  tft.setTextWrap(true);
  tft.print("Benis");

  int16_t x = 0;
  int16_t y = 0;
  int16_t w = 200;
  int16_t h = 200;

  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      uint16_t word = pgm_read_word(&((uint16_t *)myBitmap)[j * w + i]);
      tft.drawPixel(x + i, y, ~word );
    }
  }


}
