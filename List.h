#ifndef __LIST_H
#define __LIST_H

#include "config.h"

class List
{
public:
    typedef void(*list_event_cb)(const char *);
    List() {}
    ~List();

    void create(lv_obj_t *parent = nullptr);

    void add(const char *txt, void *imgsrc = (void *)LV_SYMBOL_WIFI);

    void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0);

    void hidden(bool en = true);

    void setListCallback(list_event_cb callback);

private:
    static void __listEventCallback(lv_obj_t *obj, lv_event_t event);
    lv_obj_t* _listCont = nullptr;
    static List* _list ;
    list_event_cb _callback = nullptr;
};

#endif /*__LIST_H */
