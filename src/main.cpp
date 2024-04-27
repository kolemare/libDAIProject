#include "BipartiteGraph/BipartiteGraphHandler.hpp"
#include "ImageSegmentation/ImageSegmentation.hpp"
#include "Sprinkler/Sprinkler.hpp"

int main(int argc, char **argv)
{
    Settings::initialize(argc, argv);

    // Now Settings::operation will have the value specified by the command line argument
    switch (Settings::operation)
    {
    case Operation::ImageSegmentation:
        ImageSegmentation imageSegmentation;
        imageSegmentation();
        break;
    case Operation::Sprinkler:
        Sprinkler sprinkler;
        sprinkler();
        break;
    case Operation::BP:
        BipartiteGraphHandler handler;
        handler();
        break;
    }

    // Proceed with the rest of your application logic
    return 0;
}