#include "Preload.h"

Preload::Preload()
{
    _preloadCont = nullptr;
}
Preload::~Preload()
{
    if (_preloadCont == nullptr)
    {
        return;
    }
    lv_obj_del(_preloadCont);
    _preloadCont = nullptr;
}
void Preload::create(lv_obj_t *parent)
{
    if (parent == nullptr)
    {
        parent = lv_scr_act();
    }
    if (_preloadCont == nullptr)
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

        _preloadCont = lv_cont_create(parent, NULL);
        lv_obj_set_size(_preloadCont, LV_HOR_RES, LV_VER_RES - 30);
        lv_obj_align(_preloadCont, NULL, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_obj_add_style(_preloadCont, LV_OBJ_PART_MAIN, &plStyle);

        lv_obj_t *preload = lv_spinner_create(_preloadCont, NULL);
        lv_obj_set_size(preload, lv_obj_get_width(_preloadCont) / 2, lv_obj_get_height(_preloadCont) / 2);
        lv_obj_add_style(preload, LV_OBJ_PART_MAIN, &style);
        lv_obj_align(preload, _preloadCont, LV_ALIGN_CENTER, 0, 0);
    }
}


void Preload::align(const lv_obj_t *base, lv_align_t align, lv_coord_t x, lv_coord_t y)
{
    lv_obj_align(_preloadCont, base, align, x, y);
}

void Preload::hidden(bool en)
{
    lv_obj_set_hidden(_preloadCont, en);
}
