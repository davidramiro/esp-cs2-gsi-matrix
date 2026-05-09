#include "main.h"

#include "LVGL_Display.h"
#include "ui/vars.h"

WiFiServer server(80);
Application app;
GameState gameState;
Display dp;

esp_timer_handle_t lvgl_timer;
esp_timer_handle_t gamestate_timer;

uint8_t freezeFlipFlop = 0;
uint8_t standbyTick = 0;
bool started = false;

void handlePostGSI(Request &req, Response &res) {
  StaticJsonDocument<512> obj; // Use fixed size to avoid heap fragmentation
  const DeserializationError error = deserializeJson(obj, *req.stream());


  if (error) {
    Serial.printf("error deserializing json body: %s", error.c_str());
    res.print(error.c_str());
    res.status(500);
    return;
  }

  gameState.setHeartbeat();

  char const *phase = obj["round"]["phase"];
  char const *bomb = obj["round"]["bomb"];
  char const *win_team = obj["round"]["win_team"];
  int money = obj["player"]["state"]["money"];
  int equip = obj["player"]["state"]["equip_value"];

  std::string moneyStr = std::to_string(money);
  std::string equipStr = std::to_string(equip);

  set_var_equip(equipStr.c_str());
  set_var_money(moneyStr.c_str());

  if (phase && gameState.getPhase() != phase) {
    gameState.updateRoundPhase(phase);
  }

  if (bomb && gameState.getBombStatus() != bomb) {
    gameState.updateBombStatus(bomb);
  }

  if (win_team && gameState.getWinTeam() != win_team) {
    gameState.updateRoundWinTeam(win_team);
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

uint32_t millis_cb(void)
{
  return esp_timer_get_time() / 1000;
}

void lvgl_timer_callback(void *arg) {
  LVGLDisplay::handle();
  lv_task_handler();
  ui_tick();
}

void gamestate_tasks(void *arg) {
  if (gameState.getPhase() == "freezetime" && millis_cb() - gameState.getLastHeartBeat() < 60000) {
    if (freezeFlipFlop) {
      loadScreen(SCREEN_ID_FREEZETIME_1);
      freezeFlipFlop = 0;
    } else {
      loadScreen(SCREEN_ID_FREEZETIME);
      freezeFlipFlop = 1;
    }
  }

  if (gameState.getBombStatus() == "planted") {
    if (get_var_bomb_timer() > 0) {
      set_var_bomb_timer(get_var_bomb_timer() - 1);
    }
  }

  if (started && millis_cb() - gameState.getLastHeartBeat() > 60000) {
    loadScreen(SCREEN_ID_STANDBY);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  WiFiManager wm;

  LVGLDisplay::begin();

  lv_init();
  lv_tick_set_cb(millis_cb);
  lv_obj_clean(lv_scr_act());

  ui_init();

  esp_timer_create_args_t lvgl_timer_args = {
      .callback = lvgl_timer_callback,
      .name = "lvgl"
  };
  esp_timer_create(&lvgl_timer_args, &lvgl_timer);
  esp_timer_start_periodic(lvgl_timer, 5000); // 5ms

  esp_timer_create_args_t freezetime_timer_args = {
    .callback = gamestate_tasks,
    .name = "freezetime led"
};
  esp_timer_create(&freezetime_timer_args, &gamestate_timer);
  esp_timer_start_periodic(gamestate_timer, 500000); // 500ms

  delay(4000);

  loadScreen(SCREEN_ID_CONNECTING);

  bool res = wm.autoConnect("cs2screen");

  if (!res) {
    ESP.restart();
  }

  started = true;
  set_var_ip(WiFi.localIP().toString().c_str());
  set_var_network(WiFi.SSID().c_str());

  loadScreen(SCREEN_ID_CONNECTED);

  gameState.setHeartbeat();

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
