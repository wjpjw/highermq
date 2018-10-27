#pragma once

#include "internal.h"
#include "event.h"
#include "tbb/concurrent_unordered_map.h"

namespace hmq{

class eventmap{
protected:
    eventmap(){}
public:
    // single global instance
    static eventmap&       inst() 
    {
        static eventmap instance_;
        return instance_;
    }
    std::shared_ptr<event> create_event(int fd, eventcb cb);
    std::shared_ptr<event> get_event(uint64_t id);

private:
    uidgen gen_;
    tbb::concurrent_unordered_map<uint64_t, std::shared_ptr<event>> map_;

};

}