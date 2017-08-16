#include <algorithm>

#include "diamond_search.h"
#include "vec2.h"

Diamond_search::Diamond_search(const cv::Mat& prev_frame, const cv::Mat& next_frame)
    : Optical_flow_calculator(prev_frame, next_frame)
{
    reset_cost_map();
    big_pattern = {Vec2(0, -2), Vec2(1, -1), Vec2(2, 0), Vec2(1, 1), Vec2(0, 2), Vec2(-1, 1), Vec2(-2, 0), Vec2(-1, -1)};
    small_pattern = {Vec2(0, -1), Vec2(1, 0), Vec2(0, 1), Vec2(-1, 0)};
}

void Diamond_search::reset_cost_map()
{
    if (cost_map.empty())
        cost_map = std::vector<std::vector<int> >(prev_frame.rows, std::vector<int>(prev_frame.cols, -1)); // -1 is the starting (illegal) value
    else
    {
        for (auto& row : cost_map)
            std::fill(row.begin(), row.end(), -1);
    }
}

Vec2 Diamond_search::calculate_block_opt_flow(Vec2 block_start)
{
    Vec2 best_opt_flow(0, 0);
    Vec2 current_center(0, 0);

    // INCOMPLETE
}

Optical_flow_field& Diamond_search::calculate()
{
    reset_cost_map();
    for (int block_start_y = 0; block_start_y < prev_frame.rows; block_start_y += block_size)
    {
        for (int block_start_x = 0; block_start_x < prev_frame.cols; block_start_x += block_size)
        {

        }
    }
    // INCOMPLETE
}
