#include "Display.h"
#include "GameState.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoLog.h>
#include <aWOT.h>
#include "Index.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>          
#else
#include <WiFi.h>          
#endif

#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <WiFiManager.h>   

#include <NTPClient.h>
#include <WiFiUdp.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 170

void handlePostGSI(Request &req, Response &res);

void setup();
void loop();