#include "Task.h"


Task::Task()
{
    _handler = nullptr;
    _cb = nullptr;
}
Task::~Task()
{
    if ( _handler == nullptr)
    {
        return;
    }
    Serial.println("Free Task Func");
    lv_task_del(_handler);
    _handler = nullptr;
    _cb = nullptr;
}

void Task::create(lv_task_cb_t cb, uint32_t period, lv_task_prio_t prio)
{
    _handler = lv_task_create(cb,  period,  prio, NULL);
};
