#include <string.h>
#include "vars.h"

char ip[100] = { 0 };
char network[100] = { 0 };
int32_t led_color;
int32_t bomb_timer;
char equip[100] = { 0 };
char money[100] = { 0 };

const char *get_var_money() {
    return money;
}

void set_var_money(const char *value) {
    strncpy(money, value, sizeof(money) / sizeof(char));
    money[sizeof(money) / sizeof(char) - 1] = 0;
}
const char *get_var_equip() {
    return equip;
}

void set_var_equip(const char *value) {
    strncpy(equip, value, sizeof(equip) / sizeof(char));
    equip[sizeof(equip) / sizeof(char) - 1] = 0;
}


int32_t get_var_bomb_timer() {
    return bomb_timer;
}

void set_var_bomb_timer(int32_t value) {
    bomb_timer = value;
}

int32_t get_var_led_color() {
    return led_color;
}

void set_var_led_color(int32_t value) {
    led_color = value;
}


const char *get_var_ip() {
    return ip;
}

void set_var_ip(const char *value) {
    strncpy(ip, value, sizeof(ip) / sizeof(char));
    ip[sizeof(ip) / sizeof(char) - 1] = 0;
}

const char *get_var_network() {
    return network;
}

void set_var_network(const char *value) {
    strncpy(network, value, sizeof(network) / sizeof(char));
    network[sizeof(network) / sizeof(char) - 1] = 0;
}