#include <Hive.h>
#include <HiveAI>
#include <hive/namespaces.hpp>

#include <nnue.h>

static int epoch = 0;


int main() {
    Game game;
    AlfaBeta engine;
    engine.new_game(game, learn_nnue, heuristic1);

    nd2array<float> input(1, hive::X * hive::Y * 2 * 5 + 16);
    game.get_controller().get_accumulator()._input() = input;

    while (1) {
        auto bestmove = engine.get_best_move(7);
        printf("Epoch %d, loss: %f, analyzed position: %d\n", ++epoch, total_loss/counter, counter);
        total_loss = 0.0f;
        game.get_controller().engine_move(bestmove.piece, bestmove.where);
    }

    return 0;
}
