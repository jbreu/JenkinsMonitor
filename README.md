# JenkinsMonitor

Displays a Jenkins pipeline's current weather state on an ESP8266 with ST7789 display.

# Needed hardware parts

* NodeMCU with ESP8266: https://www.ebay.de/itm/NodeMCU-V3-3-ESP8266-ESP-12-E-Lua-CH340-WiFI-WLan-IoT-Arduino-Lolin-Mini-Micro/252718027546
* Display ST7789:
https://www.ebay.de/itm/1-3-Zoll-IPS-TFT-Display-SPI-240x240-RGB-ST7789-Full-Color-Arduino-ESP8266-PI/164068161846
* Connector cables (female/female):
dihttps://www.ebay.de/itm/120-stk-Jumper-Kabel-20-cm-3er-Set-MM-MF-FF-Wire-Buchse-Stecker-Breadboard/153440066859
* USB Cable (incl. power supply):
https://www.ebay.de/itm/1000maH-Ladegerät-Netzteil-Micro-USB-Kabel-Ladekabel-für-Original-Samsung-Galaxy/133339397231

# Hardware setup
Connect following 
* Display - ESP
* GND - GNG
* VCC - 3V
* DC  - D1 
* RES - D2
* SCL - D5
* SDA - D7

# Software setup

* edit config_example.h with appropriate content
* rename config_example.h to config.h
* compile with Arduino IDE

# Appeciation

Thanks to Stuki, oneleaveleft, GernhardFlick, DeathForce, dam, PsyDuck for inspiration and input.