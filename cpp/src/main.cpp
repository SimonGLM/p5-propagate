#include "cmdlineparser.h"
#include "boundary.h"
#include "ray.h"
#include <Eigen/Dense>
#include <iostream>

int main(int argc, char **argv)
{
    auto options = cmd_line_parser::parse(argc,argv);
    Eigen::Vector2i a{200, 0};
    Eigen::Vector2i b{0, 0};
    boundary wall{a,b};
    // std::cout << "a:\n" << a << "\n\n";
    // std::cout << "b:\n"
    //           << b << "\n\n";
    // std::cout << "a-b:\n"
    //           << a - b << "\n\n";
    // std::cout << "normal:\n"
    //           << wall.normal() << std::endl;
    Eigen::Vector2i c{0, 0};
    Eigen::Vector2i d{100,100};
    ray photon{c,d};
    wall.reflect(photon);
    return 0;
}