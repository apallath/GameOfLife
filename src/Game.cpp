/*
 * TODO: File I/O
 * TODO: stdout -> OpenGL
 */
#include "Game.h"

namespace gol = GameOfLife;

gol::Game::Game(int n_x, int n_y){
    std::cout << "Creating simulation on grid of size (" << n_x << ", " << n_y << ")\n";

    //Initialize grids with zeros
    grid_dim_ = std::pair<int,int>(n_x, n_y); 
    grid_.assign(n_x, std::vector<int>(n_y, 0));
    next_grid_.assign(n_x, std::vector<int>(n_y, 0));
}

void gol::Game::read_state(std::string infile){
    std::cout << "Reading state from " << infile << "\n";
    //TODO
}

void gol::Game::init_random_state(){
    std::cout << "Initializing random state\n";

    //Fill grids with random 0 or 1
    srand(time(NULL)); //seed
    for(int x = 0; x < grid_dim_.first; x++){
        for(int y = 0; y < grid_dim_.second; y++){
            grid_[x][y] = (int) rand() % 2;
        }
    }

    //Log initial state
    if(logtofile_){
        write_state(0, logfile_);
    }
    else{
        print_state(0);
    }
}

void gol::Game::write_state(int tstep, std::string outfile){
    std::cout << "Writing state at " << tstep << " to " << outfile << "\n";
    //TODO
}

void gol::Game::print_state(int tstep) {
    //Print state to stdout
    std::cout << tstep << "\n";
    for(int x = 0; x < grid_dim_.first; x++){
        for(int y = 0; y < grid_dim_.second; y++){
            if(grid_[x][y] == 1){
                std::cout << "*";
            }
            else{
                std::cout << "-";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void gol::Game::setup(int logevery, bool logtofile, std::string logfile){
    logevery_ = logevery;
    logtofile_ = logtofile;
    logfile_ = logfile;
}

/*
 * Core logic:
 * Cells: dead (0) or alive (1)
 * Neighbors: 8 neighboring positions, periodic boundary conditions.
 * Rules:
 * 1. Any live cell with two or three live neighbors lives.
 * 2. Any dead cell with three live neighbors becomes a live cell.
 * 3. All other live cells die. All other dead cells remain dead.\
 */

void gol::Game::run(int nsteps){
    std::cout << "Running for " << nsteps << "\n";
    //Begin code here
    int tstep = 0;

    while(tstep < nsteps){
        //Update grid
        for(int x = 0; x < grid_dim_.first; x++){
            for(int y = 0; y < grid_dim_.second; y++){
                int neigh_ct = count_live_neighbors(x, y);
                if(grid_[x][y] == 1 and (neigh_ct == 2 or neigh_ct == 3)){
                    next_grid_[x][y] = 1; //cell lives
                }
                else if(grid_[x][y] == 0 and neigh_ct == 3){
                    next_grid_[x][y] = 1; //cell lives
                }
                else{
                    next_grid_[x][y] = 0; //cell dies
                }
            }
        }
        grid_ = next_grid_;

        //Update timestep
        tstep++;

        //Log
        if(tstep % logevery_ == 0){
            if(logtofile_){
                write_state(tstep, logfile_);
            }
            else{
                print_state(tstep);
            }
        }
    }
}

int gol::Game::count_live_neighbors(int x, int y){
    int count = 0;

    int x_m_1 = ((x - 1) + grid_dim_.first) % grid_dim_.first;
    int x_p_1 = ((x + 1) + grid_dim_.first) % grid_dim_.first;
    int y_m_1 = ((y - 1) + grid_dim_.second) % grid_dim_.second;
    int y_p_1 = ((y + 1) + grid_dim_.second) % grid_dim_.second;

    count += grid_[x_m_1][y];
    count += grid_[x_p_1][y];
    count += grid_[x][y_m_1];
    count += grid_[x][y_p_1];
    count += grid_[x_m_1][y_m_1];
    count += grid_[x_m_1][y_p_1];
    count += grid_[x_p_1][y_m_1];
    count += grid_[x_p_1][y_p_1];

    return count;
}

gol::Game::~Game(){
    std::cout << "Destroying simulation\n";
    //Begin code here
}