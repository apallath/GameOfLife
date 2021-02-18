#include "Game.h"

namespace gol = GameOfLife;

gol::Game::Game(int n_rows, int n_cols){
    std::cout << "Creating simulation on grid of size (" << n_rows << ", " << n_cols << ")\n";

    grid_dim_ = std::pair<int,int>(n_rows, n_cols); 

    //Initialize grids with zeros
    grid_.assign(n_rows, std::vector<int>(n_cols, 0));
    next_grid_.assign(n_rows, std::vector<int>(n_cols, 0));
}

void gol::Game::read_state(std::string infile){
    std::cout << "Reading state from " << infile << "\n";
    
    //Read from file and fill vector
    std::ifstream infstr(infile);

    if(infstr.is_open()) {
        for(int x = 0; x < grid_dim_.first; x++){
            for(int y = 0; y < grid_dim_.second; y++){
                infstr >> grid_[x][y];
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
    else{
        std::cerr << "File " << infile << " could not be opened. No such file or directory.";
        abort();
    }
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

    std::ofstream outstr;
    if(tstep == 0){
        outstr.open(outfile, std::ofstream::trunc);
    }
    else{
        outstr.open(outfile, std::ofstream::app);
    }
    
    if(outstr.is_open()) {
        outstr << tstep << "\n";
        for(int x = 0; x < grid_dim_.first; x++){
            for(int y = 0; y < grid_dim_.second; y++){
                outstr << grid_[x][y];
            }
            outstr << "\n";
        }
        outstr << "\n";
    }
    else{
        std::cerr << "File " << outfile << " could not be opened.";
        abort();
    }
}

void gol::Game::print_state(int tstep) {
    //Clear terminal output
    printf("\033[2J\033[1;1H");

    std::cout << tstep << "\n";
    for(int x = 0; x < grid_dim_.first; x++){
        for(int y = 0; y < grid_dim_.second; y++){
            if(grid_[x][y] == 1){
                std::cout << "\u2588";
            }
            else{
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    if(tstep == 0){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    else{
        std::this_thread::sleep_for(std::chrono::milliseconds(logsleep_));
    }
}

void gol::Game::setup(int logevery, int logsleep, bool logtofile, std::string logfile){
    logevery_ = logevery;
    logsleep_ = logsleep;
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
    int tstep = 0;

    while(tstep < nsteps){
        
        #pragma omp parallel
        {
            //Update next_grid
            #pragma omp for
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

            #pragma omp barrier

            //Copy grid
            #pragma omp for
            for(int x = 0; x < grid_dim_.first; x++){
                for(int y = 0; y < grid_dim_.second; y++){
                    grid_[x][y] = next_grid_[x][y];
                }
            }
        }

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