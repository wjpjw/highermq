#pragma once

#include "internal.h"

namespace hmq{

using eventcb=std::function<void(uint32_t)>;

class event{
public:
    event(int fd, eventcb cb) : fd(fd), cb(cb){}
    virtual ~event();
    void    run_cb(uint32_t flag);
    void    append_flag(uint32_t event_flag);
private:
    int fd;
    eventcb cb;
    uint32_t active_event_types;
};

}