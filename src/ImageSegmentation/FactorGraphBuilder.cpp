#include "FactorGraphBuilder.hpp"
#include <iostream>

FactorGraph FactorGraphBuilder::buildGraph(const CImg<unsigned char>& img, double J, double th_min, double th_max, double scale, double pbg, CImg<unsigned char>& evidence) {
    size_t dimx = img.width();
    size_t dimy = img.height();
    size_t N = dimx * dimy;
    vars.resize(N);  // Resize the vars vector to hold all variables
    std::vector<Factor> factors;

    for(size_t i = 0; i < N; i++) {
        vars[i] = Var(i, 2);
    }

    CImg<float> hist = img.get_channel(0).get_histogram(256, 0, 255);
    size_t cum_hist = 0;
    size_t level = 0;
    for(level = 0; level < 256; level++) {
        cum_hist += (size_t)hist(level);
        if(cum_hist > pbg * dimx * dimy / 100.0) break;
    }

    double th_avg = (th_min + th_max) / 2.0;
    double th_width = (th_max - th_min) / 2.0;

    factors.reserve(3 * N - dimx - dimy);
    for(size_t i = 0; i < dimx; i++) {
        for(size_t j = 0; j < dimy; j++) {
            size_t idx = i * dimy + j;
            if(i >= 1) factors.push_back(createFactorIsing(vars[idx], vars[(i-1)*dimy+j], J));
            if(j >= 1) factors.push_back(createFactorIsing(vars[idx], vars[i*dimy+(j-1)], J));
            double x = img(i, j);
            double th = th_avg + th_width * tanh((x - level) / scale);
            factors.push_back(createFactorIsing(vars[idx], th));
            unsigned char g = (unsigned char)((tanh(th) + 1.0) / 2.0 * 255.0);
            evidence(i, j, 0, 0) = g > 127 ? 255 : 0;
            evidence(i, j, 0, 1) = g > 127 ? 2 * (g - 127) : 0;
            evidence(i, j, 0, 2) = g > 127 ? 2 * (g - 127) : 2 * g;
        }
    }

    return FactorGraph(factors.begin(), factors.end(), vars.begin(), vars.end(), factors.size(), vars.size());
}