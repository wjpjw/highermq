#pragma once

#include "internal.h"

namespace hmq{

using eventcb=std::function<void(uint32_t)>;

class event{
public:
    event(uint64_t id, eventcb cb) : id(id), cb(cb){}
    void    run_cb(uint32_t flag);
private:
    uint64_t id;
    eventcb cb;
    uint32_t active_event_types;
};


}