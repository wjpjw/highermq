#include "internal.h"
#include "epoller.h"

namespace hmq{

class eventloop : public epoller{
public:
    // single global instance
    static eventloop&       inst() 
    {
        static eventloop instance_;
        return instance_;
    }
    void close()
    {
        shutdown_=true;
    } 
private:
    eventloop();
    bool shutdown_=false;
};

}