#ifndef FACTOR_GRAPH_BUILDER_HPP
#define FACTOR_GRAPH_BUILDER_HPP

#include <dai/factorgraph.h>
#include <CImg.h>
#include <vector>
using namespace dai;
using namespace cimg_library;

/**
 * @class FactorGraphBuilder
 * @brief A class to build factor graphs based on image data using the Ising model.
 *
 * This class provides functionality to construct a factor graph from a given image, where
 * each pixel's interaction is modeled using the Ising model. It allows for the adjustment
 * of interaction strength, threshold levels, and scaling factors to manipulate the model's
 * sensitivity to changes in pixel intensity.
 */
class FactorGraphBuilder
{
    std::vector<Var> vars; // To store the variables used in the factor graph
public:
    FactorGraph buildGraph(const CImg<unsigned char> &img, double J, double th_min, double th_max, double scale, double pbg, CImg<unsigned char> &evidence);
    const std::vector<Var> &getVars() const { return vars; } // Getter for variables
};

#endif
