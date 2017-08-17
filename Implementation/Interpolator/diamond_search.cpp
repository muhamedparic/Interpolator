#include <algorithm>
#include <iostream>

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
        cost_map = std::vector<std::vector<double> >(prev_frame.rows, std::vector<double>(prev_frame.cols, -1)); // -1 is the starting (illegal) value
    else
    {
        for (auto& row : cost_map)
            std::fill(row.begin(), row.end(), -1);
    }
}

// Each block has a separate cost map, so we need to reset the neighborhood of a block before it's used
void Diamond_search::partial_reset_cost_map(Vec2 start, Vec2 end)
{
    for (int i = start.y; i <= end.y; i++)
    {
        for (int j = start.x; j <= end.x; j++)
        {
            if (is_legal(Vec2(j, i)))
                cost_map[j][i] = -1;
        }
    }
}

Vec2 Diamond_search::calculate_block_opt_flow(Vec2 block_start)
{
    Vec2 best_opt_flow(0, 0);
    Vec2 current_center(0, 0);
    double best_cost;

    partial_reset_cost_map(Vec2(block_start.x - search_window_margin, block_start.y - search_window_margin),
                           Vec2(block_start.x + block_size + search_window_margin, block_start.y + block_size + search_window_margin));

    if (!is_legal(block_start))
    {
        std::cerr << "Checking block whose origin is an illegal coordinate, can't use cost_map, returning a 0 vector!";
        return {0, 0};
    }

    best_cost = cost_map[current_center.y][current_center.x] = cost(block_start, {0, 0});

    // First step, probably needs a separate method
//    do
//    {
//        current_center = best_opt_flow;
//        for (const Vec2& location : big_pattern)
//        {
//            Vec2 new_location = current_center + location;
//            if (is_legal(new_location))
//            {
//                if (cost_map[new_location.y][new_location.x] < 0)
//                {
//                    const auto& current_cost = cost_map[new_location.y][new_location.x] = cost(block_start, new_location);
//                    // Just for aliasing
//                    if (current_cost < best_cost)
//                    {
//                        best_cost = current_cost;
//                        best_opt_flow =
//                    }
//                }
//            }
//        }
//    } while (best_opt_flow != current_center);
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
