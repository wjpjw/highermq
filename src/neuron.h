#pragma once

#include "internal.h"

namespace hmq{

class neuron{
public:

private:
    // axon & dendrites are components of a neuron; 
    // they can't be owned by other objects
    std::unique_ptr<axon> axon_;
    tbb::concurrent_vector<std::unique_ptr<dendrite>> dendrites_;
    
    // options for dendrites
    uint32_t send_timeout;
    uint32_t recv_timeout;
    uint32_t 
};

}