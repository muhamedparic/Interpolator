#ifndef OPTICAL_FLOW_CALCULATOR_H
#define OPTICAL_FLOW_CALCULATOR_H

#include <opencv2/opencv.hpp>

#include "optical_flow_field.h"

class Optical_flow_calculator
{
public:
    set_prev_frame(const cv::Mat& frame);
    set_next_frame(const cv::Mat& frame);
    virtual Optical_flow_field& calculate() = 0;
private:
    const cv::Mat& prev_frame;
    const cv::Mat& next_frame;
    Optical_flow_field opt_flow_field;
};

#endif // OPTICAL_FLOW_CALCULATOR_H
