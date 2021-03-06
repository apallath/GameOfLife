#include "Driver.h"

namespace po = boost::program_options;
namespace gol = GameOfLife;

gol::Driver::Driver(std::string cfgfile){
    po::options_description config("Configuration");
    po::variables_map vm;

    //Available options
    config.add_options()
        ("n_rows", po::value<int>())
        ("n_cols", po::value<int>())
        ("random_init", po::value<bool>()->default_value(true))
        ("init_file", po::value<std::string>()->default_value(""))
        ("log_every", po::value<int>()->default_value(1))
        ("log_sleep", po::value<int>()->default_value(0))
        ("log_to_file", po::value<bool>()->default_value(false))
        ("log_file", po::value<std::string>()->default_value(""))
        ("run", po::value<int>(&cfg_run));
    
    //Read file
    std::ifstream cfgstream(cfgfile, std::ios::in);
    if(cfgstream.is_open()){
        po::store(po::parse_config_file(cfgstream, config, true), vm);

        //Create and setup game
        game = new Game(vm["n_rows"].as<int>(), vm["n_cols"].as<int>());

        game->setup(vm["log_every"].as<int>(), vm["log_sleep"].as<int>(), vm["log_to_file"].as<bool>(), vm["log_file"].as<std::string>());

        if(vm["random_init"].as<bool>()){
            game->init_random_state();
        }
        else{
            game->read_state(vm["init_file"].as<std::string>());
        }

        //Set run
        cfg_run = vm["run"].as<int>();
    }
    else{
        std::cerr << "File " << cfgfile << " could not be opened. No such file or directory.";
        abort();
    }
}

