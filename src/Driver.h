/**
 * Parses configuration file and creates a Game object.
 */
#include <fstream>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <stdlib.h>
#include "Game.h"

namespace GameOfLife{

/*! Driver to create Game object from configuration file. */
class Driver{
    public:
        /**
         * Constructor.
         * @param cfgfile Configuration file.
         */
        Driver(std::string cfgfile);
        
        /*! Pointer to Game object created as per configuration file. */
        Game* game;

        /*! How long to run the game for, as per configuration file. */
        int cfg_run;
};

}