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

Vec2 Diamond_search::find_rel_best_opt_flow_big_pattern(const Vec2& block_start)
{
    // rel_ is always relative to block_start
    Vec2 current_rel_center(0, 0);
    Vec2 current_abs_center(block_start);
    Vec2 current_rel_candidate;
    Vec2 current_abs_candidate;
    Vec2 best_rel_candidate(0, 0);
    Vec2 best_abs_candidate(block_start);
    double current_candidate_cost;
    double best_cost;
    double* cost_map_ptr = nullptr;

    best_cost = cost(block_start, {0, 0});
    cost_map[block_start.y][block_start.x] = best_cost;

    do
    {
        current_rel_center = best_rel_candidate;
        current_abs_center = best_abs_candidate;

        for (const auto& rel_offset : big_pattern)
        {
            current_rel_candidate = current_rel_center + rel_offset;
            current_abs_candidate = current_abs_center + rel_offset;

            if (std::max(std::abs(current_rel_candidate.y), std::abs(current_rel_candidate.x)) > search_window_margin)
                continue;

            if (is_legal(current_abs_candidate))
            {
                cost_map_ptr = &cost_map[current_abs_candidate.y][current_abs_candidate.x];
                if (*cost_map_ptr < 0)
                {
                    current_candidate_cost = cost(block_start, current_rel_candidate);
                    *cost_map_ptr = current_candidate_cost;
                }
                else
                {
                    current_candidate_cost = *cost_map_ptr;
                }
            }
            else
            {
                current_candidate_cost = cost(block_start, current_rel_candidate);
            }
            if (current_candidate_cost < best_cost)
            {
                best_cost = current_candidate_cost;
                best_rel_candidate = current_rel_candidate;
                best_abs_candidate = current_abs_candidate;
            }
        } // Needs to be refactored into a separate method
    } while (current_rel_center != best_rel_candidate);

    return best_rel_candidate;
}

Vec2 Diamond_search::find_rel_best_opt_flow_small_pattern(const Vec2& block_start, const Vec2& rel_search_origin)
{
    Vec2 abs_search_origin = block_start + rel_search_origin;
    Vec2 best_rel_candidate(0, 0);
    Vec2 best_abs_candidate(abs_search_origin);
    Vec2 current_rel_candidate;
    Vec2 current_abs_candidate;
    double current_candidate_cost;
    double best_cost;
    double* cost_map_ptr = nullptr;

    if (is_legal(abs_search_origin))
        best_cost = cost_map[abs_search_origin.y][abs_search_origin.x];
    else
        best_cost = cost(block_start, rel_search_origin);

    for (const auto& rel_offset : small_pattern)
    {
        current_rel_candidate = rel_search_origin + rel_offset;
        current_abs_candidate = abs_search_origin + rel_offset;

        if (std::max(std::abs(current_rel_candidate.y), std::abs(current_rel_candidate.x)) > search_window_margin)
            continue;

        if (is_legal(current_abs_candidate))
        {
            cost_map_ptr = &cost_map[current_abs_candidate.y][current_abs_candidate.x];
            if (*cost_map_ptr < 0)
            {
                current_candidate_cost = cost(block_start, current_rel_candidate);
                *cost_map_ptr = current_candidate_cost;
            }
            else
            {
                current_candidate_cost = *cost_map_ptr;
            }
        }
        else
        {
            current_candidate_cost = cost(block_start, current_rel_candidate);
        }
        if (current_candidate_cost < best_cost)
        {
            best_cost = current_candidate_cost;
            best_rel_candidate = current_rel_candidate;
            best_abs_candidate = current_abs_candidate;
        }
    } // Needs to be refactored into a separate method

    return best_rel_candidate;
}

Vec2 Diamond_search::calculate_block_opt_flow(Vec2 block_start)
{
    partial_reset_cost_map(Vec2(block_start.x - search_window_margin, block_start.y - search_window_margin),
                           Vec2(block_start.x + block_size + search_window_margin, block_start.y + block_size + search_window_margin));

    Vec2 big_pattern_best_rel_candidate = find_rel_best_opt_flow_big_pattern(block_start);

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
