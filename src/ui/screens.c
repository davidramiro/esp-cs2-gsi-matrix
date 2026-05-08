#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_logo);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 37, 101);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_darken(lv_color_hex(0x3e3e3e), 77), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "STOP AFK IDIOT");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 78, 142);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_recolor(obj, true);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "VON DAVE FUER ADRI ");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_connecting() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.connecting = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_spinner_create(parent_obj);
            lv_obj_set_pos(obj, 120, 14);
            lv_obj_set_size(obj, 80, 80);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 114, 102);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Connecting...");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 33, 127);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "If WiFi hasn't been configured yet, \nconnect to the cs2screen network.");
        }
    }
    
    tick_screen_connecting();
}

void tick_screen_connecting() {
}

void create_screen_connected() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.connected = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 23, 48);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(0x00ff5e));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 78, 33);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Connected to:");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 78, 66);
            lv_obj_set_size(obj, 212, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 23, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "For setup, visit:");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 183, 133);
            lv_obj_set_size(obj, 106, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 138, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "http://");
        }
    }
    
    tick_screen_connected();
}

void tick_screen_connected() {
    {
        const char *new_val = get_var_network();
        const char *cur_val = lv_label_get_text(objects.obj2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj2;
            lv_label_set_text(objects.obj2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_ip();
        const char *cur_val = lv_label_get_text(objects.obj3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj3;
            lv_label_set_text(objects.obj3, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_t_win() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.t_win = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 25, 12);
            lv_obj_set_size(obj, 271, 146);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff8e2f), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 186, 69);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "T WIN");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 43, 25);
            lv_obj_set_size(obj, 120, 120);
            lv_image_set_src(obj, &img_t);
            lv_image_set_pivot(obj, 0, 0);
            lv_image_set_scale(obj, 120);
            lv_image_set_inner_align(obj, LV_IMAGE_ALIGN_DEFAULT);
        }
    }
    
    tick_screen_t_win();
}

void tick_screen_t_win() {
}

void create_screen_ct_win() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.ct_win = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 25, 12);
            lv_obj_set_size(obj, 271, 146);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x2f80ff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 172, 69);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "CT WIN");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 43, 25);
            lv_obj_set_size(obj, 120, 120);
            lv_image_set_src(obj, &img_ct);
            lv_image_set_pivot(obj, 0, 0);
            lv_image_set_scale(obj, 120);
            lv_image_set_inner_align(obj, LV_IMAGE_ALIGN_DEFAULT);
        }
    }
    
    tick_screen_ct_win();
}

void tick_screen_ct_win() {
}

void create_screen_freezetime() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.freezetime = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 25, 12);
            lv_obj_set_size(obj, 271, 146);
            add_style_blue(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 128, 22);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "BUY");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 47, 69);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Money: $");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 47, 112);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Equip:   $");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 185, 69);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 185, 112);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_freezetime();
}

void tick_screen_freezetime() {
    {
        const char *new_val = get_var_money();
        const char *cur_val = lv_label_get_text(objects.obj6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj6;
            lv_label_set_text(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_equip();
        const char *cur_val = lv_label_get_text(objects.obj7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj7;
            lv_label_set_text(objects.obj7, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_round_start() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.round_start = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 25, 12);
            lv_obj_set_size(obj, 271, 146);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x29b554), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 108, 77);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "ROUND START");
        }
    }
    
    tick_screen_round_start();
}

void tick_screen_round_start() {
}

void create_screen_bomb() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.bomb = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj9 = obj;
            lv_obj_set_pos(obj, 25, 12);
            lv_obj_set_size(obj, 271, 146);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff8e2f), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 135, 38);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "BOMB PLANTED");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 40, 28);
            lv_obj_set_size(obj, 95, 85);
            lv_image_set_src(obj, &img_bomb);
            lv_image_set_pivot(obj, 0, 0);
            lv_image_set_scale(obj, 120);
            lv_image_set_inner_align(obj, LV_IMAGE_ALIGN_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.obj10 = obj;
            lv_obj_set_pos(obj, 51, 136);
            lv_obj_set_size(obj, 218, 10);
            lv_bar_set_range(obj, 0, 80);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf32121), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_bomb();
}

void tick_screen_bomb() {
    {
        int32_t new_val = get_var_bomb_timer();
        int32_t cur_val = lv_bar_get_value(objects.obj10);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj10;
            lv_bar_set_value(objects.obj10, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_standby() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.standby = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj11 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 170);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj12 = obj;
            lv_obj_set_pos(obj, 8, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0x369d18));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj13 = obj;
            lv_obj_set_pos(obj, 24, 149);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Waiting for game...");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 211, 16);
            lv_obj_set_size(obj, 98, 137);
            lv_image_set_src(obj, &img_zaza);
            lv_image_set_scale(obj, 140);
        }
    }
    
    tick_screen_standby();
}

void tick_screen_standby() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_connecting,
    tick_screen_connected,
    tick_screen_t_win,
    tick_screen_ct_win,
    tick_screen_freezetime,
    tick_screen_round_start,
    tick_screen_bomb,
    tick_screen_standby,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 9) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
    create_screen_connecting();
    create_screen_connected();
    create_screen_t_win();
    create_screen_ct_win();
    create_screen_freezetime();
    create_screen_round_start();
    create_screen_bomb();
    create_screen_standby();
}