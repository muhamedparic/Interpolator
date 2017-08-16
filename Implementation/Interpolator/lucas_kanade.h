#ifndef LUCAS_KANADE_H
#define LUCAS_KANADE_H

#include "optical_flow_calculator.h"

class Lucas_kanade : public Optical_flow_calculator
{
public:
    Lucas_kanade(const cv::Mat& prev_frame, const cv::Mat& next_frame);
    Optical_flow_field& calculate() override;
};

#endif // LUCAS_KANADE_H
