#include "basic_geometry.h"
#include <iostream>

int main()
{
    basic_geometry::point o(0, 0);
    basic_geometry::point a(1, 1);
    basic_geometry::point b(-1, 0);
    basic_geometry::point c(0, -1);
    std::vector<basic_geometry::point> verticies {a, b, c, a, b, c};
    basic_geometry::polygon chain(verticies);
    try 
    {
        std::cout << basic_geometry::winding_number(o, chain) << '\n';
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
    }
}