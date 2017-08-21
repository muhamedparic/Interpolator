#include "horn_schunck.h"

Horn_schunck::Horn_schunck()
{

}

Horn_schunck::Horn_schunck(const cv::Mat* prev_frame, const cv::Mat* next_frame)
    : Optical_flow_calculator(prev_frame, next_frame)
{

}

Optical_flow_field& Horn_schunck::calculate()
{

}
