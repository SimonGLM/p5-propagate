#ifndef RAY_H
#define RAY_H

#include "forward_declarations.h"
#include "aliases.h"
#include <Eigen/Dense>
#include <memory>

class ray
{
public:
    ray(const vector2 &f_start, const vector2 &f_direction, std::shared_ptr<boundary> f_last_bounce = nullptr);
    ray(const vector2 &f_start, float angle, std::shared_ptr<boundary> f_last_bounce = nullptr);

    /**
     * @brief Returns the origin point of a ray
     *
     * @return vector2
     */
    auto start() const -> vector2;

    /**
     * @brief Returns the point at which it was bounced
     *
     * @return vector2
     */
    auto end() const -> std::shared_ptr<vector2>;

    void set_end(const vector2 &f_end);

    /**
     * @brief Returns the direction vector of a ray
     *
     * @return vector2
     */
    auto direction() const -> vector2;

    auto as_line() const -> line;

    auto last_bounce() const -> std::shared_ptr<boundary>;

private:
    vector2 m_start;
    vector2 m_direction;
    std::shared_ptr<vector2> m_end{nullptr};
    std::shared_ptr<boundary> m_last_bounce;
};

#endif // RAY_H