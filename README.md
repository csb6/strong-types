# Strong-Types

This is an extremely simple, single-header implementation of strong typedefs in C++.
While several good strong typedef libraries for C++ exist, most of them
are complex, making use of a large amount of template metaprogramming to allow levels
of customization that are not necessary for many cases.

This library attempts to offer the core functionality of strong typedefs (creating
typedef-like types that rename an existing type but are treated as distinct types
by the compiler) with as little boilerplate as possible. Here is some sample code
demonstrating the some of the basic features:

```cpp
#include <iostream>
#include "strong-types.hpp"

struct Width { unsigned int v; }
struct Height { unsigned int v; }

int main()
{
    Width w{4};
    Height h{5};
    h = w; // Compile-time error
    h += 5;
    w *= 9;
    Height h2{6};
    h = h + h2; // Works
    std::cout << h << std::endl; // Works as expected
    std::cout << w << std::endl;

    return 0;
}
```

## Features

- Simple creation of typedefs; simply create a struct with a single member that
is named 'v'
- Templated operator overloads, including most arithmetic, comparison, and increment/
decrementing operators, as well as an output stream operator. Adding your own operators
is trivial
- Operator overloads use SFINAE to check that the types they are used on only have a
single member, named v, preventing most ambiguous template resolutions
- To access members/member functions of the underlying type, simply access the
'v' member.

[This blog post](https://www.fluentcpp.com/2018/04/06/strong-types-by-struct) by Vincent
Zalzal was the inspiration for this simple method of creating strong typedefs.