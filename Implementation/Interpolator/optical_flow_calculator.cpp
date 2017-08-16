#include <algorithm>
#include <stdexcept>

#include "optical_flow_calculator.h"

Optical_flow_calculator::Optical_flow_calculator(const cv::Mat& prev_frame, const cv::Mat& next_frame, int block_size)
    : prev_frame(prev_frame), next_frame(next_frame), block_size(block_size)
{
    opt_flow_field.data = std::vector<std::vector<Vec2> >(prev_frame.rows, std::vector<Vec2>(prev_frame.cols, Vec2(0, 0)));
}

Optical_flow_calculator::~Optical_flow_calculator()
{

}

double Optical_flow_calculator::cost(Vec2 block_start, Vec2 block_offset)
{
    int pixels_used = 0;
    int cost_sum = 0;
    static auto is_legal = [&](Vec2 pos) -> bool
    {
        return pos.x >= 0 && pos.y >= 0 && pos.x < prev_frame.cols && pos.y < prev_frame.rows;
    };
    static auto pixel_cost = [&](Vec2 pos_in_block) -> int
    {
        Vec2 pos_in_first_frame = block_start + pos_in_block;
        Vec2 pos_in_second_frame = block_start + block_offset + pos_in_block;
        int first_pixel = prev_frame.at<uchar>(pos_in_first_frame.y, pos_in_first_frame.x);
        int second_pixel = next_frame.at<uchar>(pos_in_second_frame.y,pos_in_second_frame.x);
        return std::abs(first_pixel - second_pixel); // Can be changed to squaring
    };

    for (int i = 0; i < block_size; i++)
    {
        for (int j = 0; j < block_size; j++)
        {
            if (is_legal(block_start + block_offset + Vec2(j, i)))
            {
                pixels_used++;
                cost_sum += pixel_cost({j, i});
            }
        }
    }

    if (pixels_used == 0)
        throw std::logic_error("Can't calculate cost with no legal pixel positions");
    return (double)cost_sum / (block_size * block_size);
}
