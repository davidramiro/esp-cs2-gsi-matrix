#include "main.h"

WiFiServer server(80);
Application app;
GameState gameState;
Display dp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

static volatile int flip = 0;
static volatile int freezetime_counter = 0;
static volatile int clock_delay = 10;

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

    for (JsonPair kv: weapons) {
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
    clock_delay = 10;
    dp.colorFill(TFT_BLACK);
  }

  if (bomb && gameState.getBombStatus().compare(bomb) != 0) {
    Log.verboseln("bomb status: %s", bomb);
    gameState.updateBombStatus(bomb);
    dp.colorFill(TFT_BLACK);
  }

  if (win_team && gameState.getWinTeam().compare(win_team) != 0) {
    Log.verboseln("won: %s", win_team);
    gameState.updateRoundWinTeam(win_team);
    clock_delay = 10;
    dp.colorFill(TFT_BLACK);
  }

  if (health != 0 && health != gameState.getHealth()) {
    Log.verboseln("health in game state: %d, health from request: %d",
                  gameState.getHealth(), health);
    gameState.updatePlayerHealth(health);
  }

  dp.updateDisplay(gameState);

  res.status(200);
  res.print("ok");
}

void handleGet(Request &req, Response &res) {
  res.set("Content-Type", "text/html");
  res.print(FPSTR(idx1));
  res.print(WiFi.localIP().toString());
  res.print(FPSTR(idx2));
}


void timer_callback(void *arg) {
  if (gameState.getPhase() == "freezetime") {
    int color;
    if (flip == 0) {
      color = TFT_BLUE;
      flip = 1;
    } else {
      color = TFT_RED;
      flip = 0;

      if (freezetime_counter < 15) {
        freezetime_counter++;
      }
    }
    dp.colorFill(color);
    char text[32];
    snprintf(text, sizeof(text), "BUY %d", 15 - freezetime_counter);
    dp.drawLargeTextTop(text, color);
  } else {
    flip = 0;
    freezetime_counter = 0;

    if (clock_delay > 0) {
      clock_delay--;
    } else {
      yield();
      dp.drawLargeTextTop(timeClient.getFormattedTime().c_str(), TFT_BLACK);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  while (!Serial);

  WiFiManager wm;

  dp.drawMediumText("Connecting to WiFi...");

  bool res = wm.autoConnect("cs2-screen");

  if (!res) {
    dp.drawMediumText("Connection error.");
    ESP.restart();
  } else {
    dp.drawMediumText("Connected :3");
  }

  dp.displayConnectionInfo(WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

  timeClient.begin();
  timeClient.setTimeOffset(3600);
  timeClient.update();

  // Set up the timer
  const esp_timer_create_args_t timer_args = {
    .callback = &timer_callback,
    .name = "one_second_timer"
  };
  esp_timer_handle_t timer_handle;
  esp_timer_create(&timer_args, &timer_handle);
  // Start timer: 1,000,000 microseconds = 1 second
  esp_timer_start_periodic(timer_handle, 500000);

  app.post("/", &handlePostGSI);
  app.get("/", &handleGet);
  server.begin();
}


void loop() {
  WiFiClient client = server.accept();

  if (client.connected()) {
    app.process(&client);
  }
}
