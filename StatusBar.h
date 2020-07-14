

#ifndef __STATUS_BAR_H
#define __STATUS_BAR_H

#include "config.h"


typedef enum {
    LV_ICON_BAT_EMPTY,
    LV_ICON_BAT_1,
    LV_ICON_BAT_2,
    LV_ICON_BAT_3,
    LV_ICON_BAT_FULL,
    LV_ICON_CHARGE,
    LV_ICON_CALCULATION
} lv_icon_battery_t;


typedef enum {
    LV_STATUS_BAR_BATTERY_LEVEL = 0,
    LV_STATUS_BAR_BATTERY_ICON = 1,
    LV_STATUS_BAR_WIFI = 2,
    LV_STATUS_BAR_BLUETOOTH = 3,
} lv_icon_status_bar_t;


class StatusBar
{
    typedef struct {
        bool vaild;
        lv_obj_t* icon;
    } lv_status_bar_t;

public:
    StatusBar();

    void createIcons(lv_obj_t *par);


    void setStepCounter(uint32_t counter);

    void updateLevel(int level);
    void updateBatteryIcon(lv_icon_battery_t icon);

    void show(lv_icon_status_bar_t icon);
    void hidden(lv_icon_status_bar_t icon);

    uint8_t height();
    lv_obj_t* self();
private:
    void refresh();

    lv_obj_t* _bar = nullptr;
    lv_obj_t* _par = nullptr;
    uint8_t _barHeight = 30;
    lv_status_bar_t _array[6];
    const int8_t iconOffset = -5;
};

#endif /*__STATUS_BAR_H */
