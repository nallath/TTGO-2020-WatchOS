#include "Switch.h"

void Switch::create(lv_obj_t* parent)
{
    // TODO: ensure that a single switch can also be created.
    // The switch class needs refactoring anyway, since it's better to have a
    // single object per switch (instead of the weird hybrid that we have now!)
}

void Switch::create(switch_cfg_t* cfg, uint8_t count, exit_cb cb, lv_obj_t* parent)
{
    if (parent == nullptr)
    {
        parent = lv_scr_act();
    }

    static lv_style_t swlStyle;
    lv_style_init(&swlStyle);
    lv_style_set_radius(&swlStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&swlStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
    lv_style_set_border_width(&swlStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_border_opa(&swlStyle, LV_OBJ_PART_MAIN, LV_OPA_50);
    lv_style_set_text_color(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_image_recolor(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

    _exit_cb = cb;

    _content = lv_cont_create(parent, NULL);
    lv_obj_set_size(_content, LV_HOR_RES, LV_VER_RES - 30);
    lv_obj_align(_content, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(_content, LV_OBJ_PART_MAIN, &swlStyle);

    _count = count;
    _sw = new lv_obj_t *[count];
    _cfg = new switch_cfg_t [count];

    memcpy(_cfg, cfg, sizeof(switch_cfg_t) * count);

    lv_obj_t *prev = nullptr;
    for (int i = 0; i < count; i++)
    {
        lv_obj_t *la1 = lv_label_create(_content, NULL);
        lv_label_set_text(la1, cfg[i].name);
        i == 0 ? lv_obj_align(la1, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 20) : lv_obj_align(la1, prev, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
        _sw[i] = lv_imgbtn_create(_content, NULL);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_ACTIVE, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_RELEASED, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_PRESSED, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_CHECKED_RELEASED, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_CHECKED_PRESSED, &off);
        lv_obj_set_click(_sw[i], true);

        lv_obj_align(_sw[i], la1, LV_ALIGN_OUT_RIGHT_MID, 80, 0);
        lv_obj_set_event_cb(_sw[i], __eventCallback);
        bindEventCallback(_sw[i], &Switch::eventCallback);
        prev = la1;
    }

    _exitBtn = lv_imgbtn_create(_content, NULL);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_ACTIVE, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_RELEASED, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_PRESSED, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_CHECKED_RELEASED, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_CHECKED_PRESSED, &iexit);
    lv_obj_set_click(_exitBtn, true);

    lv_obj_align(_exitBtn, _content, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);

    lv_obj_set_event_cb(_exitBtn, __eventCallback);
    bindEventCallback(_exitBtn, &Switch::eventCallback);

}

void Switch::eventCallback(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_SHORT_CLICKED) {
        Serial.println("LV_EVENT_SHORT_CLICKED");
        if (obj == this->_exitBtn)
        {
            if (this->_exit_cb != nullptr)
            {
                this->_exit_cb();
                return;
            }
        }
    }

    if (event == LV_EVENT_SHORT_CLICKED)
     {
        Serial.println("LV_EVENT_VALUE_CHANGED");
        for (int i = 0; i < this->_count ; i++)
        {
            lv_obj_t* sw = this->_sw[i];
            if (obj == sw)
            {
                const void* src =  lv_imgbtn_get_src(sw, LV_BTN_STATE_RELEASED);
                const void* dst = src == &off ? &on : &off;
                bool en = src == &off;
                lv_imgbtn_set_src(sw, LV_BTN_STATE_ACTIVE, dst);
                lv_imgbtn_set_src(sw, LV_BTN_STATE_RELEASED, dst);
                lv_imgbtn_set_src(sw, LV_BTN_STATE_PRESSED, dst);
                lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_RELEASED, dst);
                lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_PRESSED, dst);
                if (this->_cfg[i].cb != nullptr)
                {
                    this->_cfg[i].cb(i, en);
                }
                return;
            }
        }
    }
}

void Switch::setStatus(uint8_t index, bool en)
{
    if (index > _count)
    {
        return;
    }
    lv_obj_t* sw = _sw[index];
    const void* dst =  en ? &on : &off;
    lv_imgbtn_set_src(sw, LV_BTN_STATE_ACTIVE, dst);
    lv_imgbtn_set_src(sw, LV_BTN_STATE_RELEASED, dst);
    lv_imgbtn_set_src(sw, LV_BTN_STATE_PRESSED, dst);
    lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_RELEASED, dst);
    lv_imgbtn_set_src(sw, LV_BTN_STATE_CHECKED_PRESSED, dst);
}
