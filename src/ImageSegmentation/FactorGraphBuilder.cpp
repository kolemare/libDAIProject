#include "FactorGraphBuilder.hpp"
#include <iostream>

/**
 * @brief Builds a factor graph from a given image using specified parameters.
 *
 * This method constructs a factor graph that models the relationship between image pixels
 * and their intensity transformations based on the Ising model. The graph is built by
 * defining variables and factors that represent binary states and their pairwise relationships,
 * respectively. It also computes an evidence image that highlights significant intensity
 * transitions based on the threshold level derived from the pixel intensities histogram.
 *
 * @param img Reference to a CImg<unsigned char> object representing the input image.
 * @param J Coupling constant of the Ising model representing interaction strength between pixels.
 * @param th_min Minimum threshold for the factor intensity.
 * @param th_max Maximum threshold for the factor intensity.
 * @param scale Scaling factor used in the hyperbolic tangent function for threshold calculation.
 * @param pbg Percentage of background pixels used to determine the histogram threshold.
 * @param evidence Reference to a CImg<unsigned char> object to store the evidence image showing significant transitions.
 * @return FactorGraph An object representing the constructed factor graph.
 */
FactorGraph FactorGraphBuilder::buildGraph(const CImg<unsigned char> &img, double J, double th_min, double th_max, double scale, double pbg, CImg<unsigned char> &evidence)
{
    std::vector<Var> vars; // Instead of resizing and then assigning, we'll push back new Var objects as in the original code
    std::vector<Factor> factors;

    size_t dimx = img.width();
    size_t dimy = img.height();
    size_t N = dimx * dimy;
    vars.reserve(N); // Reserve the needed space to avoid reallocations

    for (size_t i = 0; i < N; i++)
    {
        vars.push_back(Var(i, 2)); // Push new Var objects into vars
    }

    CImg<float> hist = img.get_channel(0).get_histogram(256, 0, 255);
    size_t cum_hist = 0;
    size_t level = 0;
    for (level = 0; level < 256; level++)
    {
        cum_hist += (size_t)hist(level);
        if (cum_hist > pbg * dimx * dimy / 100.0)
        {
            break;
        }
    }

    factors.reserve(3 * N - dimx - dimy);

    double th_avg = (th_min + th_max) / 2.0;
    double th_width = (th_max - th_min) / 2.0;

    for (size_t i = 0; i < dimx; i++)
    {
        for (size_t j = 0; j < dimy; j++)
        {
            size_t idx = i * dimy + j;
            if (i >= 1)
                factors.push_back(createFactorIsing(vars[idx], vars[(i - 1) * dimy + j], J));
            if (j >= 1)
                factors.push_back(createFactorIsing(vars[idx], vars[i * dimy + (j - 1)], J));
            double x = img(i, j);
            double th = th_avg + th_width * tanh((x - level) / scale);
            factors.push_back(createFactorIsing(vars[idx], th));
            unsigned char g = (unsigned char)((tanh(th) + 1.0) / 2.0 * 255.0);
            if (g > 127)
            {
                evidence(i, j, 0) = 255;
                evidence(i, j, 1) = 2 * (g - 127);
                evidence(i, j, 2) = 2 * (g - 127);
            }
            else
            {
                evidence(i, j, 0) = 0;
                evidence(i, j, 1) = 0;
                evidence(i, j, 2) = 2 * g;
            }
        }
    }

    return FactorGraph(factors.begin(), factors.end(), vars.begin(), vars.end(), factors.size(), vars.size());
}