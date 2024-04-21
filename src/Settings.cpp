#include "Settings.hpp"

// Initialize static member variables
const char *Settings::file_i1 = nullptr;
const char *Settings::file_i2 = nullptr;
const char *Settings::file_o1 = nullptr;
const char *Settings::file_o2 = nullptr;
const char *Settings::belief = nullptr;
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

    // Parse operation
    const char *operation_str = cimg_option("-op", "ImageSegmentation", "Operation type");
    if (strcmp(operation_str, "ImageSegmentation") == 0)
        operation = Operation::ImageSegmentation;
    else if (strcmp(operation_str, "OptionB") == 0)
        operation = Operation::OptionB;
    else if (strcmp(operation_str, "OptionC") == 0)
        operation = Operation::OptionC;
}