#include "Game.h"

int main(int argc, char* argv[]){
    gol::Game game(5,5);
    game.read_state("~/state.in");
    game.init_random_state();
    game.write_state("~/state.out");
    game.print_state();
    game.run(1000, 1);
}