#ifndef PATH_H
#define PATH_H

#include "forward_declarations.h"
#include <vector>
class path
{
public:
    path(const ray &first_ray);

private:
    std::vector<ray> rays;
};

#endif // PATH_H