#pragma once
#include "internal.h"
#include "tbb/atomic.h"

namespace hmq{
// atomic counter unique id generator
struct uidgen{
    tbb::atomic<uint64_t> counter=1;
    uint64_t next() {
        return counter.fetch_and_add(1);
    }
    void reset(){
        counter=1; // starts from 1;
    }
};

}