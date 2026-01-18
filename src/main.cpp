#include <Hive.h>
#include <iostream>


int main() {
    Protocol protocol;
    Command c;
    std::cout << protocol.info() << "\nok\n";
    while(true) {
        std::cin >> c;
        c.execute(protocol);
    }
    return 0;
}
