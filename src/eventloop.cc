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

eventloop::eventloop()
{
    while(!shutdown_){
        int n=epoller_.wait(); 
        for(int i=0; i<n; i++){             
            // @to_user: make sure run_cb returns in very short time
            auto ev=eventmap::inst().get_event(epoller_.eid(i));
            /*
                Event objects are stored and transferred in shared_ptrs, which gurantees that even if it is being removed in user threads, current ev still has its last reference here in eventloop and will automatically release after its last run_cb. 
                If get_event returns nullptr, eventloop will know it's already released and skip it. 
            */  
            if(ev!=nullptr) ev->run_cb(epoller_.eflag(i));
        }
    }
}


}