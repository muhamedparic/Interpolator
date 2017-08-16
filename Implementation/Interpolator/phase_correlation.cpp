#include "phase_correlation.h"

Phase_correlation::Phase_correlation(const cv::Mat& prev_frame, const cv::Mat& next_frame)
    : Optical_flow_calculator(prev_frame, next_frame)
{

}

Optical_flow_field& Phase_correlation::calculate()
{

}
