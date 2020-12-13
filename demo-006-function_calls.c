#include "simplify_c.h"

// change mutable to unmutable and back again to 
// create error
returns nothing from function add_one(int mutable ptr x ) 
{
    set_value_of_pointer x = valueof(x) + 1;
    call print_integer(valueof(x));
}

returns nothing from function try_and_add_one(int x ) 
{
    x = valueof(x) + 1;
    call print_integer(valueof(x));
}

start_program
{
    // heap object
    auto x = new int;
    set_value_of_pointer x = 5;
    call print_location_of(x);
    call print_pointer(x);

    call print_string("call by pointer");
    call print_integer(get_value_of_pointer x);
    call add_one(x);
    // what value does this have when we return
    call print_integer(get_value_of_pointer x);

    call print_string("call by value");
    call print_integer(get_value_of_pointer x);
    call try_and_add_one(get_value_of_pointer x);
    call print_integer(get_value_of_pointer x);

    exit_program;
}