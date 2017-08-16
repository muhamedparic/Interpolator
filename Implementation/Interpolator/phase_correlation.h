#ifndef PHASE_CORRELATION_H
#define PHASE_CORRELATION_H

#include "optical_flow_calculator.h"

class Phase_correlation : public Optical_flow_calculator
{
public:
    Phase_correlation(const cv::Mat& prev_frame, const cv::Mat& next_frame);
    Optical_flow_field& calculate() override;
};

#endif // PHASE_CORRELATION_H
