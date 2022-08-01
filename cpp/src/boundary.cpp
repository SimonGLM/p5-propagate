#include "boundary.h"
#include "ray.h"
#include "aliases.h"
#include "world.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>

boundary::boundary(const vector2 &f_a, const vector2 &f_b)
    : m_a{std::move(f_a)}, m_b{std::move(f_b)} {}

auto boundary::normal() -> vector2
{
    auto rot_90_deg = Eigen::Matrix2f{
        {0, -1},
        {1, 0}};
    return (rot_90_deg * (m_a - m_b)).normalized();
}

auto boundary::a() const -> vector2
{
    return m_a;
}

auto boundary::b() const -> vector2
{
    return m_b;
}

auto boundary::reflect(const ray &inc_ray) -> vector2
{
    return reflect(inc_ray.direction());
}

auto boundary::reflect(const vector2 &vec) -> vector2
{
    auto wall_norm = normal();

    vector2 ref{vec - wall_norm * (2 * (wall_norm.transpose() * vec))};

    // be aware that in Eigen, it is only possible to implicitly convert from 1x1 matrix to scalar in one direction (weird)
    return ref;
}

auto boundary::as_line() const -> line
{
    // "Through" function builds a line which goes trough two points
    return line::Through(m_a, m_b);
}

auto boundary::operator==(boundary &other) -> bool
{
    // boundaries are equal if their a and b points are equal
    return (other.a() == m_a && other.b() == m_b);
}