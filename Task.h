


#ifndef __TASK_H
#define __TASK_H

#include "config.h"



/*****************************************************************
 *
 *          ! Task Class
 *
 */
class Task
{
public:
    Task();
    ~Task();

    void create(lv_task_cb_t cb, uint32_t period = 1000, lv_task_prio_t prio = LV_TASK_PRIO_LOW);

private:
    lv_task_t *_handler = nullptr;
    lv_task_cb_t _cb = nullptr;
};

#endif
