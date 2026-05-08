#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_IP = 0,
    FLOW_GLOBAL_VARIABLE_NETWORK = 1,
    FLOW_GLOBAL_VARIABLE_LED_COLOR = 2,
    FLOW_GLOBAL_VARIABLE_BOMB_TIMER = 3,
    FLOW_GLOBAL_VARIABLE_MONEY = 4,
    FLOW_GLOBAL_VARIABLE_EQUIP = 5
};

// Native global variables

extern const char *get_var_ip();
extern void set_var_ip(const char *value);
extern const char *get_var_network();
extern void set_var_network(const char *value);
extern int32_t get_var_led_color();
extern void set_var_led_color(int32_t value);
extern int32_t get_var_bomb_timer();
extern void set_var_bomb_timer(int32_t value);
extern const char *get_var_money();
extern void set_var_money(const char *value);
extern const char *get_var_equip();
extern void set_var_equip(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/