#include <stdexcept>

#include "boundary_smoothener.h"

Boundary_smoothener::Boundary_smoothener()
{
    frame = nullptr;
    boundary_map_horizontal = nullptr;
    boundary_map_vertical = nullptr;
    // http://dev.theomader.com/gaussian-kernel-calculator/ for sigma=1 and n=5
    kernel = {0.06136, 0.24477, 0.38774, 0.24477, 0.06136}; // Hopefully the sum doesn't go over 1
}

void Boundary_smoothener::set_kernel(const std::vector<double>& new_kernel)
{
    if (kernel.size() % 2 == 0)
        throw std::logic_error("Kernel size needs to be odd");
    kernel = new_kernel;
}

void Boundary_smoothener::set_boundary_map_horizontal(const std::vector<std::vector<char> >* new_boundary_map_horizontal)
{
    boundary_map_horizontal = new_boundary_map_horizontal;
}

void Boundary_smoothener::set_boundary_map_vertical(const std::vector<std::vector<char> >* new_boundary_map_vertical)
{
    boundary_map_vertical = new_boundary_map_vertical;
}

void Boundary_smoothener::set_frame(cv::Mat* new_frame)
{
    frame = new_frame;
}

void Boundary_smoothener::add_pixels(cv::Vec3b &dest, const cv::Vec3b &source, double factor)
{
    dest[0] += factor * source[0];
    dest[1] += factor * source[1];
    dest[2] += factor * source[2];
}

void Boundary_smoothener::run()
{
    if (frame->rows != boundary_map_horizontal->size() ||
        frame->rows != boundary_map_vertical->size() ||
        frame->cols != (*boundary_map_horizontal)[0].size() ||
        frame->cols != (*boundary_map_vertical)[0].size())
    {
        throw std::logic_error("Frame size doesn't match boundary map size");
    }

    cv::Mat new_frame(frame->clone()); // O(slow) but inevitable

    const int half_kernel_size = (kernel.size() - 1) / 2;
    const static cv::Vec3b black(0, 0, 0);

    for (int i = half_kernel_size; i < (frame->rows - half_kernel_size); i++)
    {
        for (int j = half_kernel_size; j < (frame->cols - half_kernel_size); j++)
        {
            // Vertical overrides horizontal for now, should be changed to a special case
            // if both need to be applied
            if ((*boundary_map_horizontal)[i][j] != 0)
            {
                new_frame.at<cv::Vec3b>(i, j) = black;
                for (int elem = 0; elem < kernel.size(); elem++)
                    add_pixels(new_frame.at<cv::Vec3b>(i, j), frame->at<cv::Vec3b>(i, j + elem - half_kernel_size), kernel[elem]);
            }

            if ((*boundary_map_vertical)[i][j] != 0)
            {
                new_frame.at<cv::Vec3b>(i, j) = black;
                for (int elem = 0; elem < kernel.size(); elem++)
                    add_pixels(new_frame.at<cv::Vec3b>(i, j), frame->at<cv::Vec3b>(i + elem - half_kernel_size, j), kernel[elem]);
            }
        }
    }

    *frame = new_frame; // Actually O(1)
}

