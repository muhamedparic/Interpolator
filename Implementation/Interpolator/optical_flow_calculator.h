#ifndef OPTICAL_FLOW_CALCULATOR_H
#define OPTICAL_FLOW_CALCULATOR_H

#include <opencv2/opencv.hpp>

#include "optical_flow_field.h"

class Optical_flow_calculator
{
public:
    Optical_flow_calculator(const cv::Mat& prev_frame, const cv::Mat& next_frame, int block_size = 16);
    virtual Optical_flow_field& calculate() = 0;
    virtual ~Optical_flow_calculator();
protected:
    double cost(Vec2 block_start, Vec2 block_offset);
private:
    const cv::Mat& prev_frame;
    const cv::Mat& next_frame;
    Optical_flow_field opt_flow_field;
    int block_size;
};

#endif // OPTICAL_FLOW_CALCULATOR_H
