#!/bin/bash

# Function to revert libDAI to original state
revert_libDAI() {
    echo "Reverting libDAI to original state..."
    cd libDAI || exit
    git clean -xdf
    cd ..
}

# Function to revert graphviz to original state
revert_graphviz() {
    echo "Reverting graphviz to original state..."
    cd graphviz || exit
    git clean -xdf
    cd ..
}

# Function to delete build files in root folder
delete_build_files() {
    echo "Deleting build files in root folder..."
    make clean
}

# Revert libDAI to original state
revert_libDAI

# Revert graphviz to original state
revert_graphviz

# Delete build files in root folder
delete_build_files

git submodule foreach --recursive 'git reset --hard && git clean -fdx'

echo -e "\e[94mCleanup completed successfully.\e[0m"