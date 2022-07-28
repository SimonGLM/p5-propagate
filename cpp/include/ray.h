#ifndef RAY_H
#define RAY_H

#include "forward_declarations.h"
#include <Eigen/Dense>
#include <memory>

class ray
{
public:
    ray(const Eigen::Vector2i &f_start, const Eigen::Vector2i &f_direction);
    auto start() const -> Eigen::Vector2i;
    auto direction() const -> Eigen::Vector2i;
    auto intersect(const boundary &wall) -> Eigen::Vector2i;

private:
    Eigen::Vector2i m_start;
    Eigen::Vector2i m_direction;
    // Eigen::Hyperplane<int, 2> line; // in 2D a Hyperplane is a line.
    std::shared_ptr<boundary> last_bounce{nullptr};
};

#endif // RAY_H