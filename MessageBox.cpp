#include "MessageBox.h"

MessageBox::MessageBox()
{
    _messageBox = nullptr;
}

MessageBox::~MessageBox()
{
    if (_messageBox == nullptr)
    {
        return;
    }
    lv_obj_del(_messageBox);
    _messageBox = nullptr;
}

void MessageBox::create(const char *text, lv_event_cb_t event_cb, const char **btns, lv_obj_t *par)
{
    if (_messageBox != nullptr)
    {
        return;
    }
    lv_obj_t *p = par == nullptr ? lv_scr_act() : par;
    _messageBox = lv_msgbox_create(p, NULL);
    lv_msgbox_set_text(_messageBox, text);
    if (btns == nullptr)
    {
        static const char *defBtns[] = {"Ok", ""};
        lv_msgbox_add_btns(_messageBox, defBtns);
    } else {
        lv_msgbox_add_btns(_messageBox, btns);
    }
    lv_obj_set_width(_messageBox, LV_HOR_RES - 40);
    lv_obj_set_event_cb(_messageBox, event_cb);
    lv_obj_align(_messageBox, NULL, LV_ALIGN_CENTER, 0, 0);
}

void MessageBox::setData(void *data)
{
    lv_obj_set_user_data(_messageBox, data);
}

void* MessageBox::getData()
{
    return lv_obj_get_user_data(_messageBox);
}

void MessageBox::setBtn(const char** btns)
{
    lv_msgbox_add_btns(_messageBox, btns);
}
