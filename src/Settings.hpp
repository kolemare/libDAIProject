#ifndef SETTINGS_H
#define SETTINGS_H

#include <CImg.h>
using namespace cimg_library;

enum class Operation
{
    ImageSegmentation,
    OptionB,
    OptionC
};

class Settings
{
public:
    static const char *file_i1;
    static const char *file_i2;
    static const char *file_o1;
    static const char *file_o2;
    static const char *belief;
    static double J;
    static double th_min;
    static double th_max;
    static double scale;
    static double pbg;
    static const char *infname;
    static size_t maxiter;
    static double tol;
    static const char *file_fg;
    static Operation operation;

    static void initialize(int argc, char **argv);
};

#endif // SETTINGS_H