#include "ImageProcessor.hpp"
#include <iostream>

/**
 * @brief Reads an image from a file.
 *
 * This method loads an image from the specified file using the CImg library. It also prints a message
 * to the console indicating the file being read. This function assumes the image is stored in an unsigned
 * char format.
 *
 * @param filename Pointer to a char array containing the name of the file.
 * @return CImg<unsigned char> An image object loaded from the specified file.
 */
CImg<unsigned char> ImageProcessor::readImage(const char *filename)
{
    std::cout << "Reading image (" << filename << ")..." << std::endl;
    return CImg<unsigned char>(filename);
}

/**
 * @brief Displays an image with a given title.
 *
 * This method displays the provided image in a window with the specified title. It uses the display method
 * from the CImg library.
 *
 * @param image Constant reference to a CImg<unsigned char> object representing the image to be displayed.
 * @param title Pointer to a char array containing the title of the window.
 */
void ImageProcessor::displayImage(const CImg<unsigned char> &image, const char *title)
{
    image.display(title);
}

/**
 * @brief Calculates the histogram of an image.
 *
 * This method computes the histogram of the image's first channel (assumed to be grayscale) using 256 bins
 * covering the range from 0 to 255. It returns the histogram as a CImg<float> object.
 *
 * @param image Constant reference to a CImg<unsigned char> object representing the image.
 * @return CImg<float> Histogram of the image.
 */
CImg<float> ImageProcessor::calculateHistogram(const CImg<unsigned char> &image)
{
    return image.get_channel(0).get_histogram(256, 0, 255);
}

/**
 * @brief Constructs a difference image between two images.
 *
 * This method calculates the absolute difference between two given images pixel by pixel and returns the
 * resulting difference image. This can be used to highlight changes between two images of the same size.
 *
 * @param img1 Constant reference to a CImg<unsigned char> representing the first image.
 * @param img2 Constant reference to a CImg<unsigned char> representing the second image.
 * @return CImg<int> Difference image calculated from the two input images.
 */
CImg<int> ImageProcessor::constructDifferenceImage(const CImg<unsigned char> &img1, const CImg<unsigned char> &img2)
{
    CImg<int> diffImage(img1);
    diffImage -= img2;
    diffImage.abs();
    return diffImage;
}

/**
 * @brief Normalizes a difference image based on a reference image.
 *
 * This method adjusts the intensity of a difference image based on the average intensity of a reference image.
 * It performs normalization such that regions with higher intensity in the reference have less pronounced
 * differences.
 *
 * @param img Reference to a CImg<int> object representing the difference image to be normalized.
 * @param ref Constant reference to a CImg<unsigned char> representing the reference image.
 */
void ImageProcessor::normalizeDifferenceImage(CImg<int> &img, const CImg<unsigned char> &ref)
{
    for (int i = 0; i < img.width(); i++)
    {
        for (int j = 0; j < img.height(); j++)
        {
            int avg = 0;
            for (int c = 0; c < img.spectrum(); c++)
            {
                avg += ref(i, j, 0, c);
            }
            avg /= img.spectrum();
            img(i, j, 0, 0) /= (1.0 + avg / 255.0);
        }
    }
    img.normalize(0, 255);
}

/**
 * @brief Displays and saves an image.
 *
 * This method displays an image with the specified title and saves it to a file in JPEG format with a quality
 * of 100. The method prints both actions to the console for traceability.
 *
 * @param image Constant reference to a CImg<unsigned char> object representing the image.
 * @param title Pointer to a char array containing the title of the window in which the image is displayed.
 * @param filename Pointer to a char array containing the name of the file to save the image.
 */
void ImageProcessor::displayAndSaveEvidence(const CImg<unsigned char> &image, const char *title, const char *filename)
{
    image.display(title);
    image.save_jpeg(filename, 100);
}