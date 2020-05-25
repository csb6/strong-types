#ifndef STRONG_TYPES_LIB_H
#define STRONG_TYPES_LIB_H
#include <ostream>
/**
File: strong_types.hpp
Author: Cole Blakley

Special thanks to Sean Middleditch for helping to redesign the implementation
to be simpler/quicker to compile.

This is a single-header library. It adds an extremely simple implementation
of "strong typedefs" to C++. Strong typedefs allow you to make a named type
(ex: Width) that has the same underlying type as some existing type (ex: int),
but is treated as a different type by the compiler. This helps code express
semantically different quantities, such as Meters vs. Yards, in the type system,
preventing errors at compile time. Most comparison/arithmetic operators are
allowed with these new strong typedefs. Implicit conversions during operations
are not allowed.

See the definitions below this comment to see the full range of operators
available.

NOTE:
- Only arithmetic, comparison, and increment operators are supported.
- The strong typedef can't mimic the member functions or fields of the
  underlying type. To access fields/member functions, use the 'v' member of
  the struct directly.

Here is an example of usage:

struct Meter : strong_type<int, Meter> {};
struct Yard : strong_type<int, Yard> {};
struct ForwardDistance : strong_type<unsigned int, ForwardDistance> {};
// Compiles, but can't use any of the vector's member functions directly
struct Pointless : strong_type<std::vector<int>, Pointless> {};
struct Pair { bool v; int w; }

// Always use uniform initialization
Meter length1{6};
Meter length2{7};
Yard length3{8};
Yard length4{9};
Yard length5 = {5}; // This works, too
Yard length6 = 5; // Fails to compile

length1 + length2;      // Compiles, works as expected
length2 = length1 + 5; // Compiles, works as expected
length1 = length3;    // Fails to compile; types differ

FowardDistance f{67};
f += 4; // Works as expected; f.v is now 71
std::cout << f; // Prints 71
*/

template<typename Type, typename Tag>
struct strong_type {
    Type v;

    constexpr strong_type(Type value) : v(value) {}
    constexpr strong_type() = default;

    friend std::ostream& operator<<(std::ostream& out, strong_type a)
    {
        return (out << a.v);
    }

// Arithmetic operators
    friend strong_type operator+(strong_type a, strong_type b) { return {a.v + b.v}; }
    friend strong_type operator+(strong_type a, Type &&b) { return {a.v + b}; }
    friend strong_type operator-(strong_type a, strong_type b) { return {a.v - b.v}; }
    friend strong_type operator-(strong_type a, Type &&b) { return {a.v - b}; }

    friend strong_type operator*(strong_type a, strong_type b) { return {a.v * b.v}; }
    friend strong_type operator*(strong_type a, Type &&b) { return {a.v * b}; }
    friend strong_type operator/(strong_type a, strong_type b) { return {a.v / b.v}; }
    friend strong_type operator/(strong_type a, Type &&b) { return {a.v / b}; }
    friend strong_type operator%(strong_type a, strong_type b) { return {a.v % b.v}; }
    friend strong_type operator%(strong_type a, Type &&b) { return {a.v % b}; }
// Shortcut arithmetic operators
    friend strong_type& operator+=(strong_type &a, strong_type b) { a.v += b.v; return a; }
    friend strong_type& operator+=(strong_type &a, Type &&b) { a.v += b; return a; }
    friend strong_type& operator-=(strong_type &a, strong_type b) { a.v -= b.v; return a; }
    friend strong_type& operator-=(strong_type &a, Type &&b){ a.v -= b; return a; }
    friend strong_type& operator*=(strong_type &a, strong_type b) { a *= b; return a; }
    friend strong_type& operator*=(strong_type &a, Type &&b) { a.v *= b; return a; }
    friend strong_type& operator/=(strong_type &a, strong_type b) { a /= b; return a; }
    friend strong_type& operator/=(strong_type &a, Type &&b) { a.v /= b; return a; }
    friend strong_type& operator%=(strong_type &a, strong_type b) { a %= b; return a; }
    friend strong_type& operator%=(strong_type &a, Type &&b) { a.v %= b; return a; }
    friend strong_type& operator++(strong_type &a) { ++a.v; return a; }
    friend strong_type operator++(strong_type &a, int) { return strong_type{a.v++}; }
    friend strong_type& operator--(strong_type &a) { --a.v; return a; }
    friend strong_type operator--(strong_type &a, int) { return strong_type{a.v--}; }

// Comparison operators
    friend bool operator==(strong_type a, strong_type b) { return a.v == b.v; }
    friend bool operator==(strong_type a, Type &&b) { return a.v == b; }
    friend bool operator!=(strong_type a, strong_type b) { return a.v != b.v; }
    friend bool operator!=(strong_type a, Type &&b) { return a.v != b; }
    friend bool operator<(strong_type a, strong_type b) { return a.v < b.v; }
    friend bool operator<(strong_type a, Type &&b) { return a.v < b; }
    friend bool operator>(strong_type a, strong_type b) { return a.v > b.v; }
    friend bool operator>(strong_type a, Type &&b) { return a.v > b; }
    friend bool operator<=(strong_type a, strong_type b) { return a.v <= b.v; }
    friend bool operator<=(strong_type a, Type &&b) { return a.v <= b; }
    friend bool operator>=(strong_type a, strong_type b) { return a.v >= b.v; }
    friend bool operator>=(strong_type a, Type &&b) { return a.v >= b; }
};
#endif
