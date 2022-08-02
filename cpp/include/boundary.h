#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "forward_declarations.h"
#include "aliases.h"
#include <Eigen/Dense>
#include <cmath>

class boundary
{
public:
    boundary(const vector2 &f_a, const vector2 &f_b, bool f_is_absorbing = false);
    [[nodiscard]] auto normal() const -> vector2;

    [[nodiscard]] auto reflect(const ray &inc_ray) -> vector2;
    [[nodiscard]] auto reflect(const vector2 &vec) -> vector2;

    [[nodiscard]] auto a() const -> vector2;
    [[nodiscard]] auto b() const -> vector2;

    [[nodiscard]] auto as_line() const -> line;

    [[nodiscard]] auto operator==(boundary &other) -> bool;

private:
    vector2 m_a;
    vector2 m_b;
    bool m_is_absorbing;
    // angle in degrees under which total reflection occurs
    inline static const double critical_angle{std::asin(1.000293/2.2)};
};

#endif // BOUNDARY_H