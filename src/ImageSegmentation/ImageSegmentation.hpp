#include "Settings.hpp"
#include "ImageProcessor.hpp"
#include "FactorGraphBuilder.hpp"
#include "InferenceSolver.hpp"
#include <CImg.h>
using namespace cimg_library;
using namespace std;

class ImageSegmentation
{
private:
    void runImageSegmentation();

public:
    void operator()()
    {
        this->runImageSegmentation();
    }
};