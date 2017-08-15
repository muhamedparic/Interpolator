#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <string>

#include <opencv2/opencv.hpp>

class Interpolator
{
    std::string input_file_name;
    std::string output_file_name;
    cv::VideoCapture video_capture;
public:
    Interpolator();
};

#endif // INTERPOLATOR_H
