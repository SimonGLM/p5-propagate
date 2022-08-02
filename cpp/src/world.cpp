#include "world.h"
#include "boundary.h"
#include "ray.h"
#include "aliases.h"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>

auto world::find_closest_intersect(const ray &f_ray, const std::vector<boundary> &f_boundaries) -> std::pair<vector2, boundary>
{
    auto closest = invalid_vector;
    boundary bounced_wall{invalid_vector, invalid_vector};
    for (auto wall : f_boundaries)
    {
        // skip the boundary the ray started at
        if (f_ray.last_bounce() != nullptr){
            if (*(f_ray.last_bounce()) == wall){
                continue;
            }
        }
        auto last_bounce = f_ray.last_bounce();
        if (last_bounce != nullptr)
        {
            if (wall == *last_bounce)
            {
                continue;
            }
        }
        // auto intersection = f_ray.as_line().intersect(wall.as_line());
        auto intersection = intersect(f_ray, wall);
        // calculate the distances from start to intersection and closest
        // std::cout << "from start: " << std::fabs((intersection - f_ray.start()).norm()) << "\n";
        // std::cout << "from closest: " << std::fabs((intersection - closest).norm()) << "\n";
        if (intersection != invalid_vector && std::fabs((intersection - f_ray.start()).norm()) < std::fabs((intersection - closest).norm()))
        {
            bounced_wall = wall;
            closest = intersection;
        }
    }
    // std::cout << "closest:\n" << closest << "\n";
    return std::pair<vector2, boundary>{closest, bounced_wall};
}

auto world::intersect(const ray &f_ray, const boundary &wall) -> vector2
{
    auto pt = f_ray.as_line().intersection(wall.as_line());
    // check if it is the same line and throw away if it is?

    // check if point is inside wall boundaries and in forward direction of the ray
    // (normalized direction vector is equal to normalized distance between start and intersection)
    if (!f_ray.direction().normalized().isApprox((pt - f_ray.start()).normalized(), 1e-4)){
        return invalid_vector;
    }
    if (!(wall.b() - pt).normalized().isApprox((pt - wall.a()).normalized(), 1e-4))
    {
        return invalid_vector;
    }
    return pt;
}