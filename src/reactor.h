
namespace hmq{

class epoller;

class event;


class reactor{
    constexpr static uint32_t mask=EPOLLIN|EPOLLOUT|EPOLLERR;
public:
    reactor()
    {
        while(!shutdown_){
            int n=epoller_.wait(); 
            for(int i=0; i<n; i++){
                auto epoll_event_ptr=epoller_.events()+i;
                uint32_t flag = epoll_event_ptr->events|mask;
                
            }
        }
    }
    void close()
    {
        shutdown_=true;
    } 
private:
    bool shutdown_=false;
    epoller epoller_;
};

}