#include "Driver.h"

namespace po = boost::program_options;
namespace gol = GameOfLife;

gol::Driver::Driver(std::string cfgfile){
    po::options_description config("Configuration");
    po::variables_map vm;

    //Available options
    config.add_options()
        ("n_x", po::value<int>())
        ("n_y", po::value<int>())
        ("random_init", po::value<bool>()->default_value(true))
        ("init_file", po::value<std::string>()->default_value(""))
        ("log_every", po::value<int>()->default_value(1))
        ("log_to_file", po::value<bool>()->default_value(false))
        ("log_file", po::value<std::string>()->default_value(""))
        ("run", po::value<int>(&cfg_run));
    
    //Read file
    std::ifstream cfgstream(cfgfile, std::ios::in);
    po::store(po::parse_config_file(cfgstream, config, true), vm);

    //Create and setup game
    game = new Game(vm["n_x"].as<int>(), vm["n_y"].as<int>());

    if(vm["random_init"].as<bool>()){
        game->init_random_state();
    }
    else{
        game->read_state(vm["init_file"].as<std::string>());
    }

    game->setup(vm["log_every"].as<int>(), vm["log_to_file"].as<bool>(), vm["log_file"].as<std::string>());

    //Set run
    cfg_run = vm["run"].as<int>();
}

