/**
    Copyright 2020 Tom McCallum

    Permission is hereby granted, free of charge, to any person obtaining a 
    copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation 
    the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the 
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included 
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/

#ifndef SIMPLIFY_C_HPP
#define SIMPLIFY_C_HPP

#include <cstdio>
#include <cstdlib>
#include <memory>

// generate a semi-random name based on __COUNTER__
// if __COUNTER__ is not supported you can use __LINE__.
#define internal_random_name3(name, line)    name##line
#define internal_random_name2(name,line)         internal_random_name3(name,line )   
#define internal_random_name(x)         internal_random_name2(x, __COUNTER__ )   

#ifdef enable_start_counter_from_one
#define START_INDEX 1
#else
#define START_INDEX 0
#endif

// the 3 types of static
#define internal static         // c and c++ make a function 'extern' by default
#define global_variable static              
#define local_and_permanent static 

#define any void
#define nothing void

#define ptr *
#define set_value_of_pointer *
#define get_value_of_pointer *
#define ref &
#define addressof std::addressof

// we introduce a way to get the value of an object whether its a pointer or not.
template<class U>
U& valueof(U& x) {
    return x;
}

template<class U>
U& valueof(U*x) {
    return *x;
}

// Here we have the functionality for 'defer' mechanism.
// We wrap the pointer in a class that is then given a 
// local variable name.  When the scope ends the destructor
// is called.
template<class U>
class Deferable
{
private:
    U * y;
#ifdef enable_defer_debugging
    char const * name_;
#endif
public:
    
#ifdef enable_defer_debugging
    Deferable(char const * name, U* x): name_(name), y(x) {
        printf("constructing deferable '%s'\n", name_);
#else
    Deferable(U* x): y(x) {
#endif
    }
    ~Deferable() {
#ifdef enable_defer_debugging
        printf("destroying deferred object '%s'\n", name_);
#endif
        delete y;
    }
};

// use the template function to allow us to avoid
// having to do <> everywhere in user code
template<class U>
#ifdef enable_defer_debugging
Deferable<U> create_deferable(char const * name, U* x) {
    return Deferable<U>(name, x);
#else
Deferable<U> create_deferable(U* x) {
    return Deferable<U>(x);
#endif
}

// generate a deferred oject for each item
#ifdef enable_defer_debugging
#   define defer_ext2(nm, x)    auto nm = create_deferable(#nm, x)
#else
#   define defer_ext2(nm, x)    auto nm = create_deferable(x)
#endif
#define defer_ext(nm, x)    defer_ext2(nm,x)
#define defer(x)            defer_ext(internal_random_name(DEFERRED_), x)

// make it clear a variable is _defined_ elsewhere.
// all functions are by default extern anyway so just required for
// referring to variables in other compilation units.
#define defined_elsewhere extern

// allow the user to explicitly state if variable is mutable or not
#define unmutable const         
#define mutable

#define start_program           int main(int argc, char* argv[], char* env[])

// need to use this weirdness as we cannot reorder the function
// definition component using macros
// e.g. returns nothing from function print_hello(nothing) 
//      returns integer from function add(integer a, integer b)
#define returns
#define function
#define from

// use this word to highlight that a function is being called
#define call

// a wrapper for accessing arguments passed to the program
#define get_argument(n)                   argv[n]

// wrappers to add easy printing function calls
#define print_string(x)                   printf("%s\n",x)
#define print_integer(x)                  printf("%d\n",x)
#define print_integer_(x)                  printf("%d\n",valueof(x))
#define print_decimal(x)                  printf("%f\n",x)
#define print_location_of(x)              printf("%#08x\n", addressof(x))
#define print_pointer(x)                  printf("%#08x\n", x)

// wrappers to show common exit conditions
#define crash_and_burn                    exit(1)
#define exit_program                      exit(0)

// This is not possible with multiple arguments
// #define CREATE_FUNCTION(name,args,ret)           ret name(args)

// types
#define positive_integer                    unsigned int 
#define signed_integer                      signed int
#define negative_integer                    signed int

#ifdef enable_start_counter_from_one
#   define repeat(x)                            for( int index=START_INDEX; index <= x; index++ )
#   define until(x)                           for( int index=START_INDEX; x; index++ )
#else
#   define repeat(x)                            for( int index=START_INDEX; index < x; index++ )
#   define until(x)                           for( int index=START_INDEX; x; index++ )
#endif

#define each(collection)  \
        unsigned int index =START_INDEX; \
        auto ptr_it=begin(collection); \
        auto item=*ptr_it; \
        for( ; ptr_it != end(collection); ptr_it++, index++, item=*ptr_it)
    



#endif /* SIMPLIFY_C_HPP */
