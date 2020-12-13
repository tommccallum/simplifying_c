#include "simplify_c.h"

returns positive_integer from function fibonacci(positive_integer x)
{
    if ( x < 3 ) return x;
    return call fibonacci(x-1) + call fibonacci(x-2);
}


start_program
{
    call print_integer(call fibonacci(10));
    
    exit_program;
}