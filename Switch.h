#ifndef __SWITH_H
#define __SWITH_H

#include "config.h"

LV_IMG_DECLARE(off);
LV_IMG_DECLARE(on);
LV_IMG_DECLARE(iexit);

class Switch
{
public:
    typedef struct {
        const char *name;
        void (*cb)(uint8_t, bool);
    } switch_cfg_t;

    typedef void (*exit_cb)();

    Switch();
    ~Switch();
    
    void create(switch_cfg_t* cfg, uint8_t count, exit_cb cb, lv_obj_t* parent = nullptr);

    void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0);

    void hidden(bool en = true);

    void setStatus(uint8_t index, bool en);

private:
    static void __switch_event_cb(lv_obj_t *obj, lv_event_t event);
    static Switch* _switch;
    lv_obj_t* _swCont = nullptr;
    uint8_t _count;
    lv_obj_t** _sw = nullptr;
    switch_cfg_t* _cfg = nullptr;
    lv_obj_t* _exitBtn = nullptr;
    exit_cb _exit_cb = nullptr;
};

#endif /*__SWITH_H */
