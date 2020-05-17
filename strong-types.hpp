#ifndef STRONG_TYPES_LIB_H
#define STRONG_TYPES_LIB_H
#include <type_traits>
#include <ostream>
/**
File: strong_types.hpp
Author: Cole Blakley

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
- The operators defined in this file will only work on structs/classes that
  have one member, which is named 'v'. This is to prevent the operators from
  accidentally applying to types that happen to have a member named 'v'.

Here is an example of usage:

// Define some strong typedefs; always use 'v' as the member name, and
// always make 'v' a public member. In order to use an operator with the
// typedef, 'v''s type must already have that operator defined for it.
struct Meter { int v; }
struct Yard { int v; }
struct ForwardDistance { unsigned int v; }
struct Pointless { std::vector<int> v; } // Compiles, but can't use any of
                                         // the member functions of 'v'
struct Pair { bool v; int w; }

// Always use uniform initialization
Meter length1{6};
Meter length2{7};
Yard length3{8};
Yard length4{9};
Yard length5 = {5}; // This works, too
Yard length6 = 5; // Fails to compile
Pair p{3, 3};

length1 + length2;      // Compiles, works as expected
length2 = length1 + 5; // Compiles, works as expected
length1 = length3;    // Fails to compile; types differ
pair + pair;          // Fails to compile; the strong-types operators only work
                      // on structs of form: struct X { T v; };, which Pair is not

FowardDistance f{67};
f += 4; // Works as expected; f.v is now 71
std::cout << f; // Prints 71
*/

/*Poor man's concepts (until C++20 is supported)
  Basically, these enable_ifs ensure that the operators defined below
  only work with types of the following form: struct Foo { T v; }. This prevents
  most ambiguous template resolutions, as well as unintended uses of the below operators
  on structs that happen to have a member named 'v'. The operators will only be
  enabled when used with a type with only one member: `v`.
*/
// Only return T if T is a struct where v is the only member
#define T_IF_T_ST typename std::enable_if_t<(sizeof(T::v) == sizeof(T)), T>
// Only return T if the type of T2 is the same as the type of T.v in a struct
// where v is the only member
#define T_IF_T2_EQ_V typename std::enable_if_t<sizeof(T::v) == sizeof(T) \
                                               && std::is_same_v<decltype(T::v), T2>, T>
// Only return bool if the type of T2 is the same as the type of T.v in a struct
// where v is the only member
#define BOOL_IF_T2_EQ_V typename std::enable_if_t<sizeof(T::v) == sizeof(T) \
                                                  && std::is_same_v<decltype(T::v), T2>, bool>
// Only return bool if T is a struct where v is the only member
#define BOOL_IF_T_ST \
    typename std::enable_if_t<(sizeof(T::v) == sizeof(T)), bool>
// Only return std::ostream if T is a struct where v is the only member
#define OSTREAM_IF_T_ST \
    typename std::enable_if_t<(sizeof(T::v) == sizeof(T)), std::ostream>

// For std::cout and friends
template<typename T>
OSTREAM_IF_T_ST& operator<<(std::ostream &out, T a)
{
    out << a.v;
    return out;
}

// Arithmetic operators
template<typename T>
T_IF_T_ST operator+(T a, T b) { return {a.v + b.v}; }

template<typename T, typename T2>
T_IF_T2_EQ_V operator+(T a, T2 &&b) { return {a.v + b}; }

template<typename T>
T_IF_T_ST operator-(T a, T b) { return {a.v - b.v}; }

template<typename T, typename T2>
T_IF_T2_EQ_V operator-(T a, T2 &&b) { return {a.v - b}; }

template<typename T>
T_IF_T_ST operator*(T a, T b) { return {a.v * b.v}; }

template<typename T, typename T2>
T_IF_T2_EQ_V operator*(T a, T2 &&b) { return {a.v * b}; }

template<typename T>
T_IF_T_ST operator/(T a, T b) { return {a.v / b.v}; }

template<typename T, typename T2>
T_IF_T2_EQ_V operator/(T a, T2 &&b) { return {a.v / b}; }

template<typename T>
T_IF_T_ST operator%(T a, T b) { return {a.v % b.v}; }

template<typename T, typename T2>
T_IF_T2_EQ_V operator%(T a, T2 &&b) { return {a.v % b}; }


// Shortcut arithmetic operators
template<typename T>
T_IF_T_ST& operator+=(T &a, T b) { a.v += b.v; return a; }

template<typename T, typename T2>
T_IF_T2_EQ_V& operator+=(T &a, T2 &&b) { a.v += b; return a; }

template<typename T>
T_IF_T_ST& operator-=(T &a, T b) { a.v -= b.v; return a; }

template<typename T, typename T2>
T_IF_T2_EQ_V& operator-=(T &a, T2 &&b){ a.v -= b; return a; }

template<typename T>
T_IF_T_ST& operator*=(T &a, T b) { a *= b; return a; }

template<typename T, typename T2>
T_IF_T2_EQ_V& operator*=(T &a, T2 &&b) { a.v *= b; return a; }

template<typename T>
T_IF_T_ST& operator/=(T &a, T b) { a /= b; return a; }

template<typename T, typename T2>
T_IF_T2_EQ_V& operator/=(T &a, T2 &&b) { a.v /= b; return a; }

template<typename T>
T_IF_T_ST& operator%=(T &a, T b) { a %= b; return a; }

template<typename T, typename T2>
T_IF_T2_EQ_V& operator%=(T &a, T2 &&b) { a.v %= b; return a; }

template<typename T>
T_IF_T_ST& operator++(T &a) { ++a.v; return a; }

template<typename T>
T_IF_T_ST operator++(T &a, int) { return T{a.v++}; }

template<typename T>
T_IF_T_ST& operator--(T &a) { --a.v; return a; }

template<typename T>
T_IF_T_ST operator--(T &a, int) { return T{a.v--}; }


// Comparison operators
template<typename T>
BOOL_IF_T_ST operator==(T a, T b) { return a.v == b.v; }

template<typename T, typename T2>
BOOL_IF_T2_EQ_V operator==(T a, T2 &&b) { return a.v == b; }

template<typename T>
BOOL_IF_T_ST operator!=(T a, T b) { return a.v != b.v; }

template<typename T, typename T2>
BOOL_IF_T2_EQ_V operator!=(T a, T2 &&b) { return a.v != b; }

template<typename T>
BOOL_IF_T_ST operator<(T a, T b) { return a.v < b.v; }

template<typename T, typename T2>
BOOL_IF_T2_EQ_V operator<(T a, T2 &&b) { return a.v < b; }

template<typename T>
BOOL_IF_T_ST operator>(T a, T b) { return a.v > b.v; }

template<typename T, typename T2>
BOOL_IF_T2_EQ_V operator>(T a, T2 &&b) { return a.v > b; }

template<typename T>
BOOL_IF_T_ST operator<=(T a, T b) { return a.v <= b.v; }

template<typename T, typename T2>
BOOL_IF_T2_EQ_V operator<=(T a, T2 &&b) { return a.v <= b; }

template<typename T>
BOOL_IF_T_ST operator>=(T a, T b) { return a.v >= b.v; }

template<typename T, typename T2>
BOOL_IF_T2_EQ_V operator>=(T a, T2 &&b) { return a.v >= b; }

#undef T_IF_T_ST
#undef T_IF_T2_EQ_V
#undef BOOL_IF_T2_EQ_V
#undef BOOL_IF_T_ST
#undef OSTREAM_IF_T_ST
#endif
