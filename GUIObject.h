
#ifndef __GUI_OBJECT_H
#define __GUI_OBJECT_H

#include "config.h"

class GUIObject
{
public:
    GUIObject();
    virtual ~GUIObject();
    virtual void create(lv_obj_t *parent = nullptr) = 0;
    virtual void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0);
    void hidden(bool en = true);
protected:
    lv_obj_t* _content = nullptr;
};

#endif
