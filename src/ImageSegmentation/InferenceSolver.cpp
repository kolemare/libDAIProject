#include "InferenceSolver.hpp"
#include <iostream>
#include <vector>

double InferenceSolver::runInference(dai::FactorGraph& fg, const std::string& options, size_t maxIter, double tol, cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& image, const std::vector<dai::Var>& vars) {
    dai::InfAlg* solver = dai::newInfAlgFromString(options, fg);
    solver->init();
    std::vector<double> beliefs(fg.nrVars(), 0.0);
    double maxDiff = 1.0;
    size_t dimx = image.width();
    size_t dimy = image.height();

    for (size_t iter = 0; iter < maxIter && maxDiff > tol; iter++) {
        solver->setMaxIter(iter + 1);
        maxDiff = solver->run();
        for(size_t i = 0; i < dimx; i++) {
            for(size_t j = 0; j < dimy; j++) {
                size_t idx = i * dimy + j;
                double m = solver->beliefV(idx)[1] - solver->beliefV(idx)[0];
                unsigned char g = (unsigned char)((m + 1.0) / 2.0 * 255.0);
                image(i, j, 0, 0) = g;
                image(i, j, 0, 1) = g;
                image(i, j, 0, 2) = g;
            }
        }
        disp.display(image);
        std::cout << "Iterations = " << iter << ", maxDiff = " << maxDiff << std::endl;
    }
    delete solver;
    return maxDiff;
}
