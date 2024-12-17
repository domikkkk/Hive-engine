#include <hive/coordinates.hpp>
#include <hive/namespaces.hpp>


bool Coords::operator==(const Coords &c) const noexcept {
    return this->x == c.x && this->y == c.y && this->z == c.z;
}

bool Coords::operator!=(const Coords &c) const noexcept {
    return this->x != c.x || this->y != c.y || this->z != c.z;
}


Coords Coords::operator+(const Coords &c) const noexcept {
    return {this->x + c.x, this->y + c.y};
}


Directions Coords::get_opposite(const Coords &c) const noexcept {
    int diff_y = this->y - c.y;
    int diff_x = this->x - c.x;
    if (diff_y > 0) {
        if (diff_x > 0) return Directions::SW;
        else if (diff_x == 0) return Directions::S; 
    } else if (diff_y == 0) {
        if (diff_x > 0) return Directions::W;
        else if (diff_x < 0) return Directions::E;
    } else {
        if (diff_x == 0) return Directions::N;
        else if (diff_x < 0) return Directions::NE;
    }
    return Directions::DEFAULT;
}


// const Coords Coords::get_neighbor(const Directions &direction) const noexcept {
//     switch (direction)
//     {
//     case Directions::N:  // N
//         return {this->x, this->y + 1};
//     case Directions::NE:  // NE
//         return {this->x + 1, this->y + 1};
//     case Directions::E:  // SE
//         return {this->x + 1, this->y};
//     case Directions::S:  // S
//         return {this->x, this->y - 1};
//     case Directions::SW:  // SW
//         return {this->x - 1, this->y - 1};
//     case Directions::W:  // NW
//         return {this->x - 1, this->y};
//     case Directions::UP:
//         return {this->x, this->y, this->z + 1};
//     case Directions::DOWN:
//         return {this->x, this->y, this->z - 1};
//     default:
//         return {200, 200};  // unexpected error
//     }
// }


const Coords Coords::get_ground() const noexcept {
    return {this->x, this->y, 0};
}


std::vector<Coords> Coords::get_surrounding_locations() const noexcept {
    std::vector<Coords> neighbors;
    neighbors.emplace_back(this->x, this->y + 1, this->z);
    neighbors.emplace_back(this->x + 1, this->y + 1, this->z);
    neighbors.emplace_back(this->x + 1, this->y, this->z);
    neighbors.emplace_back(this->x, this->y - 1, this->z);
    neighbors.emplace_back(this->x - 1, this->y - 1, this->z);
    neighbors.emplace_back(this->x - 1, this->y, this->z);
    return neighbors;
}


std::vector<Coords> Coords::get_in_Z() const noexcept {
    std::vector<Coords> Z;
    if (this->z > 0) {
        Z.emplace_back(this->x, this->y, this->z - 1);
    }
    if (this->z < hive::Z) {
        Z.emplace_back(this->x, this->y, this->z + 1);
    }
    return Z;
};


std::size_t HashFn::operator()(const Coords &c) const noexcept {
    std::size_t hash = (c.x + hive::X) << 16;
    hash ^= (c.y + hive::Y) << 8;
    hash ^= c.z;
    return hash;
}
