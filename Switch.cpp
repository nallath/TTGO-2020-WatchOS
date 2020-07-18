#include "Switch.h"


Switch::Switch()
{
    _swCont = nullptr;
}

Switch::~Switch()
{
    if (_swCont)
    {
        lv_obj_del(_swCont);
    }
    _swCont = nullptr;
}

void Switch::create(switch_cfg_t* cfg, uint8_t count, exit_cb cb, lv_obj_t* parent)
{
    static lv_style_t swlStyle;
    lv_style_init(&swlStyle);
    lv_style_set_radius(&swlStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&swlStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
    lv_style_set_border_width(&swlStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_border_opa(&swlStyle, LV_OBJ_PART_MAIN, LV_OPA_50);
    lv_style_set_text_color(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_image_recolor(&swlStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);


    if (parent == nullptr)
    {
        parent = lv_scr_act();
    }
    _exit_cb = cb;

    _swCont = lv_cont_create(parent, NULL);
    lv_obj_set_size(_swCont, LV_HOR_RES, LV_VER_RES - 30);
    lv_obj_align(_swCont, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(_swCont, LV_OBJ_PART_MAIN, &swlStyle);

    _count = count;
    _sw = new lv_obj_t *[count];
    _cfg = new switch_cfg_t [count];

    memcpy(_cfg, cfg, sizeof(switch_cfg_t) * count);

    lv_obj_t *prev = nullptr;
    for (int i = 0; i < count; i++)
    {
        lv_obj_t *la1 = lv_label_create(_swCont, NULL);
        lv_label_set_text(la1, cfg[i].name);
        i == 0 ? lv_obj_align(la1, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 20) : lv_obj_align(la1, prev, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
        _sw[i] = lv_imgbtn_create(_swCont, NULL);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_ACTIVE, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_RELEASED, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_PRESSED, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_CHECKED_RELEASED, &off);
        lv_imgbtn_set_src(_sw[i], LV_BTN_STATE_CHECKED_PRESSED, &off);
        lv_obj_set_click(_sw[i], true);

        lv_obj_align(_sw[i], la1, LV_ALIGN_OUT_RIGHT_MID, 80, 0);
        lv_obj_set_event_cb(_sw[i], __switch_event_cb);
        prev = la1;
    }

    _exitBtn = lv_imgbtn_create(_swCont, NULL);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_ACTIVE, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_RELEASED, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_PRESSED, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_CHECKED_RELEASED, &iexit);
    lv_imgbtn_set_src(_exitBtn, LV_BTN_STATE_CHECKED_PRESSED, &iexit);
    lv_obj_set_click(_exitBtn, true);

    lv_obj_align(_exitBtn, _swCont, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
    lv_obj_set_event_cb(_exitBtn, __switch_event_cb);

    _switch = this;
}


void Switch::align(const lv_obj_t *base, lv_align_t align, lv_coord_t x, lv_coord_t y)
{
    lv_obj_align(_swCont, base, align, x, y);
}

void Switch::hidden(bool en)
{
    lv_obj_set_hidden(_swCont, en);
}

void Switch::__switch_event_cb(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_SHORT_CLICKED) {
        Serial.println("LV_EVENT_SHORT_CLICKED");
        if (obj == _switch->_exitBtn)
        {
            if (_switch->_exit_cb != nullptr)
            {
                _switch->_exit_cb();
                return;
            }
        }
    }

    if (event == LV_EVENT_SHORT_CLICKED)
     {
        Serial.println("LV_EVENT_VALUE_CHANGED");
        for (int i = 0; i < _switch->_count ; i++)
        {
            lv_obj_t* sw = _switch->_sw[i];
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
                if (_switch->_cfg[i].cb != nullptr)
                {
                    _switch->_cfg[i].cb(i, en);
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
