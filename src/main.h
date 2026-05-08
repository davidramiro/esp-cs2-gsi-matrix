#pragma once

#include "Display.h"
#include "AppConfig.h"
#include "GameState.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <aWOT.h>
#include "Index.h"
#include "ui/ui.h"

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

#include <WiFiUdp.h>

void handlePostGSI(Request &req, Response &res);

void setup();
void loop();