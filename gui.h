/*
Copyright (c) 2019 lewis he
This is just a demonstration. Most of the functions are not implemented.
The main implementation is low-power standby. 
The off-screen standby (not deep sleep) current is about 4mA.
Select standard motherboard and standard backplane for testing.
Created by Lewis he on October 10, 2019.
*/

#ifndef __GUI_H
#define __GUI_H

#include "StatusBar.h"

void setupGui();
void updateStepCounter(uint32_t counter);
void updateBatteryIcon(lv_icon_battery_t index);
void wifi_list_add(const char *ssid);
void wifi_connect_status(bool result);
void updateBatteryLevel();

#endif /*__GUI_H */
