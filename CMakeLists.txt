cmake_minimum_required(VERSION 3.5.0)
project(mystique)


add_executable(mystique ./src/main.c ./src/lib.c )


target_link_directories(mystique PRIVATE include/)
target_include_directories(mystique PRIVATE include/)
target_link_libraries(mystique PRIVATE ${CMAKE_SOURCE_DIR}/include/discord_game_sdk.dylib)

# Tests
enable_testing()
add_test(NAME version COMMAND mystique --version)
add_test(NAME help COMMAND mystique --help)
