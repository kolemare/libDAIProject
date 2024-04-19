#ifndef FACTOR_GRAPH_BUILDER_HPP
#define FACTOR_GRAPH_BUILDER_HPP

#include <dai/factorgraph.h>
#include <CImg.h>
#include <vector>
using namespace dai;
using namespace cimg_library;

class FactorGraphBuilder {
    std::vector<Var> vars;  // To store the variables used in the factor graph
public:
    FactorGraph buildGraph(const CImg<unsigned char>& img, double J, double th_min, double th_max, double scale, double pbg, CImg<unsigned char>& evidence);
    const std::vector<Var>& getVars() const { return vars; }  // Getter for variables
};

#endif
