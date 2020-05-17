#include <iostream>
#include "strong-types.hpp"
#include <cassert>

// If tests are successful, only output should be '435' at runtime

struct Width  { int v; };
struct Height { int v; };

int main()
{
    // Printing
    {
        Width buildingHeight{435};
        std::cout << buildingHeight << '\n';
    }

    // Assignment
    {
        Width a{89};
        Width b{a};
        assert(a == b && a == 89);
        Width c{8};
        a = c;
        assert(a == c && a == 8);

        a = Width{67};
        assert(a == 67);

        a = {};
        assert(a == 0); // May be undefined? Not sure.
    }

    // Basic arithmetic
    {
        Width buildingWidth{45};

        assert(buildingWidth + 5 == 50);
        assert(buildingWidth + buildingWidth == 90);

        assert(buildingWidth - 5 == 40);
        assert(buildingWidth - buildingWidth == 0);

        assert(buildingWidth * 4 == 180);
        assert(buildingWidth * buildingWidth == 45 * 45);

        assert(buildingWidth / 15 == 3);
        assert(buildingWidth / buildingWidth == 1);

        assert(buildingWidth % 2 == 1);
        assert(buildingWidth % buildingWidth == 0);
    }

    {
        Width buildingWidth{45};
        Width expected{55};

        buildingWidth += 10;
        assert(buildingWidth == 55);
        assert(buildingWidth == expected);
    }

    // Shorthand operators
    {
        Width buildingWidth{45};
        Width expected{35};

        buildingWidth -= 10;
        assert(buildingWidth == 35);
        assert(buildingWidth == expected);
    }

    {
        Width buildingWidth{45};
        Width expected{90};

        buildingWidth *= 2;
        assert(buildingWidth == 90);
        assert(buildingWidth == expected);
    }

    {
        Width buildingWidth{90};
        Width expected{45};

        buildingWidth /= 2;
        assert(buildingWidth == 45);
        assert(buildingWidth == expected);
    }

    {
        Width buildingWidth{100};
        Width expected{50};

        buildingWidth /= 2;
        assert(buildingWidth == 50);
        assert(buildingWidth == expected);
    }

    {
        Width buildingWidth{44};
        Width expected{0};

        buildingWidth %= 4;
        assert(buildingWidth == 0);
        assert(buildingWidth == expected);
    }

    {
        Width buildingWidth{45};
        Width expected{90};

        buildingWidth *= 2;
        assert(buildingWidth == 90);
        assert(buildingWidth == expected);
    }

    {
        Width buildingWidth{45};

        assert(buildingWidth++ == 45);
        assert(++buildingWidth == 47);
    }

    {
        Width buildingWidth{45};

        assert(buildingWidth-- == 45);
        assert(--buildingWidth == 43);
    }

    // Comparison operators
    {
        Width buildingWidth{45};
        Width other{45};

        assert(buildingWidth == 45);
        assert(buildingWidth == other);
    }

    {
        Width buildingWidth{45};
        Width other{46};

        assert(buildingWidth != 46);
        assert(buildingWidth != other);
    }

    {
        Width buildingWidth{45};
        Width other{46};

        assert(buildingWidth < 46);
        assert(buildingWidth < other);
    }

    {
        Width buildingWidth{45};
        Width other{40};

        assert(buildingWidth > 40);
        assert(buildingWidth > other);
    }

    {
        Width buildingWidth{45};
        Width other{48};

        assert(buildingWidth <= 45);
        assert(buildingWidth <= other);
    }

    {
        Width buildingWidth{45};
        Width other{41};

        assert(buildingWidth >= 45);
        assert(buildingWidth >= other);
    }

    // Const-ness
    {
        Width a{56};
        const Width b{67};
        a += b;
        assert(a == 56 + 67);
    }

    {
        Width c{56};
        int j = 4;
        int *p = &j;
        //assert(c + *p); //Should fail to compile
    }

    {
        Width w{98};
        Height y{98};
        // All 16 of these operations should fail to compile
        /*w + y;
        w - y;
        w * y;
        w / y;
        w % y;
        w += y;
        w -= y;
        w *= y;
        w /= y;
        w %= y;
        w == y;
        w != y;
        w < y;
        w > y;
        w <= y;
        w >= y;*/
    }
}
