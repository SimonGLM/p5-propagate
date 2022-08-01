#include "world.h"
#include "boundary.h"
#include "ray.h"
#include "aliases.h"
#include <Eigen/Dense>
#include <iostream>

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
        if ((intersection - f_ray.start()).norm() < (intersection - closest).norm())
        {
            bounced_wall = wall;
            closest = intersection;
        }
    }
    return std::pair<vector2, boundary>{closest, bounced_wall};
}

auto world::intersect(const ray &f_ray, const boundary &wall) -> vector2
{
    auto pt = f_ray.as_line().intersection(wall.as_line());
    // check if it is the same line and throw away if it is?

    // check if point is inside wall boundaries and in forward direction of the ray
    bool valid_intersect = true;
    auto ray_vec = pt - f_ray.start();
    if (f_ray.direction()[0] != 0 && ray_vec[0]/f_ray.direction()[0] < 0){
        valid_intersect = false;
    }
    if (f_ray.direction()[1] != 0 && ray_vec[1]/f_ray.direction()[1] < 0){
        valid_intersect = false;
    }
    if ((wall.b() - pt).normalized() != (pt - wall.a()).normalized())
    {
        valid_intersect = false;
    }
    if (valid_intersect){
        return pt;
    }
    return invalid_vector;
}

/*
auto world::intersect(const ray &f_ray, const boundary &wall) -> vector2
{
    // not the most efficient, will be changed when it is understood what exactly
    // the vector arithmetics are of this thing
    int x1 = wall.a()[0];
    int y1 = wall.a()[1];
    int x2 = wall.b()[0];
    int y2 = wall.b()[1];

    int x3 = f_ray.start()[0];
    int y3 = f_ray.start()[1];
    int x4 = (f_ray.start() + f_ray.direction())[0];
    int y4 = (f_ray.start() + f_ray.direction())[1];

    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0)
    {
        return vector2{
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max()};
    }

    int t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    int u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
    if (t > 0 && u > 0)
    {
        vector2 pt{
            x1 + t * (x2 - x1),
            y1 + t * (y2 - y1)};
        return pt;
    }
    return vector2{
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()};
}
*/