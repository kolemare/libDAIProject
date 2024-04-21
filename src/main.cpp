#include "ImageSegmentation/ImageSegmentation.hpp"

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
    case Operation::OptionB:
        // Handle Option B
        break;
    case Operation::OptionC:
        // Handle Option C
        break;
    }

    // Proceed with the rest of your application logic
    return 0;
}