#include "Game.h"
#include "Driver.h"

namespace gol = GameOfLife;

int main(int argc, char* argv[]){
    // Get config file name from command line args
    if(argc < 2){
        std::cerr << "Pass a configuration file name.\n";
    }
    else{
        gol::Driver game_driver(argv[1]);
        game_driver.game->run(game_driver.cfg_run);
    }
}