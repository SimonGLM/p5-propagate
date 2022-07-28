#ifndef WORLD_H
#define WORLD_H

#include "forward_declarations.h"
#include "aliases.h"
#include <Eigen/Dense>

class world
{
public:
    /**
     * @brief Returns the first point where a ray will intersect with a wall
     *
     * @param f_ray
     * @param f_boundaries
     * @return vector2
     */
    static auto find_closest_intersect(const ray &f_ray, const std::vector<boundary> &f_boundaries) -> vector2;

    /**
     * @brief Returns the intersection point of a ray with a wall
     *
     * @param f_ray
     * @param f_wall
     * @return vector2
     */
    static auto intersect(const ray &f_ray, const boundary &f_wall) -> vector2;

private:
    world() = default;
    ~world() = default;
};

#endif // WORLD_H