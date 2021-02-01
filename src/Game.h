/**
 * Implements Conway's Game of Life on a rectangular 2D grid.
 */
#ifndef GAMEOFLIFE_GAME_H_
#define GAMEOFLIFE_GAME_H_

#include <iostream>
#include <string>

namespace GameOfLife{

/*! Game on grid of size n_x * n_y. */
class Game{
    public:
        /**
         * Constructor.
         * @param n_x Grid size along x-direction.
         * @param n_y Grid size along y-direction.
         */
        Game(int n_x, int n_y); 

        /**
         * Read initial state from file.
         * @param infile Filename to read initial state data from.
         */
        void read_state(std::string infile);

        /*! Initialize random state. */
        void init_random_state();

        /**
         * Read initial state from file.
         * @param outfile Filename to append state data to.
         */
        void write_state(std::string outfile);

        /*! Print state to stdout. */
        void print_state();

        /**
         * Setup game.
         * @param logevery Interval to log simulation state.
         * @param logstdout Log simulation state to stdout (default=false).
         * @param logfile Filename to log state to.
         */
        void setup(int logevery, bool logstdout=true, std::string logfile="");

        /**
         * Run game.
         * @param nsteps Number of steps to run game for.
         */
        void run(int nsteps);

        /*! Destructor */
        ~Game();
};

}

#endif