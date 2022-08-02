#include "cmdlineparser.h"
#include "boundary.h"
#include "ray.h"
#include "aliases.h"
#include "path.h"
#include "world.h"
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <omp.h>


int main(int argc, char **argv)
{
    auto options = cmd_line_parser::parse(argc, argv);

    std::cout << "OMP threads: " << omp_get_max_threads() << "\n";
    omp_set_num_threads(omp_get_max_threads());
    std::vector<double> times(omp_get_max_threads(), 0.);

    constexpr std::size_t n_bounces{3};

    constexpr std::size_t n_rays{1};

    // create walls
    float scale = 4.;
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
    for (auto b : crystal){
        std::cout << "normal:\n" << b.normal() << "\n";
    }

    std::vector<path> paths{};
    for (auto i = std::size_t{0}; i < n_rays; i++){
        paths.push_back(path{ray{vector2{0, 0}, static_cast<float>(i / static_cast<float>(n_rays) * 360.)}});
    }

#pragma omp parallel for
    for (auto i = std::size_t{0}; i < n_rays; i++)
    {
        // times[thread_id] = start_time();
        auto wtime = omp_get_wtime();
        int thread_id = omp_get_thread_num();

        paths[i].bounce_n(crystal, n_bounces);

        // times[thread_id] = end_time();

        wtime = omp_get_wtime() - wtime;
        times[omp_get_thread_num()] += wtime;
    }
    for (auto i = std::size_t{0}; i < omp_get_max_threads(); i++){
        std::cout << "Thread " << i << " " << static_cast<int>(times[i]*1e6) << " µs\n";
    }

    // for (auto p : paths){
    //     std::cout << p.n_bounces() << " ";
    // }
    std::cout << "\n";
    std::cout << paths[0].debug_str(1);
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