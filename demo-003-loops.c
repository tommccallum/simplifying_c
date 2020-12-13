#include "simplify_c.h"

start_program
{
    // loop a given number of times
    repeat(10) 
    {
        call print_integer(index);
    }
    
    // an until loop that takes an expression
    until(index < 10) 
    {
        call print_integer(index);
    }

    exit_program;
}