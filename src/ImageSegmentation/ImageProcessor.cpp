#include "ImageProcessor.hpp"
#include <iostream>

CImg<unsigned char> ImageProcessor::readImage(const char* filename) {
    std::cout << "Reading image (" << filename << ")..." << std::endl;
    return CImg<unsigned char>(filename);
}

void ImageProcessor::displayImage(const CImg<unsigned char>& image, const char* title) {
    image.display(title);
}

CImg<float> ImageProcessor::calculateHistogram(const CImg<unsigned char>& image) {
    return image.get_channel(0).get_histogram(256, 0, 255);
}

CImg<int> ImageProcessor::constructDifferenceImage(const CImg<unsigned char>& img1, const CImg<unsigned char>& img2) {
    CImg<int> diffImage(img1);
    diffImage -= img2;
    diffImage.abs();
    return diffImage;
}

void ImageProcessor::normalizeDifferenceImage(CImg<int>& img, const CImg<unsigned char>& ref) {
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            int avg = 0;
            for (int c = 0; c < img.spectrum(); c++) {
                avg += ref(i, j, 0, c);
            }
            avg /= img.spectrum();
            img(i, j, 0, 0) /= (1.0 + avg / 255.0);
        }
    }
    img.normalize(0, 255);
}

void ImageProcessor::displayAndSaveEvidence(const CImg<unsigned char>& image, const char* title, const char* filename) {
    image.display(title);
    image.save_jpeg(filename, 100);
}