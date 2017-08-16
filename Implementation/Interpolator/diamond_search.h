#ifndef DIAMOND_SEARCH_H
#define DIAMOND_SEARCH_H

#include <array>
#include <vector>

#include "optical_flow_calculator.h"
#include "vec2.h"

class Diamond_search : public Optical_flow_calculator
{
public:
    Diamond_search(const cv::Mat& prev_frame, const cv::Mat& next_frame);
    Optical_flow_field& calculate() override;
private:
    std::array<Vec2, 8> big_pattern;
    std::array<Vec2, 4> small_pattern;
    std::vector<std::vector<int> > cost_map;
};

#endif // DIAMOND_SEARCH_H
