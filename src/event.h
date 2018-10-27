#pragma once

#include "internal.h"

namespace hmq{

using eventcb=std::function<void(uint32_t)>;

class event{
public:
    event(uint64_t id, eventcb cb) : id(id), cb(cb)
    {}
private:
    uint64_t id;
    eventcb cb;
    uint32_t event_flag;
};


}