#include "Preload.h"

void Preload::create(lv_obj_t *parent)
{
    if (parent == nullptr)
    {
        parent = lv_scr_act();
    }
    if (_content == nullptr)
    {
        static lv_style_t plStyle;
        lv_style_init(&plStyle);
        lv_style_set_radius(&plStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_bg_color(&plStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
        lv_style_set_bg_opa(&plStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
        lv_style_set_border_width(&plStyle, LV_OBJ_PART_MAIN, 0);
        lv_style_set_text_color(&plStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
        lv_style_set_image_recolor(&plStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

        static lv_style_t style;
        lv_style_init(&style);
        lv_style_set_radius(&style, LV_OBJ_PART_MAIN, 0);
        lv_style_set_bg_color(&style, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
        lv_style_set_bg_opa(&style, LV_OBJ_PART_MAIN, LV_OPA_0);
        lv_style_set_border_width(&style, LV_OBJ_PART_MAIN, 0);
        lv_style_set_text_color(&style, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
        lv_style_set_image_recolor(&style, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);

        _content = lv_cont_create(parent, NULL);
        lv_obj_set_size(_content, LV_HOR_RES, LV_VER_RES - 30);
        lv_obj_align(_content, NULL, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_obj_add_style(_content, LV_OBJ_PART_MAIN, &plStyle);

        lv_obj_t *preload = lv_spinner_create(_content, NULL);
        lv_obj_set_size(preload, lv_obj_get_width(_content) / 2, lv_obj_get_height(_content) / 2);
        lv_obj_add_style(preload, LV_OBJ_PART_MAIN, &style);
        lv_obj_align(preload, _content, LV_ALIGN_CENTER, 0, 0);
    }
}
