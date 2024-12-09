#include <hive/protocol.hpp>
#include <sstream>


void analize_command(const std::string &command) {

}


std::istream &operator>>(std::istream &is, Command &command) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream line_stream(line);
        std::getline(line_stream, command.command_type, ' ');
        std::getline(line_stream, command.parameters);
    }
    return is;
}


void Command::execute(Game &game) {
    if (this->command_type == Instrucions::newgame) {
        std::cout << game.get_gamestring();
    } else if (this->command_type == Instrucions::info) {

    } else if (this->command_type == Instrucions::play) {

    } else if (this->command_type == Instrucions::validmoves) {
        
    } else if (this->command_type == Instrucions::bestmove) {

    } else if (this->command_type == Instrucions::options) {
        
    } else {
        std::cout << "err Invalid command. Try 'help' to see a list of valid commands.\n";
    }
    std::cout << "ok\n";
}