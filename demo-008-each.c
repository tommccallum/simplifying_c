#include "simplify_c.h"
#include <vector>

struct Point {
    int x;
    int y;
};

returns nothing from function print_point(Point unmutable this_point )
{
    call print_integer(valueof(this_point).x);
    call print_integer(valueof(this_point).y);
}

start_program
{
    
    // each instantiates two variables item and index that
    // point at the item VALUE and the index of the value within
    // the collection
    {
        auto items = std::vector<int> { 100,101,102 };
        each(items) 
        {
            call print_integer(item);
            call print_integer(index);
        }
    }

    {
        auto points = std::vector<Point> {{0,0}, {1,1}, {2,2}};
        each(points) 
        {
            call print_point(item);
            call print_integer(index);
        }
    }


    exit_program;
}