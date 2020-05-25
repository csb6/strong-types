#include "strong-types.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct NaturalInt : strong_type<unsigned int, NaturalInt> {};

struct Name : public strong_type<std::string, Name> {};

int main()
{
    // Use unsigned numbers safely
    NaturalInt a{5};
    std::vector<NaturalInt> numbers = {{1}, {56}, {90}, {56}, {2}, {78}, {5}};
    for(auto each : numbers) {
        std::cout << each << ' ';
    }
    std::cout << '\n';
    std::sort(numbers.begin(), numbers.end());

    for(auto each : numbers) {
        std::cout << each << ' ';
    }
    std::cout << '\n';

    // Create strong string typedefs
    Name person{{"Jean"}};
    Name person2{{"Jeff"}};
    person += "-Paul";
    std::cout << person << '\n';
    std::cout << (person < person2) << '\n';
    std::cout << "Using v member directly: " << person.v << '\n';
 
    return 0;
}
