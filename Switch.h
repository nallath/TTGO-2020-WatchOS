#ifndef __SWITH_H
#define __SWITH_H

#include "config.h"
#include "GUIObject.h"

LV_IMG_DECLARE(off);
LV_IMG_DECLARE(on);
LV_IMG_DECLARE(iexit);

class Switch: public GUIObject
{
public:
    typedef struct {
        const char *name;
        void (*cb)(uint8_t, bool);
    } switch_cfg_t;

    typedef void (*exit_cb)();

    void create(switch_cfg_t* cfg, uint8_t count, exit_cb cb, lv_obj_t* parent = nullptr);
    void create(lv_obj_t* parent = nullptr);
    void setStatus(uint8_t index, bool en);

protected:
    void eventCallback(lv_obj_t* kb, lv_event_t event);
private:
    uint8_t _count;
    lv_obj_t** _sw = nullptr;
    switch_cfg_t* _cfg = nullptr;
    lv_obj_t* _exitBtn = nullptr;
    exit_cb _exit_cb = nullptr;
};

#endif /*__SWITH_H */
