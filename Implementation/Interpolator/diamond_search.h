#ifndef DIAMOND_SEARCH_H
#define DIAMOND_SEARCH_H

#include <array>
#include <vector>

#include "optical_flow_calculator.h"
#include "vec2.h"

class Diamond_search : public Optical_flow_calculator
{
public:
    Diamond_search();
    Diamond_search(const cv::Mat* prev_frame, const cv::Mat* next_frame);
    Optical_flow_field& calculate() override;
private:
    std::array<Vec2, 8> big_pattern;
    std::array<Vec2, 4> small_pattern;
    std::vector<std::vector<double> > cost_map;

    Vec2 calculate_block_opt_flow(const Vec2& block_start);
    void reset_cost_map();
    void partial_reset_cost_map(const Vec2& start, const Vec2& end);
    Vec2 find_best_opt_flow_big_pattern(const Vec2& block_start);
    Vec2 find_best_opt_flow_small_pattern(const Vec2& block_start, const Vec2& search_origin);
    void init_patterns();
};

#endif // DIAMOND_SEARCH_H
