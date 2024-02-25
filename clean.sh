#!/bin/bash

# Function to revert libDAI to original state
revert_libDAI() {
    echo "Reverting libDAI to original state..."
    cd libDAI || exit
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

# Delete build files in root folder
delete_build_files

echo -e "\e[94mCleanup completed successfully.\e[0m"