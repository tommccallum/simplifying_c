#include "simplify_c.h"

// need to use this weirdness as we cannot reorder the function
// definition component using macros
returns nothing from function print_hello(nothing) 
{
    print_string("hello world!");
}

start_program
{
    call print_hello();
    call print_integer(10);
    call print_decimal(3.2);
    auto value = get_argument(0);
    call print_string(value);

    exit_program;
}