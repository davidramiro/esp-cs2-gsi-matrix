#include "main.h"

WiFiServer server(80);
Application app;
GameState gameState;
Display display(PIN, MATRIX_WIDTH, MATRIX_HEIGHT, BRIGHTNESS);

void handlePostGSI(Request &req, Response &res) {
  Log.verboseln("POST /");

  JsonDocument obj;
  DeserializationError error = deserializeJson(obj, *req.stream());

  if (error) {
    Log.errorln("error deserializing json body: %s", error.c_str());
    res.print(error.c_str());
    res.status(500);
    return;
  }

  char const *phase = obj["round"]["phase"];
  char const *bomb = obj["round"]["bomb"];
  char const *win_team = obj["round"]["win_team"];
  int health = obj["player"]["state"]["health"];
  const JsonObject weapons = obj["player"]["weapons"];

  if (weapons) {

    int ammoClip = -1;
    int ammoMax = -1;

    for (JsonPair kv : weapons) {
      if (kv.value()["state"] == "active") {
        ammoClip = kv.value()["ammo_clip"];
        ammoMax = kv.value()["ammo_clip_max"];
      }
    }

    if (ammoClip != -1 && ammoClip != gameState.getAmmoClip()) {
      gameState.updatePlayerAmmoClip(ammoClip);
    }

    if (ammoMax > 0 && ammoMax != gameState.getAmmoMax()) {
      gameState.updatePlayerAmmoMax(ammoMax);
    }
  }

  if (phase && gameState.getPhase().compare(phase) != 0) {
    Log.verboseln("phase in game state: %s, phase from request: %s",
                  gameState.getPhase().c_str(), phase);
    gameState.updateRoundPhase(phase);
  }

  if (bomb && gameState.getBombStatus().compare(bomb) != 0) {

    Log.verboseln("bomb status: %s", bomb);
    gameState.updateBombStatus(bomb);
  }

  if (win_team && gameState.getWinTeam().compare(win_team) != 0) {
    Log.verboseln("won: %s", win_team);
    gameState.updateRoundWinTeam(win_team);
  }

  if (health != 0 && health != gameState.getHealth()) {
    Log.verboseln("health in game state: %d, health from request: %d",
                  gameState.getHealth(), health);
    gameState.updatePlayerHealth(health);
  }

  display.updateDisplay(gameState);

  res.status(200);
  res.print("ok");
}

void setup() {
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  while (!Serial)
    ;

  WiFi.mode(WIFI_STA);
  WiFi.hostname("ESPCS2GSI");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int8_t wifiStatusCode = WiFi.waitForConnectResult();
  if (wifiStatusCode != WL_CONNECTED) {
    Log.errorln("Error connecting to WiFi, code %d", wifiStatusCode);
    display.showText("WiFi Error", 1500);

    return;
  }

  Log.infoln("IP: %p", WiFi.localIP());
  // display.showText(WiFi.localIP().toString().c_str(), 1500);

  app.post("/", &handlePostGSI);
  server.begin();
}

void loop() {
  WiFiClient client = server.accept();

  if (client.connected()) {
    app.process(&client);
  }
}
