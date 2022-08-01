#include "path.h"
#include "ray.h"
#include "boundary.h"
#include "world.h"
#include <sstream>
#include <string>
#include <vector>

path::path(const ray &first_ray)
    : rays{{first_ray}} {}

std::size_t path::n_bounces()
{
    return rays.size() - 1;
}

std::string path::debug_str()
{
    std::stringstream sstr{};
    sstr << "bounces: " << n_bounces() << "\n";
    for (auto r : rays){
        sstr << "start:\n" << r.start() << "\ndirection:\n" << r.direction() << "\n";
        if (r.end() != nullptr){
             sstr << "end:\n" << *(r.end()) << "\n";
        }
    }
    return sstr.str();
}

void path::bounce_n(const std::vector<boundary> &f_walls, std::size_t n_bounces){
    for (auto i = std::size_t{0}; i < n_bounces; i++){
        bounce(f_walls);
    }
}

void path::bounce(const std::vector<boundary> &f_walls)
{
    auto intersection = world::find_closest_intersect(rays.back(), f_walls);
    if (intersection.first != invalid_vector){
        auto pt = intersection.first;
        auto wall = intersection.second;
        rays.back().set_end(pt);
        rays.push_back(ray{pt, wall.reflect(rays.back()), std::make_shared<boundary>(wall)});
    }
}