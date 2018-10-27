#include "eventmap.h"

namespace hmq{

std::shared_ptr<event> eventmap::create_event(int fd, eventcb cb)
{
    map_.push(gen_.next(), std::make_shared<event>(fd, cb));
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