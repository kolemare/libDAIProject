#ifndef SETTINGS_H
#define SETTINGS_H

#include <CImg.h>
using namespace cimg_library;

enum class Operation
{
    ImageSegmentation,
    Sprinkler,
    BP
};

/**
 * @class Settings
 * @brief Manages configuration settings for various modules within the application.
 *
 * This class contains static member variables that hold configuration settings such as file paths,
 * algorithm parameters, and operation modes. These settings are initialized from command-line arguments
 * using the CImg library functions. The class supports different operations such as Image Segmentation,
 * Sprinkler Bayesian network, and Bipartite Graph handling, each with its own set of configurations.
 */
class Settings
{
public:
    static const char *file_i1;
    static const char *file_i2;
    static const char *file_o1;
    static const char *file_o2;
    static const char *belief;
    static const char *bp_graphviz;
    static const char *sprinkler_fg;
    static double J;
    static double th_min;
    static double th_max;
    static double scale;
    static double pbg;
    static const char *infname;
    static size_t maxiter;
    static double tol;
    static const char *file_fg;
    static Operation operation;

    static void initialize(int argc, char **argv);
};

#endif // SETTINGS_H