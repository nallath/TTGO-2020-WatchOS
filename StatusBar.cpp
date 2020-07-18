
#include "StatusBar.h"

LV_IMG_DECLARE(step);

StatusBar::StatusBar()
{
    memset(_array, 0, sizeof(_array));
}

void StatusBar::createIcons(lv_obj_t *par)
{
    _par = par;

    static lv_style_t barStyle;

    lv_style_init(&barStyle);
    lv_style_set_radius(&barStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color(&barStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&barStyle, LV_OBJ_PART_MAIN, LV_OPA_20);
    lv_style_set_border_width(&barStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_text_color(&barStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_image_recolor(&barStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

    _bar = lv_cont_create(_par, NULL);
    lv_obj_set_size(_bar,  LV_HOR_RES, _barHeight);
    lv_obj_add_style(_bar, LV_OBJ_PART_MAIN, &barStyle);

    _array[0].icon = lv_label_create(_bar, NULL);
    lv_label_set_text(_array[0].icon, "100%");

    _array[1].icon = lv_img_create(_bar, NULL);
    lv_img_set_src(_array[1].icon, LV_SYMBOL_BATTERY_FULL);

    _array[2].icon = lv_img_create(_bar, NULL);
    lv_img_set_src(_array[2].icon, LV_SYMBOL_WIFI);
    lv_obj_set_hidden(_array[2].icon, true);

    _array[3].icon = lv_img_create(_bar, NULL);
    lv_img_set_src(_array[3].icon, LV_SYMBOL_BLUETOOTH);
    lv_obj_set_hidden(_array[3].icon, true);

    //step counter
    _array[4].icon = lv_img_create(_bar, NULL);
    lv_img_set_src(_array[4].icon, &step);
    lv_obj_align(_array[4].icon, _bar, LV_ALIGN_IN_LEFT_MID, 10, 0);

    _array[5].icon = lv_label_create(_bar, NULL);
    lv_label_set_text(_array[5].icon, "0");
    lv_obj_align(_array[5].icon, _array[4].icon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    refresh();
}

void StatusBar::setStepCounter(uint32_t counter)
{
    lv_label_set_text(_array[5].icon, String(counter).c_str());
    lv_obj_align(_array[5].icon, _array[4].icon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
}

void StatusBar::updateLevel(int level)
{
    lv_label_set_text(_array[0].icon, (String(level) + "%").c_str());
    refresh();
}

void StatusBar::updateBatteryIcon(lv_icon_battery_t icon)
{
    const char *icons[6] = {LV_SYMBOL_BATTERY_EMPTY, LV_SYMBOL_BATTERY_1, LV_SYMBOL_BATTERY_2, LV_SYMBOL_BATTERY_3, LV_SYMBOL_BATTERY_FULL, LV_SYMBOL_CHARGE};
    lv_img_set_src(_array[1].icon, icons[icon]);
    refresh();
}

void StatusBar::show(lv_icon_status_bar_t icon)
{
    lv_obj_set_hidden(_array[icon].icon, false);
    refresh();
}

void StatusBar::setIconHidden(lv_icon_status_bar_t icon)
{
    lv_obj_set_hidden(_array[icon].icon, true);
    refresh();
}

uint8_t StatusBar::height()
{
    return _barHeight;
}

lv_obj_t* StatusBar::self()
{
    return _bar;
}

void StatusBar::refresh()
{
    int prev;
    for (int i = 0; i < 4; i++) {
        if (!lv_obj_get_hidden(_array[i].icon)) {
            if (i == LV_STATUS_BAR_BATTERY_LEVEL) {
                lv_obj_align(_array[i].icon, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
            } else {
                lv_obj_align(_array[i].icon, _array[prev].icon, LV_ALIGN_OUT_LEFT_MID, iconOffset, 0);
            }
            prev = i;
        }
    }
};
