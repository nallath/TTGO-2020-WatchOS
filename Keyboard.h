#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "config.h"

class Keyboard
{
public:
    typedef enum
    {
        KB_EVENT_OK,
        KB_EVENT_EXIT,
    } kb_event_t;

    typedef void (*kb_event_cb)(kb_event_t event);

    Keyboard();

    ~Keyboard();

    void create(lv_obj_t* parent = nullptr);

    void align(const lv_obj_t* base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0);

    static void __kb_event_cb(lv_obj_t* kb, lv_event_t event);

    void setKeyboardEvent(kb_event_cb cb);

    const char* getText();

    void hidden(bool en = true);

private:
    lv_obj_t* _kbCont = nullptr;
    kb_event_cb _cb = nullptr;
    static const char* btnm_mapplus[10][23];
    static Keyboard *_kb;
    static char __buf[128];
};

#endif /*__KEYBOARD_H */
