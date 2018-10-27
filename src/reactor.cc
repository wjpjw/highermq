#include "reactor.h"
#include "event.h"

namespace hmq{

reactor::reactor()
{
    while(!shutdown_){
        int n=epoller_.wait(); 
        for(int i=0; i<n; i++){
            uint32_t flag = epoller_.event_flag(i);
            uint64_t eventid = epoller_.event_id(i);
            // get event & execute
        }
    }
}


}