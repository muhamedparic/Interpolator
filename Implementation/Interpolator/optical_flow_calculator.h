#ifndef OPTICAL_FLOW_CALCULATOR_H
#define OPTICAL_FLOW_CALCULATOR_H

#include <opencv2/opencv.hpp>

#include "optical_flow_field.h"

class Optical_flow_calculator
{
public:
    Optical_flow_calculator(int block_size = 16);
    Optical_flow_calculator(const cv::Mat* prev_frame, const cv::Mat* next_frame, int block_size = 16);
    virtual Optical_flow_field& calculate() = 0;
    virtual ~Optical_flow_calculator();
    void set_prev_frame(const cv::Mat* new_prev_frame);
    void set_next_frame(const cv::Mat* new_next_frame);
protected:
    const cv::Mat* prev_frame;
    const cv::Mat* next_frame;
    cv::Mat prev_frame_grayscale;
    cv::Mat next_frame_grayscale;
    Optical_flow_field opt_flow_field;
    int block_size;
    int search_window_margin;

    double cost(const Vec2& block_start, const Vec2& block_offset) const;
    inline bool is_legal(const Vec2& pos) const
    {
        return pos.x >= 0 && pos.y >= 0 && pos.x < prev_frame->cols && pos.y < prev_frame->rows;
    }
    inline int grayscale_pixel(const cv::Vec3b& pixel) const
    {
        return (pixel[0] + pixel[1] + pixel[2]) / 3;
    }
    void init_opt_flow_field();
};

#endif // OPTICAL_FLOW_CALCULATOR_H
