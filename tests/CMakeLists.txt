file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build/)

# Run random test
add_test(NAME random_run COMMAND GameOfLife random.cfg
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Run blinker test
add_test(NAME blinker COMMAND GameOfLife blinker.cfg
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Compare blinker output to gold standard output
add_test(NAME blinker_compare COMMAND ${CMAKE_COMMAND} -E compare_files blinker.out build/blinker.out
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Run block test
add_test(NAME block COMMAND GameOfLife block.cfg
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Compare blinker output to gold standard output
add_test(NAME block_compare COMMAND ${CMAKE_COMMAND} -E compare_files block.out build/block.out
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Run beehive test
add_test(NAME beehive COMMAND GameOfLife beehive.cfg
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Compare beehive output to gold standard output
add_test(NAME beehive_compare COMMAND ${CMAKE_COMMAND} -E compare_files beehive.out build/beehive.out
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})