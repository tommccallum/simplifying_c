#define enable_start_counter_from_one
#include "simplify_c.h"



start_program
{
    // loop a given number of times
    // 1...10
    repeat(10) 
    {
        call print_integer(index);
    }
    
    // an until loop that takes an expression
    // 1...9
    until(index < 10) 
    {
        call print_integer(index);
    }

    exit_program;
}