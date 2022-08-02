#include "ray.h"
#include "aliases.h"
#include <limits>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <cmath>

ray::ray(const vector2 &f_start, const vector2 &f_direction, std::shared_ptr<boundary> f_last_bounce)
    : m_start{std::move(f_start)}, m_direction{std::move(f_direction)}, m_last_bounce{f_last_bounce} {}

ray::ray(const vector2 &f_start, float angle, std::shared_ptr<boundary> f_last_bounce)
    : m_start{std::move(f_start)}, m_last_bounce{f_last_bounce}
{
    Eigen::Rotation2D<float> rotation{angle * (M_PI / 180)};
    vector2 f_direction{0, 1};
    m_direction = rotation * f_direction;
}

auto ray::start() const -> vector2
{
    return m_start;
}

auto ray::end() const -> std::shared_ptr<vector2>
{
    return m_end;
}

void ray::set_end(const vector2 &f_end)
{
    m_end = std::make_shared<vector2>(f_end);
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