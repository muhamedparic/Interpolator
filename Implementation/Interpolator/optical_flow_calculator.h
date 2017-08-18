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
    const cv::Mat& prev_frame;
    const cv::Mat& next_frame;
    Optical_flow_field opt_flow_field;
    int block_size;
    int search_window_margin;

    double cost(Vec2 block_start, Vec2 block_offset);
    inline bool is_legal(const Vec2& pos);
};

#endif // OPTICAL_FLOW_CALCULATOR_H
