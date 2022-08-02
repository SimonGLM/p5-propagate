#ifndef PATH_H
#define PATH_H

#include "forward_declarations.h"
#include <vector>
#include <deque>
#include <string>
#include <memory>
class path
{
public:
    path(const ray &first_ray, bool f_keep_all_rays = false);
    void process(const std::vector<boundary> &f_walls, std::size_t max_bounces = std::numeric_limits<std::size_t>::max(), float max_length = 1e6);
    auto bounce(const std::vector<boundary> &f_walls) -> bool;

    auto n_bounces() const -> std::size_t;
    auto length() const -> float;
    auto debug_str(std::size_t n_first = 0) const -> std::string;
    auto termination() const -> std::shared_ptr<boundary>;

private:
    float m_length{0.};
    std::shared_ptr<boundary> m_termination{nullptr};
    std::deque<ray> m_rays;
    bool m_keep_all_rays;
};

#endif // PATH_H