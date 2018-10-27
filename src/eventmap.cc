#include "eventmap.h"

namespace hmq{

uint64_t eventmap::create_event(int fd, eventcb cb)
{
    uint64_t id=gen_.next();
    map_[id]=std::make_shared<event>(fd, cb);
    return id;
}

std::shared_ptr<event> eventmap::get_event(uint64_t id)
{
    try{
        auto duh=map_.at(id);
        return duh;
    }catch(...){
        return nullptr;
    }
}


}