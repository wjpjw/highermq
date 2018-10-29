#pragma once

#include "internal.h"

namespace hmq{

// duration in milliseconds
// max duration: 4+ million seconds, 1193 hours
using duration=uint32_t;

// max long_duration: 5124095576030 hours, 5849424 centries
// enough to 
using long_duration=uint64_t;


}