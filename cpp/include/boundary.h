#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "forward_declarations.h"
#include <Eigen/Dense>

class boundary
{
public:
    boundary(const Eigen::Vector2i &f_a, const Eigen::Vector2i &f_b);
    auto normal() -> Eigen::Vector2i;

    auto reflect(const ray &inc_ray) -> Eigen::Vector2i;
    auto reflect(const Eigen::Vector2i &vec) -> Eigen::Vector2i;

private:
    Eigen::Vector2i m_a;
    Eigen::Vector2i m_b;
};

#endif // BOUNDARY_H