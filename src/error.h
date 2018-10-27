#include "internal.h"

namespace hmq{


class error : public std::runtime_error
{
public:
    
    error(const std::string& what) : runtime_error(what){}
};

//If is_error is very unlikely(less than say 5% chance) to be true, this function could potentially enhance branch prediction.
static inline void error_if(bool is_error, const std::string& err_msg){
    if(unlikely(is_error)) throw error(err_msg);
}

//Calling this function implies unacceptable flaws in program design. For example, failure of pthread_join() would trigger qpanic as it implies there exists deadlocks.   
extern void panic_if(bool fatal_error, const std::string& err_msg);

extern void panic(const std::string& err_msg);
}
