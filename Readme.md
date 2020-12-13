# Simplify C

An experiment is using macros and templates to play about with programming language readability.

## Why?

* To demonstrate how using different terminology can make language more approachable.
* As an education tool in developing new languages without implementing a parser etc.
* For fun and curiosity to see how much we can manipulate about the syntax.

## Why not?

* As these language experiments are just macros there is no compiler checks for them
and you get errors based on the preprocessed code.
* The semantics of the language don't change.
* It's fun but not a serious attempt a writing a language.

## Constraints and Limitations

* Using preprocessor macros we cannot reorder constructs.
* Sometime we need additional scoping brackets to ensure that predefined variables do not clash.

## Compile and Test instructions

```
git clone https://github.com/tommccallum/simplifying_c
./build.sh test
```

## Demo

```
#include "simplify_c.h"

returns nothing from function print_hello(nothing) 
{
    print_string("hello world\n");
}

start_program
{
    call print_hello();
    exit_program;
}
```

## Other constructs

Here are some of the constructs implemented:

### defer
Use of a ```defer``` construct implemented as mix of macros and template metaprogramming.  
This allows you to create an object on the heap and then ensure it gets removed when it exits scope.

```
{
    auto m = new Point;
    defer(m);
}
```

### valueof
Use of a ```valueof``` function so you don't need to use ```->``` instead of ```.```.  
This is implemented as a function template.

```
auto m = new Point;
auto p = Point;
m.x = valueof(p).x;
valueof(m).x = valueof(p).x;
```

### each

Looping through a collection using the ```each``` keyword generates a preset variable ```item``` pointing to the current item and index that is the value of the item.  Note the scoping bracket before and after as we need to hide the declared variables from other each constructs within the same outer scope.  These are not required if there is only one ```each``` construct in the function.

```
{
    each(points) {
        call print_point(item);
        call print_integer(index);
    }
}
```

### until

Loop until some expression is true.  This is the same as a while loop but we have a predefined variable index that indexes the current loop.  The expression can be any valid C/C++ expression at time of call.

```
until(index < 10) 
{
    call print_integer(index);
}
```

### repeat

Loop from ```start_index``` to 10, where start_index is 0 or 1 depending on the flag to the library.  Again, a variable called index gives the value of the current loop.

```
repeat(10) 
{
    call print_integer(index);
}
```

# Library flags

Before including the header file you can set the following flags:

```
enable_start_counter_from_one       // start loop, until loop counters at 1 rather than 0
enable_defer_debugging              // print out construction and destruction of deferred objects
```


