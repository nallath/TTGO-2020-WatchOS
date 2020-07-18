
#ifndef __PRELOAD_H
#define __PRELOAD_H
#include "config.h"


class Preload
{
public:
    Preload();
    ~Preload();
    void create(lv_obj_t *parent = nullptr);
    void align(const lv_obj_t *base, lv_align_t align, lv_coord_t x = 0, lv_coord_t y = 0);
    void hidden(bool en = true);

private:
    lv_obj_t *_preloadCont = nullptr;
};

#endif
