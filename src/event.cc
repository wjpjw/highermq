#include "epoller.h"
#include "event.h"

namespace hmq{

void    event::run_cb(uint32_t flag){
    active_event_types &= ~(flag&(EPOLLIN | EPOLLOUT | EPOLLERR));
    cb(flag); 
    // flag is unfiltered, therefore user-defined callbacks, 
    // rather than merely check POLLIN or POLLOUT, 
    // should also check POLLHUP, POLLERR, POLLNVAL (& EPOLLPRI if used)
}


}