cmake_minimum_required(VERSION 3.5.0)
project(mystique)
add_executable(mystique ./src/main.c ./src/lib.c)

# Tests
enable_testing()
add_test(NAME version COMMAND mystique --version)
add_test(NAME help COMMAND mystique --help)
