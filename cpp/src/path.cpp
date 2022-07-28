#include "path.h"
#include "ray.h"
#include <vector>

path::path(const ray &first_ray)
    : rays{{first_ray}} {}