#ifndef BOUNDARY_SMOOTHENER_H
#define BOUNDARY_SMOOTHENER_H

#include <vector>

#include <opencv2/opencv.hpp>

class Boundary_smoothener
{
public:
    Boundary_smoothener();
    void set_frame(cv::Mat* new_frame);
    void set_boundary_map_horizontal(const std::vector<std::vector<char> >* new_boundary_map_horizontal);
    void set_boundary_map_vertical(const std::vector<std::vector<char> >* new_boundary_map_vertical);
    void run();
    void set_kernel(const std::vector<double>& new_kernel);
private:
    std::vector<double> kernel;
    cv::Mat* frame;
    const std::vector<std::vector<char> >* boundary_map_horizontal;
    const std::vector<std::vector<char> >* boundary_map_vertical;

    void add_pixels(cv::Vec3b& dest, const cv::Vec3b& source, double factor);
};

#endif // BOUNDARY_SMOOTHENER_H
