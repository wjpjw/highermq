#include "hmq.h"
#include "tbb/tbb.h"

namespace hmq{

void init()
{
    tbb::task_scheduler_init init(tbb::task_scheduler_init::default_num_threads());

}

}