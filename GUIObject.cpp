#include "GUIObject.h"

GUIObject::callback_map_type GUIObject::callbacks = {};

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

void GUIObject::setHidden(bool hiddenState)
{
    lv_obj_set_hidden(_content, hiddenState);
}

void GUIObject::align(const lv_obj_t *base, lv_align_t align, lv_coord_t x, lv_coord_t y)
{
    lv_obj_align(_content, base, align, x, y);
}

void GUIObject::eventCallback(lv_obj_t* kb, lv_event_t event)
{}

void GUIObject::__eventCallback(lv_obj_t* kb, lv_event_t event)
{
    callbacks.at(kb)(kb, event);
}
