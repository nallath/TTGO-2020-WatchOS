#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "config.h"
#include "GUIObject.h"

class Keyboard: public GUIObject
{
public:
    typedef enum
    {
        KB_EVENT_OK,
        KB_EVENT_EXIT,
    } kb_event_t;

    typedef void (*kb_event_cb)(kb_event_t event);

    void create(lv_obj_t* parent = nullptr) override;

    void setKeyboardEvent(kb_event_cb cb);

    const char* getText();
    void eventCallback(lv_obj_t* kb, lv_event_t event);
private:
    lv_obj_t* _kbCont = nullptr;
    kb_event_cb _callback = nullptr;
    static const char* btnm_mapplus[10][23];

    char __buf[128];
};

#endif /*__KEYBOARD_H */
