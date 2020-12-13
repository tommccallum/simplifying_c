#include "simplify_c.h"

start_program
{
    // local stack object
    negative_integer a = -100;
    call print_location_of(a);

    // heap object
    auto x = new int;
    set_value_of_pointer x = 5;
    call print_location_of(x);
    call print_pointer(x);
    call print_integer(get_value_of_pointer x);

    exit_program;
}