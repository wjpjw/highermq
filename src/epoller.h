#pragma once

#include "internal.h"
#include <sys/epoll.h>

namespace hmq{

/*

The event argument describes the object linked to the file descriptor fd. The struct epoll_event is defined as :

typedef union epoll_data {
    void        *ptr;  
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;

struct epoll_event {
    uint32_t     events;     // Epoll events
    epoll_data_t data;       // User data variable
};

The events member is a bit set composed using the following available event types:
EPOLLIN
    The associated file is available for read(2) operations.
EPOLLOUT
    The associated file is available for write(2) operations.
EPOLLRDHUP (since Linux 2.6.17)
    Stream socket peer closed connection, or shut down writing half of connection. (This flag is especially useful for writing simple code to detect peer shutdown when using Edge Triggered monitoring.)
EPOLLPRI
    There is urgent data available for read(2) operations.
EPOLLERR
    Error condition happened on the associated file descriptor. epoll_wait(2) will always wait for this event; it is not necessary to set it in events.
EPOLLHUP
    Hang up happened on the associated file descriptor. epoll_wait(2) will always wait for this event; it is not necessary to set it in events.
EPOLLET
    Sets the Edge Triggered behavior for the associated file descriptor. The default behavior for epoll is Level Triggered. See epoll(7) for more detailed information about Edge and Level Triggered event distribution architectures.
EPOLLONESHOT (since Linux 2.6.2)
    Sets the one-shot behavior for the associated file descriptor. This means that after an event is pulled out with epoll_wait(2) the associated file descriptor is internally disabled and no other events will be reported by the epoll interface. The user must call epoll_ctl() with EPOLL_CTL_MOD to rearm the file descriptor with a new event mask.

*/

// @indenpendent
// @threadsafe
class epoller{
public:
    constexpr static int max_nr_epoll_events=1024; 
    constexpr static uint32_t mask=(EPOLLIN|EPOLLOUT|EPOLLERR);
    epoller();
    ~epoller();
    //void* ev_data is stored in event.data.ptr
    void                    add(int fd, uint64_t eventid);
    void                    mod(int fd, int events_new, uint64_t eventid);
    void                    mod(int fd, int events_old, int events_append, uint64_t eventid);
    void                    del(int fd);
    int                     wait();
    int                     fd() const noexcept {return epoll_fd_;}
    uint32_t                event_flag(int index)
    {
        return get_event(index).events&mask;
    }
    uint64_t                event_id(int index)
    {
        return get_event(index).data.u64;
    }
protected:
    struct epoll_event*     events(){return events_;}
    struct epoll_event&     get_event(int index);
private:
    int                     epoll_fd_;
    struct epoll_event      events_[max_nr_epoll_events];
};



}