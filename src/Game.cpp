#include "Game.h"

namespace gol = GameOfLife;

gol::Game::Game(int n_x, int n_y){
    std::cout << "Creating simulation on grid of size (" << n_x << ", " << n_y << ")\n";
}

void gol::Game::read_state(std::string infile){
    std::cout << "Reading state from " << infile << "\n";
}

void gol::Game::init_random_state(){
    std::cout << "Initializing random state\n";
}

void gol::Game::write_state(std::string outfile){
    std::cout << "Writing state to " << outfile << "\n";
}

void gol::Game::print_state() {
    std::cout << "Printing state\n";
}

void gol::Game::setup(int logevery, bool logstdout, std::string logfile){
    std::cout << "Setup game to log every " << logevery;
    if(logstdout){
        std::cout << " to stdout\n";
    }
    else{
        std::cout << " to " << logfile << "\n";
    }
}

void gol::Game::run(int nsteps){
    std::cout << "Running for " << nsteps << "\n";
}

gol::Game::~Game(){
    std::cout << "Destroying simulation\n";
}