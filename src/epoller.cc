#include "epoller.h"
#include <fcntl.h>          // fcntl, posix_fadvise
#include <sys/stat.h>       // stat, S_ISREG
#include <unistd.h>         // read, open, write, close, lseek, pread
#include "error.h"
/*

configurations of hmq's epoll

1. LT mode:
    see 
    https://stackoverflow.com/questions/12892286/epoll-with-edge-triggered-event/12897334


2. one-shot mode:
    play safe in very concurrent environment

3. 1024 max events:
    a lower(but not crazily low) max_events value seems reasonable 

4. nonblocking & cloexec fds:
    set every socket nonblocking upon CTL_ADD

5. use epoll_event.data.fd to get event object 
    no user defined data field, no implicit coupling      

6. IN, OUT and ERR:
    monitor these three types of events

*/

namespace hmq{

epoller::epoller(){
    epoll_fd_=epoll_create1(EPOLL_CLOEXEC);
    error_if(epoll_fd_<0, "Fail to epoll_create1()");
}

epoller::~epoller()
{
    close(epoll_fd_);
}

void                    epoller::add(int fd){
    fcntl(fd, F_SETFD, FD_CLOEXEC);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    struct epoll_event ee;
    ee.events=0;
    error_if ((epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ee)) != 0, "Fail to add epoll event");
}

void                    epoller::mod(int fd, int events_new)
{
    struct epoll_event ee;
    ee.events   = events_new | EPOLLONESHOT | EPOLLERR;
    error_if(epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ee) != 0, "Fail to mod epoll event"); 
}

void                    epoller::del(int fd){
    struct epoll_event ee; //unused
    error_if(epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &ee)!=0, "Fail to del epoll event");
}

int                     epoller::wait()
{
    int n = epoll_wait(epoll_fd_, events_, max_nr_epoll_events, -1);
    error_if(n<0, "epoll_wait failed");
    return n; 
}

struct epoll_event&     epoller::get_event(int index){
    if(index>max_nr_epoll_events-1) throw error("index out of bound");
    return events_[index];
}

    
}