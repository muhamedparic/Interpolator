#include "lucas_kanade.h"

Lucas_kanade::Lucas_kanade()
{

}

Lucas_kanade::Lucas_kanade(const cv::Mat* prev_frame, const cv::Mat* next_frame)
    : Optical_flow_calculator(prev_frame, next_frame)
{

}

Optical_flow_field& Lucas_kanade::calculate()
{

}
