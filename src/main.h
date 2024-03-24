#include "Display.h"
#include "GameState.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoLog.h>
#include <aWOT.h>

#if __has_include("WifiCredentials.h")
#include "WifiCredentials.h"
#else
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"
#endif

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#define PIN D2
#define BRIGHTNESS 96
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8

void handlePostGSI(Request &req, Response &res);

void setup();
void loop();