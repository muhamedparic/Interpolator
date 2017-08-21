#include <ctime>
#include <cstdlib>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "test_diamond_search.h"
#include "diamond_search.h"
#include "vec2.h"

Test_diamond_search::Test_diamond_search()
{
    identical_frames();
    random_frames();
    shift();
}

template <typename T1, typename T2>
bool Test_diamond_search::compare(const T1& val1, const T2& val2)
{
    if (!(val1 == val2))
    {
        std::cerr << "Values don't match!";\
        return false;
    }
    return true;
}

void Test_diamond_search::identical_frames()
{
    Diamond_search* search;
    const int height = 72;
    const int width = 128;

    cv::Mat frame(height, width, CV_8UC1);

    std::srand(std::time(0));

    auto rand_pixel = [](){
        return rand() % 255;
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            frame.at<uchar>(i, j) = rand_pixel();
    }

    search = new Diamond_search(&frame, &frame);
    Optical_flow_field& field = search->calculate();

    for (int i = 0; i < field.rows; i++)
    {
        for (int j = 0; j < field.cols; j++)
            compare(field.data[i][j], Vec2(0, 0));
    }

    delete search;
}

void Test_diamond_search::random_frames()
{
    Diamond_search* search;
    const int height = 32;
    const int width = 32;

    cv::Mat frame1(height, width, CV_8UC1);
    cv::Mat frame2(height, width, CV_8UC1);

    std::srand(std::time(0));

    auto rand_pixel = [](){
        return rand() % 255;
    };

    for (int i = 0; i < frame1.rows; i++)
    {
        for (int j = 0; j < frame1.cols; j++)
            frame1.at<uchar>(i, j) = rand_pixel();
    }

    for (int i = 0; i < frame2.rows; i++)
    {
        for (int j = 0; j < frame2.cols; j++)
            frame2.at<uchar>(i, j) = rand_pixel();
    }

    search = new Diamond_search(&frame1, &frame2);

    Optical_flow_field& field = search->calculate();

    for (int i = 0; i < field.rows; i++)
    {
        for (int j = 0; j < field.cols; j++)
            std::cout << field.data[i][j].x << ' ' << field.data[i][j].y << "  ";
        std::cout << std::endl;
    }

    delete search;
}

void Test_diamond_search::shift()
{
    Diamond_search* search;
    const int height = 80;
    const int width = 80;

    cv::Mat frame1(height, width, CV_8UC1);
    cv::Mat frame2(height, width, CV_8UC1);

    std::srand(std::time(0));

    auto rand_pixel = [](){
        return rand() % 255;
    };

    for (int i = 0; i < frame1.rows; i++)
    {
        for (int j = 0; j < frame1.cols; j++)
            frame1.at<uchar>(i, j) = rand_pixel();
    }

    int i_offset = -2;
    int j_offset = 0;

    for (int i = 0; i < frame2.rows; i++)
    {
        for (int j = 0; j < frame2.cols; j++)
        {
            if (i >= i_offset && j >= j_offset)
                frame2.at<uchar>(i, j) = frame1.at<uchar>(i - i_offset, j - j_offset);
            else
                frame2.at<uchar>(i, j) = rand_pixel();
        }
    }

    search = new Diamond_search(&frame1, &frame2);

    Optical_flow_field& field = search->calculate();

    for (int i = 0; i < field.rows; i++)
    {
        for (int j = 0; j < field.cols; j++)
            std::cout << field.data[i][j].x << ' ' << field.data[i][j].y << "  ";
        std::cout << std::endl;
    }

//    for (int i = 0; i < frame1.rows; i++)
//    {
//        for (int j = 0; j < frame1.cols; j++)
//            std::cout << (int)frame1.at<uchar>(i, j) << "  ";
//        std::cout << std::endl;
//    }

//    std::cout << "\n\n";

//    for (int i = 0; i < frame2.rows; i++)
//    {
//        for (int j = 0; j < frame2.cols; j++)
//            std::cout << (int)frame2.at<uchar>(i, j) << "  ";
//        std::cout << std::endl;
//    }

    delete search;
}
