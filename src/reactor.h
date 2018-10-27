#include "internal.h"
#include "epoller.h"

namespace hmq{

class reactor{
public:
    // single global instance
    static reactor&       inst() 
    {
        static reactor instance_;
        return instance_;
    }
    void close()
    {
        shutdown_=true;
    } 
private:
    reactor();
    bool shutdown_=false;
    epoller epoller_;
};

}