#ifndef PATH_H
#define PATH_H

#include "forward_declarations.h"
#include <vector>
#include <string>
class path
{
public:
    path(const ray &first_ray);
    void bounce_n(const std::vector<boundary> &f_walls, std::size_t n_bounces);
    void bounce(const std::vector<boundary> &f_walls);

    std::size_t n_bounces();
    std::string debug_str(std::size_t n_first = 0);

private:
    std::vector<ray> rays;
};

#endif // PATH_H