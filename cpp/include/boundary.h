#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "forward_declarations.h"
#include "aliases.h"
#include <Eigen/Dense>

class boundary
{
public:
    boundary(const vector2 &f_a, const vector2 &f_b);
    auto normal() -> vector2;

    auto reflect(const ray &inc_ray) -> vector2;
    auto reflect(const vector2 &vec) -> vector2;

    auto a() const -> vector2;
    auto b() const -> vector2;

    auto as_line() const -> line;

    auto operator==(boundary &other) -> bool;

private:
    vector2 m_a;
    vector2 m_b;
};

#endif // BOUNDARY_H