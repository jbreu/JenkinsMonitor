#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h>
#include "data.h"
#include "config.h"

#define TFT_DC    D1     // TFT DC  pin is connected to NodeMCU pin D1 (GPIO5)
#define TFT_RST   D2     // TFT RST pin is connected to NodeMCU pin D2 (GPIO4)
#define TFT_CS    D8     // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)
#define LED       D4     // D4 declare LED pin on NodeMCU Dev Kit

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(LED, OUTPUT);
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
  // Don't check server's fingerprint for a fixed value
  client.setInsecure(); //the magic line, use with caution

  // TODO enable/disable client certificate by configuration
  X509List cert(clientcert);
  PrivateKey key(clientkey);
  client.setClientRSACert(&cert, &key);

  if (!client.connect(host, 443)) {
    digitalWrite(LED, LOW); // Turn the LED on
    Serial.println("connection failed");
    return;
  }
  digitalWrite(LED, HIGH); // Turn the LED on

  client.print(String("GET ") + url + reduction + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Authorization: Basic " + token + "\r\n" +
               "Connection: close\r\n\r\n");

  // Skip header
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line.startsWith("\r"))
      break;
  }

  // Read full response json
  String line = client.readStringUntil('\n');

  // Parse json for weather score
  DynamicJsonDocument json(1000);
  StaticJsonDocument<256> filter;
  filter["healthReport"][0]["score"] = true;
  auto error = deserializeJson(json, line, DeserializationOption::Filter(filter));
  //serializeJsonPretty(json, Serial);

  if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    tft.fillScreen(ST77XX_RED);
    return;
  }

  if (json["healthReport"][0]["score"].isNull()) {
    tft.fillScreen(ST77XX_RED);
    return;
  }

  int score = json["healthReport"][0]["score"];
  
  Serial.println(score);

  int16_t x = 0;
  int16_t y = 0;
  int16_t w = 200;
  int16_t h = 200;

  const unsigned char * image;

  switch (score) {
    case 100:
      image = sunny;
      break;
    case 80:
      image = partiallysunny;
      break;
    case 60:
      image = cloudy;
      break;
    case 40:
      image = raining;
      break;
    case 20:
      image = storm;
      break;
    case 0:
      image = storm;
      break;
    default:
      image = storm;
  }

  tft.fillScreen(ST77XX_BLACK);
  //tft.setRotation(2);

  // TODO Check if for all images the size is ok
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      uint16_t word = pgm_read_word(&((uint16_t *)image)[j * w + i]);
      if (word != 0x0000) {
        tft.drawPixel(20 + x + i, 20 + y, (((word<<8)&0xff00)|((word>>8)&0x00ff)) );
      }
    }
  }

  delay(60000);
}
