#ifndef INFERENCE_SOLVER_HPP
#define INFERENCE_SOLVER_HPP

#include "Settings.hpp"
#include <dai/factorgraph.h>
#include <dai/alldai.h>
#include <CImg.h>
using namespace dai;
using namespace cimg_library;
using namespace std;

/**
 * @class InferenceSolver
 * @brief Class designed to handle the inference process on factor graphs using various algorithms.
 *
 * This class encapsulates methods for running inference algorithms on factor graphs to solve problems
 * such as image segmentation. It utilizes the libDAI library for managing the factor graphs and inference
 * algorithms, and the CImg library for displaying the results. The class provides a method to run the
 * inference, visualize the process, and output the results.
 */
class InferenceSolver
{
public:
    double runInference(FactorGraph &fg, std::string algOpts, size_t maxIter, double tol, std::vector<double> &m, size_t dimx, size_t dimy, CImgDisplay &disp);
};

#endif
