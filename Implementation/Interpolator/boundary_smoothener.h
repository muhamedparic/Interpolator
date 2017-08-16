#ifndef BOUNDARY_SMOOTHENER_H
#define BOUNDARY_SMOOTHENER_H

#include <opencv2/opencv.hpp>

class Boundary_smoothener
{
public:
    Boundary_smoothener(); // TEMPORARY
    Boundary_smoothener(cv::Mat& frame,
                        const std::vector<std::vector<char> >& bound_map_h,
                        const std::vector<std::vector<char> >& bound_map_v);
    void run();
    void set_kernel(const std::vector<char>& new_kernel);
private:
    std::vector<char> kernel;
};

#endif // BOUNDARY_SMOOTHENER_H
