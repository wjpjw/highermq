#pragma once

#include "internal.h"
#include "event.h"
#include "tbb/concurrent_unordered_map.h"
#include "uidgen.h"

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
    uint64_t create_event(int, eventcb);
    std::shared_ptr<event> get_event(int);
private:
    tbb::concurrent_unordered_map<uint64_t, std::shared_ptr<event>> map_;
};

}