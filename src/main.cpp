#include <Hive>
#include <iostream>
#include <decorators.hpp>



int main(int argc, char **argv) {
    Protocol protocol;
    Command c;
    std::cout << protocol.info() << "\nok\n";
    while(true) {
        std::cin >> c;
        c.execute(protocol);
    }
    return 0;
}
