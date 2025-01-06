#include <hive/protocol.hpp>
#include <sstream>


void Protocol::create_game() noexcept {
    this->game = Game(++this->n_game);
    this->engine.set_game(game, heuristic1);
}


std::string Protocol::get_info() noexcept {
    std::string gamestring = this->game.get_gameType() + ";";
    switch (this->game.get_gameState())
    {
    case State::NOTSTARTED:
        gamestring += GameState::notstarted;
        break;
    case State::INPROGRESS:
        gamestring += GameState::inprogress;
        break;
    case State::DRAW:
        gamestring += GameState::draw;
        break;
    case State::WHITEWINS:
        gamestring += GameState::whitewins;
        break;
    case State::BLACKWINS:
        gamestring += GameState::blackwins;
        break;
    default:
        break;
    }
    gamestring += ";";
    switch (this->game.get_controller().get_current())
    {
    case Color::WHITE:
        gamestring += "White[";
        break;
    case Color::BLACK:
        gamestring += "Black[";
    default:
        break;
    }
    gamestring += std::to_string(this->game.get_controller().get_turns()) + "]";
    for (auto str: this->game.get_moves()) {
        gamestring += ';' + str;
    }
    return gamestring;
}


void Protocol::move(const struct Move_parameters &move) {
    this->game.player_move(move);
    this->game.update();
}


void Protocol::unmove(const int &n) noexcept {
    this->game.undo(n);
}


void Protocol::pass() noexcept {
    this->game.pass();
}


std::string Protocol::get_notation(const std::string &piece, const Coords &where) noexcept {
    if (piece == Instrucions::pass) return Instrucions::pass;
    std::string to_display = piece + " ";
    auto adjacent = this->game.get_controller().find_adjacent(where);
    switch (adjacent.second)
    {
    case Directions::NE:
        to_display += adjacent.first + "/";
        break;
    case Directions::E:
        to_display += adjacent.first + "-";
        break;
    case Directions::S:
        to_display += adjacent.first + "\\";
        break;
    case Directions::SW:
        to_display += "/" + adjacent.first;
        break;
    case Directions::W:
        to_display += "-" + adjacent.first;
        break;
    case Directions::N:
        to_display += "\\" + adjacent.first;
        break;
    case Directions::UP:
        to_display += adjacent.first;
        break;
    case Directions::DEFAULT:
        to_display.erase(to_display.size()-1);
    default:
        break;
    }
    return to_display;
}


std::string Protocol::get_valid_moves() noexcept {
    std::string to_display = "";
    std::unordered_map<std::string, std::vector<Coords>> valid_moves;
    this->game.set_valid_moves(valid_moves);
    bool is_valid = false;
    for (auto move: valid_moves) {
        for (auto where: move.second) {
            is_valid = true;
            to_display += this->get_notation(move.first, where) + ";";
        }
    }
    if (!is_valid) {
        return Instrucions::pass;
    }
    return to_display.erase(to_display.size()-1, 1);
}


std::string Protocol::get_best_move(const int &depth) noexcept {
    auto best_move = this->engine.get_best_move(depth);
    return get_notation(best_move.piece, best_move.where);
}


std::istream &operator>>(std::istream &is, Command &command) {
    std::string line;
    command.arguments = "";
    if (std::getline(is, line)) {
        std::istringstream line_stream(line);
        std::getline(line_stream, command.command_type, ' ');
        std::getline(line_stream, command.arguments);
    }
    return is;
}


void Command::execute(Protocol &protocol) {
    try {
        if (this->command_type == Instrucions::newgame) {
            protocol.create_game();
            std::cout << protocol.get_info();
        } else if (this->command_type == Instrucions::info) {
            std::cout << protocol.get_best_move(1);
        } else if (this->command_type == Instrucions::play) {
            if (this->arguments == Instrucions::pass) protocol.pass();
            else protocol.move(create_move(this->arguments));
            std::cout << protocol.get_info();
        } else if (this->command_type == Instrucions::undo) {
            int n = 1;
            if (this->arguments.size() > 0) n = std::stoi(this->arguments);
            protocol.unmove(std::max(1, n));
            std::cout << protocol.get_info();
        } else if (this->command_type == Instrucions::validmoves) {
            std::cout << protocol.get_valid_moves();
        } else if (this->command_type == Instrucions::bestmove) {
            auto info = get_info_from_BestMove(this->arguments);
            if (info.is_time) {

            } else {
                std::cout << protocol.get_best_move(info.depth);
            }
        } else if (this->command_type == Instrucions::options) {
        
        } else if (this->command_type == Instrucions::pass) {
            protocol.pass();
            std::cout << protocol.get_info();
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
    } catch (const PieceNotExisting &e) {
        std::cerr << e.what();
    } catch (const PieceNotOnTheBoard &e) {
        std::cerr << e.what();
    } catch (const NotOneHive &e) {
        std::cerr << e.what();
    } catch (const InvalidMove &e) {
        std::cerr << e.what();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
    std::cout << "\nok\n";
}


Move_parameters create_move(const std::string &arguments) noexcept {
    std::string piece, target;
    std::istringstream stream(arguments);
    std::getline(stream, piece, ' ');
    std::getline(stream, target);
    if (target.length() == 0) return {piece, target, Directions::DEFAULT, arguments};
    std::size_t n = target.size()-1;
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
    } else if (((target[n] > 57 && target[n] < 97) || (target[n] < 48)) && target[n] != 81) {
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
    } else {
        return {piece, target, Directions::UP, arguments};
    }
}


_BestMove_Arguments get_info_from_BestMove(const std::string &arguments) noexcept {
    _BestMove_Arguments result;
    std::string type, number;
    std::istringstream stream(arguments);
    std::getline(stream, type, ' ');
    if (type.size() == 0) return result;
    if (type == BestMove_Argument::depth) {
        std::getline(stream, number);
        result.depth = std::stoi(number);
    } else if (type == BestMove_Argument::time) {
        result.is_time = true;
        std::getline(stream, number, ':');
        result.time += std::stoi(number) * 3600;
        std::getline(stream, number, ':');
        result.time += std::stoi(number) * 60;
        std::getline(stream, number);
        result.time += std::stoi(number);
    }
    return result;
}
