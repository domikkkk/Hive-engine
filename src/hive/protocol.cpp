#include <hive/protocol.hpp>
#include <sstream>


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
        game.player_move(create_move(this->parameters));
        game.update();
        std::cout << game.get_gamestring();
    } else if (this->command_type == Instrucions::validmoves) {
        
    } else if (this->command_type == Instrucions::bestmove) {

    } else if (this->command_type == Instrucions::options) {
        
    } else {
        std::cout << "err Invalid command. Try 'help' to see a list of valid commands.";
    }
    std::cout << "\nok\n";
}


Move_parameters create_move(std::string &parameters) {
    std::string piece, target;
    std::istringstream stream(parameters);
    std::getline(stream, piece, ' ');
    std::getline(stream, target);
    if (target.length() == 0) return {piece, target, Directions::DEFAULT, parameters};
    Directions d;
    if (target[0] < 97) {
        switch (target[0])
        {
        case '/':
            d = Directions::SW;
            break;
        case '-':
            d = Directions::W;
            break;
        case '\\':
            d = Directions::N;
            break;
        default:
            d = Directions::DEFAULT;
            break;
        }
        return {piece, target.erase(0, 1), d, parameters};
    } else {
        std::size_t n = target.size()-1;
        switch (target[n])
        {
        case '/':
            d = Directions::NE;
            break;
        case '-':
            d = Directions::E;
            break;
        case '\\':
            d = Directions::S;
            break;
        default:
            d = Directions::DEFAULT;
            break;
        }
        return {piece, target.erase(n, 1), d, parameters};
    }
}