#ifndef HORN_SCHUNCK_H
#define HORN_SCHUNCK_H

#include "optical_flow_calculator.h"

class Horn_schunck : public Optical_flow_calculator
{
public:
    Horn_schunck();
    Horn_schunck(const cv::Mat* prev_frame, const cv::Mat* next_frame);
    Optical_flow_field& calculate() override;
};

#endif // HORN_SCHUNCK_H
