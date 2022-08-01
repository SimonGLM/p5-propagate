#ifndef ALIASES_H
#define ALIASES_H

#include <Eigen/Dense>

using vector2 = Eigen::Vector2f;
using line = Eigen::Hyperplane<float, 2>; // in 2D a Hyperplane is a line.
static const vector2 invalid_vector{
    std::numeric_limits<int>::max(),
    std::numeric_limits<int>::max()};

#endif // ALIASES_H