#include "cmdlineparser.h"
#include "boundary.h"
#include "ray.h"
#include "aliases.h"
#include "path.h"
#include "world.h"
#include <Eigen/Dense>
#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
    auto options = cmd_line_parser::parse(argc, argv);

    constexpr std::size_t n_bounces{2};

    constexpr std::size_t n_rays{1};

    // create walls
    // float scale = 4.;
    // float BF{21.28};
    // float BR{28.75};
    // vector2 A{100 * scale, BR / 2 * scale};
    // vector2 B{-100 * scale, BR / 2 * scale};
    // vector2 C{-100 * scale, -BR / 2 * scale};
    // vector2 D{100 * scale, BF - BR / 2 * scale};
    vector2 A{100, 100};
    vector2 B{-100, 100};
    vector2 C{-100, -100};
    vector2 D{100, -100};
    std::vector<boundary> crystal{{boundary{A, B},
                                   boundary{B, C},
                                   boundary{C, D},
                                   boundary{D, A}}};
    for (auto b : crystal){
        std::cout << "normal:\n" << b.normal() << "\n";
    }
    vector2 interaction_pt{0,0};
    std::vector<path> paths{};
    paths.push_back(path{ray{interaction_pt, static_cast<float>(2)}});
    // for (auto i = std::size_t{0}; i < n_rays; i++){
    //     paths.push_back(path{ray{interaction_pt, static_cast<float>(i)}});
    // }
    // p.append(new Ray(createVector((X0 - 100) * scale, 0), p5.Vector.fromAngle(radians(a / nRays * 360))));


#pragma omp parallel for
    for (auto i = std::size_t{0}; i < n_rays; i++){
        paths[i].bounce_n(crystal, n_bounces);
    }

    for (auto p : paths){
        std::cout << p.n_bounces() << " ";
        // std::cout << p.debug_str();
    }
    std::cout << "\n";
    std::cout << paths[0].debug_str();
    std::cout << std::flush;

    // vector2 A{100, 100};
    // vector2 B{-100, 100};
    // ray r{vector2{200,0}, vector2{0,1}};
    // boundary wall{A, B};
    // std::cout << "A:\n" << A << std::endl;
    // std::cout << "B:\n" << B << std::endl;
    // std::cout << world::intersect(r, wall) << std::endl;
    return 0;
}