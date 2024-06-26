#include "Settings.hpp"

// Initialize static member variables
const char *Settings::file_i1 = nullptr;
const char *Settings::file_i2 = nullptr;
const char *Settings::file_o1 = nullptr;
const char *Settings::file_o2 = nullptr;
const char *Settings::belief = nullptr;
const char *Settings::bp_graphviz = nullptr;
const char *Settings::sprinkler_fg = nullptr;
double Settings::J = 0.0;
double Settings::th_min = 0.0;
double Settings::th_max = 0.0;
double Settings::scale = 0.0;
double Settings::pbg = 0.0;
const char *Settings::infname = nullptr;
size_t Settings::maxiter = 0;
double Settings::tol = 0.0;
const char *Settings::file_fg = nullptr;
Operation Settings::operation = Operation::ImageSegmentation;

/**
 * @brief Initializes settings from command-line arguments.
 *
 * This method parses command-line arguments to set up various configuration parameters for the application.
 * It uses the CImg library's command-line parsing utility to extract values for each setting. The method
 * supports switching between different operations and adjusts settings accordingly based on the provided
 * arguments.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void Settings::initialize(int argc, char **argv)
{
    file_i1 = cimg_option("-i1", "example_img_in1.jpg", "Input image 1");
    file_i2 = cimg_option("-i2", "example_img_in2.jpg", "Input image 2");
    file_o1 = cimg_option("-o1", "local_evidence.jpg", "Output image (local evidence)");
    file_o2 = cimg_option("-o2", "magnetizations.jpg", "Output image (magnetizations)");
    J = cimg_option("-J", 2.4, "Pairwise interaction strength");
    th_min = cimg_option("-thmin", -3.0, "Local evidence strength of background");
    th_max = cimg_option("-thmax", 3.2, "Local evidence strength of foreground");
    scale = cimg_option("-scale", 40.0, "Scale of pixel values");
    pbg = cimg_option("-pbg", 90.0, "Percentage of background in image");
    infname = cimg_option("-method", "BP[updates=SEQMAX,maxiter=1,tol=1e-9,logdomain=0]", "Inference method");
    maxiter = cimg_option("-maxiter", 100, "Maximum number of iterations");
    tol = cimg_option("-tol", 1e-9, "Tolerance level for inference method");
    file_fg = cimg_option("-fg", "", "Output factor graph file");
    belief = cimg_option("-blf", "", "Name of belief files");
    bp_graphviz = cimg_option("-bpg", "", "Graphviz Bipartite graph output");
    sprinkler_fg = cimg_option("-spfg", "", "Sprinkler factor graph output");

    // Parse operation
    const char *operation_str = cimg_option("-op", "ImageSegmentation", "Operation type");
    if (strcmp(operation_str, "ImageSegmentation") == 0)
        operation = Operation::ImageSegmentation;
    else if (strcmp(operation_str, "Sprinkler") == 0)
        operation = Operation::Sprinkler;
    else if (strcmp(operation_str, "BP") == 0)
        operation = Operation::BP;
}