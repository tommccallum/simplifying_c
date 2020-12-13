#define enable_defer_debugging 
#include "simplify_c.h"

struct Point {
    int x;
    int y;
};

// we need function overloading still to handle the situation where we have
// a function that can take either a pointer or a value
returns nothing from function print_point(Point unmutable ptr this_point )
{
    print_integer(valueof(this_point).x);
    print_integer(valueof(this_point).y);
}

returns nothing from function print_point(Point unmutable this_point )
{
    print_integer(valueof(this_point).x);
    print_integer(valueof(this_point).y);
}

returns nothing from function test_defer_in_function() {
    auto p = new Point;
    defer(p);               // object is destroyed when goes out of scope
    valueof(p).x = 20;
    valueof(p).y = 25;
    print_point(p);
}

start_program
{
    // note that we can use our valueof function
    // to avoid having to do -> for pointers and . for local
    // variables
    {
        auto p = new Point;
        defer(p);               // object is destroyed when goes out of scope
        valueof(p).x = 10;
        valueof(p).y = 15;
        call print_point(p);
    }

    auto local_p = Point {};
    valueof(local_p).x = 10;
    valueof(local_p).y = 15;
    call print_point(local_p);

    call  test_defer_in_function();

    exit_program;
}