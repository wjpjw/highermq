#include "eventmap.h"

namespace hmq{

// file descriptors are naturally unique ids of events
uint64_t eventmap::create_event(int fd, eventcb cb)
{
    map_[id]=std::make_shared<event>(fd, cb);
    return id;
}

std::shared_ptr<event> eventmap::get_event(int fd)
{
    try{
        auto duh=map_.at(fd);
        return duh;
    }catch(...){
        return nullptr;
    }
}


}