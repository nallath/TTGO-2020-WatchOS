#include "GUIObject.h"


GUIObject::GUIObject()
{
    _content = nullptr;
}

GUIObject::~GUIObject()
{
    if (_content == nullptr)
    {
        return;
    }
    lv_obj_del(_content);
    _content = nullptr;
}

void GUIObject::hidden(bool en)
{
    lv_obj_set_hidden(_content, en);
}

void GUIObject::align(const lv_obj_t *base, lv_align_t align, lv_coord_t x, lv_coord_t y)
{
    lv_obj_align(_content, base, align, x, y);
}
