#ifndef __LIST_H
#define __LIST_H

#include "config.h"
#include "GUIObject.h"

class List: public GUIObject
{
public:
    typedef void(*list_event_cb)(const char *);

    void create(lv_obj_t *parent = nullptr);

    void add(const char *txt, void *imgsrc = (void *)LV_SYMBOL_WIFI);

    void setListCallback(list_event_cb callback);

private:
    static void __listEventCallback(lv_obj_t *obj, lv_event_t event);
    static List* _list ;
    list_event_cb _callback = nullptr;
};

#endif /*__LIST_H */
