#ifndef __MENU_BAR_H
#define __MENU_BAR_H

#include "config.h"

class MenuBar
{
public:
    typedef struct {
        const char *name;
        void *img;
        void (*event_cb)();
    } lv_menu_config_t;

    MenuBar();

    void createMenu(lv_menu_config_t *config, int count, lv_event_cb_t event_cb, int direction = 1);

    lv_obj_t* exitBtn() const;

    lv_obj_t* self() const;

    void hidden(bool en = true);

    lv_obj_t *obj(int index) const;
private:
    lv_obj_t *_cont, *_view, *_exit, * *_obj;
    lv_point_t *_vp ;
    int _count = 0;
};

#endif /*__MENU_BAR_H */
