#ifndef SPRINKLER_HPP
#define SPRINKLER_HPP

#include "Settings.hpp"
#include <dai/factorgraph.h>
#include <dai/var.h>
#include <dai/factor.h>

namespace dai
{
    /**
     * @class Sprinkler
     * @brief Implements a Bayesian network simulation of the Sprinkler example using factor graphs.
     *
     * This class encapsulates the functionality to simulate the Sprinkler Bayesian network, commonly used in
     * probabilistic graphical models for teaching and demonstration purposes. The network includes variables
     * such as Cloudy, Sprinkler, Rain, and Wet Grass, with appropriate conditional probabilities. The class
     * uses the libDAI library for creating and manipulating factor graphs and provides a method to run the
     * entire simulation, which calculates various probabilities and outputs the results.
     */
    class Sprinkler
    {
    private:
        void runSprinkler();

    public:
        void operator()()
        {
            this->runSprinkler();
        }
    };
}

#endif // SPRINKLER_HPP