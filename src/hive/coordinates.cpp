#include <hive/coordinates.hpp>


Coords movements(const Directions &direction) {
    switch (direction)
    {
    case Directions::N:  // N
        return {0, 2};
    case Directions::NE:  // NE
        return {1, 1};
    case Directions::SE:  // SE
        return {1, -1};
    case Directions::S:  // S
        return {0, -2};
    case Directions::SW:  // SW
        return {-1, -1};
    case Directions::NW:  // NW
        return {-1, 1};
    default:
        return {200, 200};  // unexpected error
    }
}


size_t HashFn::operator()(const Coords &c) const {
#ifdef DEBUG
    return c.x + 23 * (c.y + 47 * c.z);
#endif
    size_t hash = (c.x + 22) << 16;
    hash ^= (c.y + 44) << 8;
    hash ^= c.z;
    return hash;
}
