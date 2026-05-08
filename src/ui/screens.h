#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_CONNECTING = 2,
    SCREEN_ID_CONNECTED = 3,
    SCREEN_ID_T_WIN = 4,
    SCREEN_ID_CT_WIN = 5,
    SCREEN_ID_FREEZETIME = 6,
    SCREEN_ID_ROUND_START = 7,
    SCREEN_ID_BOMB = 8,
    SCREEN_ID_STANDBY = 9,
    _SCREEN_ID_LAST = 9
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *connecting;
    lv_obj_t *connected;
    lv_obj_t *t_win;
    lv_obj_t *ct_win;
    lv_obj_t *freezetime;
    lv_obj_t *round_start;
    lv_obj_t *bomb;
    lv_obj_t *standby;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_connecting();
void tick_screen_connecting();

void create_screen_connected();
void tick_screen_connected();

void create_screen_t_win();
void tick_screen_t_win();

void create_screen_ct_win();
void tick_screen_ct_win();

void create_screen_freezetime();
void tick_screen_freezetime();

void create_screen_round_start();
void tick_screen_round_start();

void create_screen_bomb();
void tick_screen_bomb();

void create_screen_standby();
void tick_screen_standby();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/