
#ifndef __PRELOAD_H
#define __PRELOAD_H
#include "config.h"
#include "GUIObject.h"

class Preload: public GUIObject
{
public:
    void create(lv_obj_t *parent = nullptr);
private:
    lv_obj_t *_preloadCont = nullptr;
};

#endif
