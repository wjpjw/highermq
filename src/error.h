#include "internal.h"

namespace hmq{

extern std::string error_str(str what, uint16_t level);

class error : public std::runtime_error
{
public:
    enum error_level : uint16_t{
        I=0, 
        II=1, 
        III=2
    };
    error(str what, error_level level=I) 
        : runtime_error(qerror_str(what, level)), error_level_(level){}
    error_level error_level_;    
};

//If is_error is very unlikely(less than say 5% chance) to be true, this function could potentially enhance branch prediction.
static inline void error_if(bool is_error, const std::string& err_msg){
    if(unlikely(is_error)) throw qerror(err_msg);
}

//Calling this function implies unacceptable flaws in program design. For example, failure of pthread_join() would trigger qpanic as it implies there exists deadlocks.   
extern void panic_if(bool fatal_error, const std::string& err_msg);

extern void panic(const std::string& err_msg);
}
