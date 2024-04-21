#include "InferenceSolver.hpp"
#include <iostream>
#include <vector>

double InferenceSolver::runInference(FactorGraph &fg, std::string algOpts, size_t maxIter, double tol, std::vector<double> &m, size_t dimx, size_t dimy, CImgDisplay &disp)
{
    // Construct inference algorithm
    cout << "Inference algorithm: " << algOpts << endl;
    cout << "Constructing inference algorithm object..." << endl;
    InfAlg *ia = newInfAlgFromString(algOpts, fg);

    // Initialize inference algorithm
    cout << "Initializing inference algorithm..." << endl;
    ia->init();

    // Initialize vector for storing the magnetizations
    m = vector<double>(fg.nrVars(), 0.0);

    // Construct an image that will hold the intermediate single-variable beliefs
    CImg<unsigned char> image(dimx, dimy, 1, 3);

    // maxDiff stores the current convergence level
    double maxDiff = 1.0;

    // Iterate while maximum number of iterations has not been
    // reached and requested convergence level has not been reached
    cout << "Starting inference algorithm..." << endl;

    for (size_t iter = 0; iter < maxIter && maxDiff > tol; iter++)
    {
        // Set magnetizations to beliefs
        for (size_t i = 0; i < fg.nrVars(); i++)
        {
            m[i] = ia->beliefV(i)[1] - ia->beliefV(i)[0];
        }

        // For each pixel, calculate a color coded magnetization
        // and store it in the image for visualization
        for (size_t i = 0; i < dimx; i++)
            for (size_t j = 0; j < dimy; j++)
            {
                unsigned char g = (unsigned char)((m[i * dimy + j] + 1.0) / 2.0 * 255.0);
                if (g > 127)
                {
                    image(i, j, 0) = 255;
                    image(i, j, 1) = 2 * (g - 127);
                    image(i, j, 2) = 2 * (g - 127);
                }
                else
                {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 2 * g;
                }
            }

        // Display the image with the current beliefs
        disp = image;
        std::string filename = std::string(Settings::belief) + std::to_string(iter) + ".jpg";

        // Convert the filename to const char* for the CImg function
        const char *filename_c_str = filename.c_str();
        image.save_jpeg(filename_c_str, 100);

        // Perform the requested inference algorithm for only one step
        ia->setMaxIter(iter + 1);
        maxDiff = ia->run();

        // Output progress
        cout << " Iterations = " << iter << ", maxDiff = " << maxDiff << endl;
    }

    cout << "Finished inference algorithm" << endl;

    // Clean up inference algorithm
    delete ia;

    // Return reached convergence level
    return maxDiff;
}
