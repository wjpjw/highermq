#include "eventloop.h"
#include "event.h"
#include "eventmap.h"

/*
    eventloop creates a epoll loop on its creation
    
    Epoll-based reactors are synchronised outside kernel boundry. 

    To handle events efficiently and boundedly, user code must 
    exploit as much parallelism as possible after each epoll_wait().
*/

namespace hmq{

eventloop::eventloop() : epoller()
{
    while(!shutdown_){
        int n=epoller_.wait(); 
        for(int i=0; i<n; i++){     
            // get another epoll_event      
            auto epoll_ev=get_event(i);
            // get its associated event object & run event callback
            auto ev=eventmap::inst().get_event(epoll_ev.data.fd);
            /*
                Event objects are stored and transferred in shared_ptrs, which gurantees that even if it is being removed in user threads, current ev still has its last reference here in eventloop and will automatically release after its last run_cb. 
                If get_event returns nullptr, eventloop will know it's already released and skip it. 
            */  
            if(ev!=nullptr) ev->run_cb(epoll_ev.events&mask);
        }
    }
}


}