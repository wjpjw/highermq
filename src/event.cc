#include "eventloop.h"
#include "event.h"

namespace hmq{

// cb's parameter flag is unfiltered, 
// therefore user-defined callbacks, 
// rather than merely check POLLIN or POLLOUT, 
// should also check POLLHUP, POLLERR, POLLNVAL (& EPOLLPRI if used)
void event::run_cb(uint32_t flag){
    active_event_types &= ~(flag&epoller::mask);
    cb(flag); 
}

event::~event()
{
    shutdown(fd, SHUT_RDWR);
    eventloop::inst().del(fd); 
    close(fd);
}

// 
void event::append_flag(uint32_t event_flag)
{
    active_event_types|=event_flag;
    eventloop::inst().mod(fd, active_event_types, fd);
}

}