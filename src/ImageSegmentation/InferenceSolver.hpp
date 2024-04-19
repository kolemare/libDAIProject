#ifndef INFERENCE_SOLVER_HPP
#define INFERENCE_SOLVER_HPP

#include <dai/factorgraph.h>
#include <dai/alldai.h>
#include <CImg.h>
using namespace dai;
using namespace cimg_library;

class InferenceSolver {
public:
    double runInference(FactorGraph& fg, const std::string& options, size_t maxIter, double tol, CImgDisplay& disp, CImg<unsigned char>& image, const std::vector<dai::Var>& vars);
};

#endif
