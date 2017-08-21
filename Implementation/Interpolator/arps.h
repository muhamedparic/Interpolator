#ifndef ARPS_H
#define ARPS_H

#include "optical_flow_calculator.h"

class ARPS : public Optical_flow_calculator
{
public:
    ARPS(const cv::Mat* prev_frame, const cv::Mat* next_frame);
    Optical_flow_field& calculate() override;
};

#endif // ARPS_H
