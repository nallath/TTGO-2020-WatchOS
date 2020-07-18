#include "Keyboard.h"

const char *Keyboard::btnm_mapplus[10][23] = {
    {
        "a", "b", "c",   "\n",
        "d", "e", "f",   "\n",
        "g", "h", "i",   "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "j", "k", "l", "\n",
        "n", "m", "o",  "\n",
        "p", "q", "r",  "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "s", "t", "u",   "\n",
        "v", "w", "x", "\n",
        "y", "z", " ", "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "A", "B", "C",  "\n",
        "D", "E", "F",   "\n",
        "G", "H", "I",  "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "J", "K", "L", "\n",
        "N", "M", "O",  "\n",
        "P", "Q", "R", "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "S", "T", "U",   "\n",
        "V", "W", "X",   "\n",
        "Y", "Z", " ", "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "1", "2", "3",  "\n",
        "4", "5", "6",  "\n",
        "7", "8", "9",  "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "0", "+", "-",  "\n",
        "/", "*", "=",  "\n",
        "!", "?", "#",  "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "<", ">", "@",  "\n",
        "%", "$", "(",  "\n",
        ")", "{", "}",  "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    },
    {
        "[", "]", ";",  "\n",
        "\"", "'", ".", "\n",
        ",", ":",  " ", "\n",
        LV_SYMBOL_LEFT, "Del", LV_SYMBOL_OK, LV_SYMBOL_RIGHT, ""
    }
};

void Keyboard::create(lv_obj_t* parent)
{
    static lv_style_t kbStyle;

    lv_style_init(&kbStyle);
    lv_style_set_radius(&kbStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color(&kbStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&kbStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
    lv_style_set_border_width(&kbStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_text_color(&kbStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_image_recolor(&kbStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

    if (parent == nullptr)
    {
        parent = lv_scr_act();
    }

    _content = lv_cont_create(parent, NULL);
    lv_obj_set_size(_content, LV_HOR_RES, LV_VER_RES - 30);
    lv_obj_align(_content, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(_content, LV_OBJ_PART_MAIN, &kbStyle);

    lv_obj_t *ta = lv_textarea_create(_content, NULL);
    lv_obj_set_height(ta, 40);
    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_pwd_mode(ta, false);
    lv_textarea_set_text(ta, "");

    lv_obj_align(ta, _content, LV_ALIGN_IN_TOP_MID, 10, 10);

    lv_obj_t *kb = lv_keyboard_create(_content, NULL);
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_TEXT_LOWER, btnm_mapplus[0]);
    lv_obj_set_height(kb, LV_VER_RES / 3 * 2);
    lv_obj_set_width(kb, 240);
    lv_obj_align(kb, _content, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_keyboard_set_textarea(kb, ta);

    lv_obj_add_style(kb, LV_OBJ_PART_MAIN, &kbStyle);
    lv_obj_add_style(ta, LV_OBJ_PART_MAIN, &kbStyle);

    lv_obj_set_event_cb(kb, __eventCallback);

    bindEventCallback(kb, &Keyboard::eventCallback);
}

void Keyboard::eventCallback(lv_obj_t* kb, lv_event_t event)
{
    if (event != LV_EVENT_VALUE_CHANGED && event != LV_EVENT_LONG_PRESSED_REPEAT)
    {
        return;
    }
    lv_keyboard_ext_t* ext = (lv_keyboard_ext_t*)lv_obj_get_ext_attr(kb);
    const char* txt = lv_btnmatrix_get_active_btn_text(kb);
    if (txt == NULL)
    {
        return;
    }

    static int index = 0;
    if (strcmp(txt, LV_SYMBOL_OK) == 0)
    {
        strcpy(__buf, lv_textarea_get_text(ext->ta));
        if (this->_callback != nullptr)
        {
            this->_callback(KB_EVENT_OK);
        }
        return;
    } else if (strcmp(txt, "Exit") == 0)
    {
        if (this->_callback != nullptr)
        {
            this->_callback(KB_EVENT_EXIT);
        }
        return;
    } else if (strcmp(txt, LV_SYMBOL_RIGHT) == 0)
    {
        index = index + 1 >= sizeof(btnm_mapplus) / sizeof(btnm_mapplus[0]) ? 0 : index + 1;
        lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_TEXT_LOWER, btnm_mapplus[index]);
        return;
    } else if (strcmp(txt, LV_SYMBOL_LEFT) == 0)
    {
        index = index - 1 >= 0 ? index - 1 : sizeof(btnm_mapplus) / sizeof(btnm_mapplus[0]) - 1;
        lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_TEXT_LOWER, btnm_mapplus[index]);
        return;
    } else if (strcmp(txt, "Del") == 0)
    {
        lv_textarea_del_char(ext->ta);
    } else
    {
        lv_textarea_add_text(ext->ta, txt);
    }
}

void Keyboard::setKeyboardEvent(kb_event_cb callback)
{
    _callback = callback;
}

const char* Keyboard::getText()
{
    return (const char *)__buf;
}
