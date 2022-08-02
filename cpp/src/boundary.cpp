#include "boundary.h"
#include "ray.h"
#include "aliases.h"
#include "world.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>
#include <cmath>

float random_float(float a, float b)
{
    float random = (static_cast<float>(rand())) / static_cast<float>(RAND_MAX);
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

boundary::boundary(const vector2 &f_a, const vector2 &f_b, bool f_is_absorbing)
    : m_a{std::move(f_a)}, m_b{std::move(f_b)}, m_is_absorbing{f_is_absorbing} {}

auto boundary::normal() const -> vector2
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
    if (m_is_absorbing){
        return invalid_vector;
    }
    auto wall_norm = normal();

    // angle in respect to the normal of the plane
    auto angle = std::acos(wall_norm.transpose() * vec) * 180. / M_PI;
    // std::cout << "angle: " << angle << "°\n";

    // direct reflection due to total reflection
    if (angle > critical_angle)
    {
        // be aware that in Eigen, it is only possible to implicitly convert from 1x1 matrix to scalar in one direction (weird)
        return vector2{vec - wall_norm * (2 * (wall_norm.transpose() * vec))};
    }
    return invalid_vector;

    // diffuse reflection due to teflon
    // std::cout << "critical angle: " << critical_angle << "\n";
    auto random_angle = random_float(-critical_angle, critical_angle); // in respect to the normal

    Eigen::Rotation2D<float> rotation{random_angle};
    // std::cout << "random angle: " << random_angle << "°\n";
    // std::cout << "new direction:\n"
    //           << -(rotation * wall_norm) * std::fabs(vec.norm()) << "\n";
    return -(rotation * wall_norm) * std::fabs(vec.norm());
}

auto boundary::as_line() const -> line
{
    // "Through" function builds a line which goes trough two points
    return line::Through(m_a, m_b);
}

auto boundary::operator==(boundary &other) -> bool
{
    // boundaries are equal if their a and b points are equal
    return (other.a().isApprox(m_a, 1e-4) && other.b().isApprox(m_b, 1e-4));
}