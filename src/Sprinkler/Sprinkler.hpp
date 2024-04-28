#ifndef SPRINKLER_HPP
#define SPRINKLER_HPP

#include "Settings.hpp"
#include <dai/factorgraph.h>
#include <dai/var.h>
#include <dai/factor.h>

namespace dai
{
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