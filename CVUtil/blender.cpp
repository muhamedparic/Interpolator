#include "adapters.hpp"
#include <iostream>
#include <string>
#include <algorithm>

//const cv::Size out_size(1920, 1080);

void calc_inter_frame(const mp::Image&, const mp::Image&, mp::Image&);

int main(int argc, char** argv)
{
    bool slow_mo = false;
    
    if (argc < 2)
    {
        std::cout << "No input video!\n";
        return -1;
    }
    if (argc >= 4 && std::string(argv[3]) == "-s")
    {
        slow_mo = true;
    }


    mp::Video input(argv[1], mp::Vid_mode::read);
    mp::Image prev_frame, next_frame, inter_frame;

    cv::Video output(argv[2], mp::Vid_mode::write, slow_mo ? 30 : 60, input.width(), input.height());

    input.read(next_frame);

    while (true)
    {
        std::swap(prev_frame, next_frame);
        input.read(next_frame);

        if (next_frame.empty())
            break;
        
        calc_inter_frame(prev_frame, next_frame, inter_frame);
        //cv::resize(prev_frame, prev_frame, out_size);
        //cv::resize(inter_frame, inter_frame, out_size);
        output.write(prev_frame);
        output.write(inter_frame);
    }
}

void calc_inter_frame(const mp::Image& prev_frame, const mp::Image& next_frame, mp::Image& inter_frame)
{
    for (int i = 0; i < prev_frame.height(); i++)
    {
        for (int j = 0; j < prev_frame.width(); j++)
        {
            Pixel prev = prev_frame.at(i, j);
            Pixel next = next_frame.at(i, j);
            
            inter_frame.at(i, j).r = ((int)prev.r + next.r) / 2;
            inter_frame.at(i, j).g = ((int)prev.g + next.g) / 2;
            inter_frame.at(i, j).b = ((int)prev.b + next.b) / 2;
        }
    }
}