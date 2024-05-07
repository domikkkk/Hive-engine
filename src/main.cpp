#include <Hive>
#include <HiveAI>
#include <iostream>


int main(int argc, char **argv) {
    hive::Insect p({1, 1});
    std::vector<Coords> result = p.get_surrounding_locations();
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i].x << " " << result[i].y << "\n";
    }
    return 0;
}
