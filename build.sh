#!/bin/bash

# Function to show usage information
usage() {
    echo "Usage: $0 [--clean | --full]"
    echo "  --clean: Clean libDAI, Create Makefile config, Build libDAI, Clean application build, Build application."
    echo "  --full: Create Makefile config, Build libDAI, Clean application build, Build application."
    echo "    none: Clean application build, Build application."
    exit 1
}

# Function to clean libDAI git and revert to original state
clean_libDAI() {
    echo "Cleaning libDAI and reverting to original state..."
    cd libDAI || exit
    git clean -xdf
    git reset --hard
    git submodule update --init --recursive
    cd ..
}

# Function to clean graphviz git and revert to original state
clean_graphviz() {
    echo "Cleaning graphviz and reverting to original state..."
    cd graphviz || exit
    git clean -xdf
    git reset --hard
    git submodule update --init --recursive
    cd ..
}

# Function to modify Makefile
modify_makefile() {
    cd libDAI || exit
    echo "Modifying Makefile..."
    cp Makefile.LINUX Makefile.conf
    sed -i 's/BOOSTLIBS_PO=-lboost_program_options-mt/BOOSTLIBS_PO=-lboost_program_options/g' Makefile.conf
    sed -i 's/BOOSTLIBS_UTF=-lboost_unit_test_framework-mt/BOOSTLIBS_UTF=-lboost_unit_test_framework/g' Makefile.conf
    cd ..
}

build_graphviz() {
    echo "Building Graphviz..."
    cd graphviz || exit
    if [ ! -d "build" ]; then
        mkdir -p build
        cd build || exit
        cmake ..
    else
        cd build || exit
    fi
    make
    cd ../..
}

# Check number of arguments
if [[ $# -gt 2 ]]; then
    usage
fi

# Check for valid argument combinations
if [[ $# -eq 2 && ($1 != "--clean" || $2 != "--full") && ($1 != "--full" || $2 != "--clean") ]]; then
    usage
fi

# Handle different combinations of arguments
if [[ $# -eq 0 ]]; then
    # No arguments provided
    echo "Building application only."
    # If no arguments are provided, shouldn't we still build Graphviz?
    build_graphviz
elif [[ ($1 == "--clean" && $2 == "--full") || ($1 == "--full" && $2 == "--clean") ]]; then
    # Clean and full arguments provided in any order
    clean_libDAI
    clean_graphviz
    modify_makefile
    build_graphviz  # Moved here to ensure clean start for full build
    echo "Building libDAI..."
    cd libDAI || exit
    make
    cd ..
elif [[ $1 == "--clean" ]]; then
    # Only clean argument provided
    clean_libDAI
    clean_graphviz
    modify_makefile
    build_graphviz
    echo "Building libDAI..."
    cd libDAI || exit
    make
    cd ..
elif [[ $1 == "--full" ]]; then
    # Only full argument provided
    modify_makefile
    build_graphviz
    echo "Building libDAI..."
    cd libDAI || exit
    make
    cd ..
fi

# Build the main application
make clean
make

# Check the exit status of the make command
if [ $? -ne 0 ]; then
    echo -e "\e[91mBuild failed. Make sure you run the build.sh with --full if building for the first time or if libDAI isn't built yet.\e[0m"
else
    echo -e "\e[94mBuild completed successfully.\e[0m"
fi