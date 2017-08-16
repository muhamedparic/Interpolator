#include "diamond_search.h"
#include "vec2.h"

Diamond_search::Diamond_search(const cv::Mat& prev_frame, const cv::Mat& next_frame)
    : Optical_flow_calculator(prev_frame, next_frame)
{
    cost_map = std::vector<std::vector<int> >(prev_frame.rows, std::vector<int>(prev_frame.cols));
    big_pattern = {Vec2(0, -2), Vec2(1, -1), Vec2(2, 0), Vec2(1, 1), Vec2(0, 2), Vec2(-1, 1), Vec2(-2, 0), Vec2(-1, -1)};
    small_pattern = {Vec2(0, -1), Vec2(1, 0), Vec2(0, 1), Vec2(-1, 0)};
}

Optical_flow_field& Diamond_search::calculate()
{

}
