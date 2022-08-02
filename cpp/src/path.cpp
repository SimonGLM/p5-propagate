#include "path.h"
#include "ray.h"
#include "boundary.h"
#include "world.h"
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

auto det(vector2 v1, vector2 v2) -> float{
    return v1[0]*v2[1] - v1[1]*v2[0];
}

path::path(const ray &first_ray)
    : m_rays{{first_ray}} {}

auto path::n_bounces() const -> std::size_t
{
    return m_rays.size() - 1;
}

auto path::debug_str(std::size_t n_first) const -> std::string
{
    std::stringstream sstr{};
    sstr << "bounces: " << n_bounces() << "\n";
    if (n_first == 0){
        n_first = m_rays.size();
    }
    for (auto i = std::size_t{0}; i < std::min(n_first, m_rays.size()); i++){
        sstr << "start:\n"
             << m_rays[i].start() << "\ndirection:\n"
             << m_rays[i].direction() << "\n"
             << "angle: " << std::atan2(det(vector2{1,0},m_rays[i].direction()), m_rays[i].direction().dot(vector2{1,0})) * 180./M_PI << "\n";
        if (m_rays[i].end() != nullptr)
        {
            sstr << "end:\n"
                 << *(m_rays[i].end()) << "\n";
        }
    }
    return sstr.str();
}

auto path::length() const -> float
{
    return m_length;
}

auto path::termination() const -> std::shared_ptr<boundary>
{
    return m_termination;
}

void path::process(const std::vector<boundary> &f_walls, std::size_t max_bounces, float max_length){
    for (auto i = std::size_t{0}; i < max_bounces; i++){
        if (!bounce(f_walls) || m_length > max_length){
            break;
        }
    }
}

auto path::bounce(const std::vector<boundary> &f_walls) -> bool
{
    auto intersection = world::find_closest_intersect(m_rays.back(), f_walls);
    if (intersection.first != invalid_vector){
        auto pt = intersection.first;
        auto wall = intersection.second;
        m_rays.back().set_end(pt);
        auto reflected = wall.reflect(m_rays.back());
        m_length += std::fabs((pt - m_rays.back().start()).norm());

        if (reflected == invalid_vector){
            m_termination = std::make_shared<boundary>(wall);
            return false;
        }
        m_rays.push_back(ray{pt, std::move(reflected), std::make_shared<boundary>(wall)});
        return true;
    }
    return false;
}