#ifndef IMAGE_PROCESSOR_HPP
#define IMAGE_PROCESSOR_HPP

#include <CImg.h>
using namespace cimg_library;

/**
 * @class ImageProcessor
 * @brief Provides functionalities for reading, displaying, and processing images.
 *
 * This class utilizes the CImg library to handle various image processing operations,
 * such as reading images from files, displaying images, calculating histograms,
 * constructing difference images, normalizing images, and saving images after displaying.
 */
class ImageProcessor
{
public:
    CImg<unsigned char> readImage(const char *filename);
    void displayImage(const CImg<unsigned char> &image, const char *title);
    CImg<float> calculateHistogram(const CImg<unsigned char> &image);
    CImg<int> constructDifferenceImage(const CImg<unsigned char> &img1, const CImg<unsigned char> &img2);
    void normalizeDifferenceImage(CImg<int> &img, const CImg<unsigned char> &ref);
    void displayAndSaveEvidence(const CImg<unsigned char> &image, const char *title, const char *filename);
};

#endif
