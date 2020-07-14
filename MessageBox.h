
#ifndef __MESSAGE_BOX_H
#define __MESSAGE_BOX_H

#include "config.h"

class MessageBox
{
public:
    MessageBox();
    ~MessageBox();

    void create(const char *text, lv_event_cb_t event_cb, const char **btns = nullptr, lv_obj_t *par = nullptr);

    void setData(void *data);

    void* getData();
    void setBtn(const char **btns);

private:
    lv_obj_t* _messageBox = nullptr;
};

#endif __MESSAGE_BOX_H
