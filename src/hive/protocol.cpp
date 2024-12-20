#include <hive/protocol.hpp>
#include <sstream>


std::istream &operator>>(std::istream &is, Command &command) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream line_stream(line);
        std::getline(line_stream, command.command_type, ' ');
        std::getline(line_stream, command.arguments);
    }
    return is;
}


void Command::execute(Game &game) {
    if (this->command_type == Instrucions::newgame) {
        std::cout << game.get_gamestring();
    } else if (this->command_type == Instrucions::info) {

    } else if (this->command_type == Instrucions::play) {
        game.player_move(create_move(this->arguments));
        game.update();
        std::cout << game.get_gamestring();
    } else if (this->command_type == Instrucions::undo) {
        int n = 1;
        if (this->arguments.size() > 0) n = std::stoi(this->arguments);
        game.undo(std::max(1, n));
        std::cout << game.get_gamestring();
    } else if (this->command_type == Instrucions::validmoves) {
        game.set_valid_moves();
        std::cout << game.get_valid_moves();
    } else if (this->command_type == Instrucions::bestmove) {

    } else if (this->command_type == Instrucions::options) {
        
    } else if (this->command_type == Instrucions::help) {
        std::cout << "Usage: <COMMAND> [optional arguments]\n";
        std::cout << "Possible commands:\n";
        std::cout << "info                                          - display info about game.\n";
        std::cout << "newgame                                       - start a new game\n";
        std::cout << "play [what insect] [next to another insect]   - make a move in game.\n\tFor example: play wS1 /wG1 - place the first white spider on the bottom left edge of the first white grasshoper\n";
        std::cout << "undo [n]                                      - go back n moves. Default 1\n";
        std::cout << "validmoves                                    - return all possible moves separated ';' for actual possition\n";
        std::cout << "bestmove                                      - return the best move according to engine for actual possition\n";
        std::cout << "options                                       - return options about engine\n";
        std::cout << "help                                          - return help";
    } else {
        std::cout << "err Invalid command. Try 'help' to see a list of valid commands.";
    }
    std::cout << "\nok\n";
}


Move_parameters create_move(std::string &arguments) {
    std::string piece, target;
    std::istringstream stream(arguments);
    std::getline(stream, piece, ' ');
    std::getline(stream, target);
    if (target.length() == 0) return {piece, target, Directions::DEFAULT, arguments};
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
        return {piece, target.erase(0, 1), d, arguments};
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
        return {piece, target.erase(n, 1), d, arguments};
    }
}
