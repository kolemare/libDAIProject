#include "BipartiteGraph/BipartiteGraphHandler.hpp"
#include "ImageSegmentation/ImageSegmentation.hpp"
#include "Sprinkler/Sprinkler.hpp"

/**
 * @file main.cpp
 * @brief Main entry point for a multi-module application demonstrating various functionalities.
 *
 * This program initializes settings from command line arguments and executes one of several operations
 * based on those settings. The operations include image segmentation, a Sprinkler Bayesian network simulation,
 * and handling of a bipartite graph. Each operation is encapsulated in its own class and is executed depending
 * on the user-specified option. This approach demonstrates modularity and the use of command line parameters
 * to control application behavior.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Returns 0 upon successful execution, signaling normal program termination.
 */
int main(int argc, char **argv)
{
    Settings::initialize(argc, argv);

    // Now Settings::operation will have the value specified by the command line argument
    switch (Settings::operation)
    {
    case Operation::ImageSegmentation:
        ImageSegmentation imageSegmentation;
        imageSegmentation();
        break;
    case Operation::Sprinkler:
        Sprinkler sprinkler;
        sprinkler();
        break;
    case Operation::BP:
        BipartiteGraphHandler handler;
        handler();
        break;
    }

    // Proceed with the rest of your application logic
    return 0;
}