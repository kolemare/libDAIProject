#ifndef INFERENCE_SOLVER_HPP
#define INFERENCE_SOLVER_HPP

#include "Settings.hpp"
#include <dai/factorgraph.h>
#include <dai/alldai.h>
#include <CImg.h>
using namespace dai;
using namespace cimg_library;
using namespace std;

class InferenceSolver
{
public:
    double runInference(FactorGraph &fg, std::string algOpts, size_t maxIter, double tol, std::vector<double> &m, size_t dimx, size_t dimy, CImgDisplay &disp);
};

#endif
