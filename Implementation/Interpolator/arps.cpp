#include "arps.h"

ARPS::ARPS()
{

}

ARPS::ARPS(const cv::Mat* prev_frame, const cv::Mat* next_frame)
    : Optical_flow_calculator(prev_frame, next_frame)
{

}

Optical_flow_field& ARPS::calculate()
{

}
