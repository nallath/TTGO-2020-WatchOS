#include "List.h"

void List::create(lv_obj_t *parent)
{
    if (parent == nullptr)
    {
        parent = lv_scr_act();
    }
    if (_content == nullptr)
    {
        static lv_style_t listStyle;
        lv_style_init(&listStyle);
        lv_style_set_radius(&listStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_bg_color(&listStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
        lv_style_set_bg_opa(&listStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
        lv_style_set_border_width(&listStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_text_color(&listStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
        lv_style_set_image_recolor(&listStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

        _content = lv_list_create(lv_scr_act(), NULL);
        lv_list_set_scrollbar_mode(_content, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_size(_content, LV_HOR_RES, LV_VER_RES - 30);

        lv_obj_add_style(_content, LV_OBJ_PART_MAIN, &listStyle);
        lv_obj_align(_content, NULL, LV_ALIGN_CENTER, 0, 0);
    }
    _list = this;
}

void List::add(const char *txt, void *imgsrc)
{
    lv_obj_t *btn = lv_list_add_btn(_content, imgsrc, txt);
    lv_obj_set_event_cb(btn, __listEventCallback);
}

void List::__listEventCallback(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_SHORT_CLICKED)
    {
        const char *txt = lv_list_get_btn_text(obj);
        if (_list->_callback != nullptr)
        {
            _list->_callback(txt);
        }
    }
}

void List::setListCallback(list_event_cb callback)
{
    _callback = callback;
}
