#include "ImageSegmentation.hpp"

void ImageSegmentation::runImageSegmentation()
{
    ImageProcessor ip;
    FactorGraphBuilder fgb;
    InferenceSolver is;

    cout << "Reading input image 1 (" << Settings::file_i1 << ")..." << endl;
    CImg<unsigned char> image1 = CImg<>(Settings::file_i1);
    cout << "Reading input image 2 (" << Settings::file_i2 << ")..." << endl;
    CImg<unsigned char> image2 = CImg<>(Settings::file_i2);

    // Check image sizes
    if ((image1.width() != image2.width()) || (image1.height() != image2.height()))
    {
        cerr << "Error: input images should have same size." << endl;
    }

    size_t dimx = image1.width();
    size_t dimy = image1.height();

    // Display input images
    cout << "Displaying input image 1..." << endl;
    CImgDisplay disp1(image1, "Input image 1", 0);
    cout << "Displaying input image 2..." << endl;
    CImgDisplay disp2(image2, "Input image 2", 0);

    // Construct absolute difference image
    cout << "Constructing difference image..." << endl;
    CImg<int> image3(image1);
    image3 -= image2;
    image3.abs();

    // Normalize difference image
    image3.norm(1); // 1 = L1, 2 = L2, -1 = Linf

    // Normalize the difference by the average value of the background image
    for (size_t i = 0; i < dimx; i++)
    {
        for (size_t j = 0; j < dimy; j++)
        {
            int avg = 0;
            image3(i, j, 0) /= (1.0 + avg / 255.0);
        }
    }
    image3.normalize(0, 255);

    // Display difference image
    cout << "Displaying difference image..." << endl;
    CImgDisplay disp3(image3, "Relative difference of both inputs", 0);

    // Convert difference image into a factor graph and store
    // the local evidence in image4 for visualization
    CImg<unsigned char> image4(dimx, dimy, 1, 3);

    cout << "Converting difference image into factor graph..." << endl;
    FactorGraph fg = fgb.buildGraph(image3, Settings::J, Settings::th_min, Settings::th_max, Settings::scale, Settings::pbg, image4);

    // Display local evidence
    cout << "Displaying local evidence..." << endl;
    CImgDisplay disp4(image4, "Local evidence", 0);

    cout << "Saving local evidence as JPEG in " << Settings::file_o1 << endl;
    image4.save_jpeg(Settings::file_o1, 100);
    if (strlen(Settings::file_fg) > 0)
    {
        cout << "Saving factor graph as " << Settings::file_fg << endl;
        fg.WriteToFile(Settings::file_fg);
    }
    // Solve the inference problem and visualize intermediate steps
    CImgDisplay disp5(dimx, dimy, "Beliefs during inference", 0);

    vector<double> m; // Stores the final magnetizations
    cout << "Solving the inference problem...please be patient!" << endl;

    is.runInference(fg, Settings::infname, Settings::maxiter, Settings::tol, m, dimx, dimy, disp5);
    // Visualize the final magnetizations
    for (size_t i = 0; i < dimx; i++)
        for (size_t j = 0; j < dimy; j++)
        {
            unsigned char g = (unsigned char)((m[i * dimy + j] + 1.0) / 2.0 * 255.0);
            if (g > 127)
            {
                image4(i, j, 0) = image2(i, j, 0);
                image4(i, j, 1) = image2(i, j, 1);
                image4(i, j, 2) = image2(i, j, 2);
            }
            else
            {
                for (size_t c = 0; c < (size_t)image4.spectrum(); c++)
                    image4(i, j, c) = 255;
            }
        }
    cout << "Displaying the final result of the segmentation problem..." << endl;
    CImgDisplay main_disp(image4, "Foreground/background segmentation result", 0);
    cout << "Saving the final result of the segmentation problem as JPEG in " << Settings::file_o2 << endl;
    image4.save_jpeg(Settings::file_o2, 100);

    while (!main_disp.is_closed())
        cimg::wait(40);
    return;
}