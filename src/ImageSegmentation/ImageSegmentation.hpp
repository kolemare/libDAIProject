#include "Settings.hpp"
#include "ImageProcessor.hpp"
#include "FactorGraphBuilder.hpp"
#include "InferenceSolver.hpp"
#include <CImg.h>
using namespace cimg_library;
using namespace std;

/**
 * @class ImageSegmentation
 * @brief Class to handle image segmentation processes using factor graphs and inference techniques.
 *
 * This class encapsulates the entire process of segmenting an image based on differences between two images.
 * It utilizes factor graphs to model the problem and applies inference methods to segment the images.
 * The class is designed to be used as a callable object, allowing it to be invoked easily where needed.
 */
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