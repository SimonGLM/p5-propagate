#include "cmdlineparser.h"
#include "boundary.h"
#include "ray.h"
#include "aliases.h"
#include <Eigen/Dense>
#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
    auto options = cmd_line_parser::parse(argc, argv);

    // create walls
    unsigned scale = 4;
    float BF{21.28};
    float BR{28.75};
    vector2 A{100 * scale, BR / 2 * scale};
    vector2 B{-100 * scale, BR / 2 * scale};
    vector2 C{-100 * scale, -BR / 2 * scale};
    vector2 D{100 * scale, BF - BR / 2 * scale};
    std::vector<boundary> crystal{{boundary{A, B},
                                   boundary{B, C},
                                   boundary{C, D},
                                   boundary{D, A}}};

    return 0;
}