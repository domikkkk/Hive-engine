#include <Hive>
#include <iostream>
#include <decorators.hpp>



int main(int argc, char **argv) {
    Protocol protocol;
    Command c;
    std::cout << protocol.info() << "ok\n";
    while(true) {
        std::cin >> c;
        c.execute(protocol);
    }
    return 0;
}
