#include "ray.h"
#include <limits>
#include <Eigen/Dense>

ray::ray(const Eigen::Vector2i &f_start, const Eigen::Vector2i &f_direction)
 : m_start{std::move(f_start)}
 , m_direction{std::move(f_direction)}{}

auto ray::start() const -> Eigen::Vector2i
{
    return m_start;
}

auto ray::direction() const -> Eigen::Vector2i
{
    return m_direction;
}

auto ray::intersect(const boundary &wall) -> Eigen::Vector2i {
    // int x1 = wall.a.x;
    // int y1 = wall.a.y;
    // int x2 = wall.b.x;
    // int y2 = wall.b.y;

    // int x3 = this.pos.x;
    // int y3 = this.pos.y;
    // int x4 = this.pos.x + this.dir.x;
    // int y4 = this.pos.y + this.dir.y;

    // int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // if (den == 0)
    // {
    //     return;
    // }

    // int t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    // int u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
    // if (t > 0 && t < 1 && u > 0)
    // {
    //     Eigen::Vectori2 pt{
    //         x1 + t * (x2 - x1),
    //         y1 + t * (y2 - y1)
    //     };
    //     return pt;
    // }
    // else
    // {
        return Eigen::Vector2i{
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max()
        };
    // }
}