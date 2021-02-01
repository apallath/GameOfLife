/**
 * Implements Conway's Game of Life on a rectangular 2D grid.
 */
#ifndef GAMEOFLIFE_GAME_H_
#define GAMEOFLIFE_GAME_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace GameOfLife{

/*! Game on grid of size n_rows * n_cols. */
class Game{
    public:
        /**
         * Constructor.
         * @param n_rows Number of rows in grid.
         * @param n_cols Number of columns in grid.
         */
        Game(int n_rows, int n_cols); 

        /**
         * Read initial state from file.
         * @param infile Filename to read initial state data from.
         */
        void read_state(std::string infile);

        /*! Initialize random state. */
        void init_random_state();

        /**
         * Read initial state from file.
         * @param tstep Current timestep.
         * @param outfile Filename to append state data to.
         */
        void write_state(int tstep, std::string outfile);

        /** 
         * Print state to stdout. 
         * @param tstep Current timestep.
        */
        void print_state(int tstep);

        /**
         * Setup game.
         * @param logevery Interval to log simulation state.
         * @param logsleep Time interval (in ms) to sleep after logging.
         * @param logtofile Log simulation state to file (default=false).
         * @param logfile Filename to log state to.
         */
        void setup(int logevery, int logsleep, bool logtofile=false, std::string logfile="");

        /**
         * Run game.
         * @param nsteps Number of steps to run game for.
         */
        void run(int nsteps);

        /*! Destructor */
        ~Game();
    
    private:
        // Member variables_
        std::pair<int,int> grid_dim_; // grid dimensions
        std::vector<std::vector<int>> grid_; //grid at current timestep
        std::vector<std::vector<int>> next_grid_; //grid at next timestep

        int logevery_;
        int logsleep_;
        bool logtofile_;
        std::string logfile_;

        // Member functions
        int count_live_neighbors(int x, int y); // Counts live neighbors of cell (x, y)
};

}

#endif