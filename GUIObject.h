
#ifndef __GUI_OBJECT_H
#define __GUI_OBJECT_H

#include "config.h"
#include <unordered_map>
#include <functional>

class GUIObject
{
public:
    typedef std::function<void(lv_obj_t*, lv_event_t)> callbackFunc;
    typedef std::unordered_map<lv_obj_t*, callbackFunc> callback_map_type;

    GUIObject();
    virtual ~GUIObject();

    virtual void create(lv_obj_t *parent = nullptr) = 0;
    virtual void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0);
    void setHidden(bool hiddenState);

protected:
    static callback_map_type callbacks;

    lv_obj_t* _content = nullptr;

    virtual void eventCallback(lv_obj_t* kb, lv_event_t event);

    // Callbacks need to be static, so use this function to handle them
    // If you want a non static callback, use bindEventCallback first
    static void __eventCallback(lv_obj_t* kb, lv_event_t event);

    // It's super tricky to put member functions in a map, so that why this
    // function should be used instead.
    template <typename T, typename std::enable_if<std::is_base_of<GUIObject, T>{}, int>::type = 0>
    void bindEventCallback (lv_obj_t* x, void(T::*newFn)(lv_obj_t*, lv_event_t))
    {
        callbacks.insert(std::make_pair(x, std::bind(newFn, static_cast<T*>(this), std::placeholders::_1, std::placeholders::_2)));
    }
};

#endif
