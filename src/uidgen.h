#pragma once

namespace hmq{
//unique id generator
struct uidgen{
    tbb::atomic<uint64_t> counter=0;
    uint64_t next() {
        return counter.fetch_and_add(1);
    }
    void reset(){
        counter=0;
    }
};

}