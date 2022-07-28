#include "boundary.h"
#include "ray.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>

boundary::boundary(const Eigen::Vector2i &f_a, const Eigen::Vector2i &f_b)
    : m_a{std::move(f_a)}, m_b{std::move(f_b)} {}

auto boundary::normal() -> Eigen::Vector2i
{
    auto rot_90_deg = Eigen::Matrix2i{
        {0, -1},
        {1, 0}};
    return (rot_90_deg * (m_a - m_b)).normalized();
}

auto boundary::reflect(const ray &inc_ray) -> Eigen::Vector2i
{
    return reflect(inc_ray.direction());
}

auto boundary::reflect(const Eigen::Vector2i &vec) -> Eigen::Vector2i
{
    auto wall_norm = normal();
    // be aware that in Eigen, it is only possible to implicitly convert from 1x1 matrix to scalar in one direction (weird)
    return (wall_norm *(2 * (wall_norm.transpose() * vec)) - vec);
}