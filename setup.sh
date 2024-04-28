#!/bin/bash

# Update Git submodules recursively
git submodule update --init --recursive

# Install required packages using apt-get
sudo apt-get update
sudo apt-get install -y g++ make doxygen graphviz libboost-dev libboost-graph-dev libboost-program-options-dev libboost-test-dev libgmp-dev cimg-dev imagemagick libmagickcore-dev libharfbuzz-dev texlive-latex-extra