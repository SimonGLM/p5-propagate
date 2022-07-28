#include "ray.h"
#include "aliases.h"
#include <limits>
#include <Eigen/Dense>

ray::ray(const vector2 &f_start, const vector2 &f_direction, std::shared_ptr<boundary> f_last_bounce)
    : m_start{std::move(f_start)}, m_direction{std::move(f_direction)}, m_last_bounce{f_last_bounce} {}

auto ray::start() const -> vector2
{
    return m_start;
}

auto ray::direction() const -> vector2
{
    return m_direction;
}

auto ray::as_line() const -> line
{
    // "Through" function builds a line which goes trough two points
    return line::Through(m_start, m_start + m_direction);
}

auto ray::last_bounce() const -> std::shared_ptr<boundary>
{
    return m_last_bounce;
}