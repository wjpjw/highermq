#include "error.h"
#include <stdlib.h>

//Calling this function implies unacceptable flaws in program design. For example, failure of pthread_join() would trigger qpanic as it implies there exists deadlocks.   
void hmq::panic_if(bool fatal_error, const std::string& err_msg){
    if(unlikely(fatal_error)){
       abort();
    }
}

void hmq::panic(const std::string& err_msg){
    abort();
}

