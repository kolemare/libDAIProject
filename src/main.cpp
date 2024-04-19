#include "ImageSegmentation/ImageProcessor.hpp"
#include "ImageSegmentation/FactorGraphBuilder.hpp"
#include "ImageSegmentation/InferenceSolver.hpp"
#include <CImg.h>
using namespace cimg_library;

int main(int argc, char** argv) {
    ImageProcessor ip;
    FactorGraphBuilder fgb;
    InferenceSolver is;

    CImg<unsigned char> img1 = ip.readImage("input_image.jpg");
    CImg<unsigned char> evidence(img1.width(), img1.height(), 1, 3);

    FactorGraph fg = fgb.buildGraph(img1, 2.4, -3.0, 3.2, 40.0, 90.0, evidence);
    const std::vector<Var>& vars = fgb.getVars();  // Retrieve variables from builder

    CImgDisplay disp;
    double finalDiff = is.runInference(fg, "BP[updates=SEQMAX,maxiter=100,tol=1e-9]", 100, 1e-9, disp, evidence, vars);

    std::cout << "Final difference: " << finalDiff << std::endl;

    return 0;
}