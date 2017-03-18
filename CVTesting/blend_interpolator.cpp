#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <algorithm>

//const cv::Size out_size(1920, 1080);

void calc_inter_frame(const cv::Mat&, const cv::Mat&, cv::Mat&);

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


    cv::VideoCapture input(argv[1]);
    cv::Mat prev_frame, next_frame, inter_frame;

    cv::VideoWriter output(argv[2], CV_FOURCC('H', '2', '6', '4'), slow_mo ? 30 : 60, cv::Size(input.get(cv::CAP_PROP_FRAME_WIDTH), input.get(cv::CAP_PROP_FRAME_HEIGHT)));

    input >> next_frame;

    while (true)
    {
        std::swap(prev_frame, next_frame);
        input >> next_frame;

        if (next_frame.empty())
            break;
        
        calc_inter_frame(prev_frame, next_frame, inter_frame);
        //cv::resize(prev_frame, prev_frame, out_size);
        //cv::resize(inter_frame, inter_frame, out_size);
        output << prev_frame;
        output << inter_frame;
    }
}

void calc_inter_frame(const cv::Mat& prev_frame, const cv::Mat& next_frame, cv::Mat& inter_frame)
{
    cv::addWeighted(prev_frame, 0.5, next_frame, 0.5, 0, inter_frame);
}