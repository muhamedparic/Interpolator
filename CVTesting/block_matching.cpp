#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#define BLOCK_S 8
int FRAME_H, FRAME_W, BLOCK_H, BLOCK_W;

void interpolate_frame(const cv::Mat &previous, const cv::Mat &next, cv::Mat &result);
double calc_MAD(const cv::Mat &first, int fy, int fx, const cv::Mat &second, int sy, int sx);

inline const unsigned char &red(const cv::Mat &im, int row, int col)
{
    return *(im.data + (3 * row * FRAME_W) + 3 * col + 2);
}

inline const unsigned char &green(const cv::Mat &im, int row, int col)
{
    return *(im.data + (3 * row * FRAME_W) + 3 * col + 1);
}

inline const unsigned char &blue(const cv::Mat &im, int row, int col)
{
    return *(im.data + (3 * row * FRAME_W) + 3 * col);
}

int main(int argc, char **argv)
{
    cv::VideoCapture input(argv[1]);
    cv::Mat previous, next, dummy;

    int steps = 2000;

    while (steps--) {
        input >> dummy;
    }

    input >> previous;
    input >> next;

    FRAME_H = previous.rows;
    FRAME_W = previous.cols;
    BLOCK_H = FRAME_H / BLOCK_S;
    BLOCK_W = FRAME_W / BLOCK_S;

    cv::Mat interpolated(previous.clone());
    interpolated = cv::Scalar(0, 0, 0);
    interpolate_frame(previous, next, interpolated);

    cv::namedWindow("Previous", cv::WINDOW_NORMAL);
    cv::namedWindow("Interpolated", cv::WINDOW_NORMAL);
    cv::namedWindow("Next", cv::WINDOW_NORMAL);

    cv::resizeWindow("Previous", 640, 360);
    cv::resizeWindow("Interpolated", 640, 360);
    cv::resizeWindow("Next", 640, 360);

    cv::imshow("Previous", previous);
    cv::imshow("Interpolated", interpolated);
    cv::imshow("Next", next);

    cv::waitKey(0);
}

void interpolate_frame(const cv::Mat &previous, const cv::Mat &next, cv::Mat &result)
{
    for (int i = 0; i < BLOCK_H; i++)
    {
        for (int j = 0; j < BLOCK_W; j++)
        {
            std::cout << "BLOCK " << i * BLOCK_W + j << '\n';
            int best_oy, best_ox;
            double best_mad = 256.0;

            for (int oy = -15; oy < 16; oy++)
            {
                for (int ox = -15; ox < 16; ox++)
                {
                    double mad = calc_MAD(previous, i, j, next, i + oy, j + ox);
                    if (mad < best_mad)
                    {
                        best_mad = mad;
                        best_oy = oy;
                        best_ox = ox;
                    }
                }
            }

            for (int ii = 0; ii < BLOCK_S; ii++)
            {
                for (int jj = 0; jj < BLOCK_S; jj++)
                {
                    int py = i * BLOCK_S + ii;
                    int px = j * BLOCK_S + jj;
                    int iy = i * BLOCK_S + best_oy + ii;
                    int ix = j * BLOCK_S + best_ox + jj;

                    if (iy >= 0 && iy < FRAME_H &&
                        ix >= 0 && ix < FRAME_W)
                    {
                        result.at<cv::Vec3b>(iy, ix) = previous.at<cv::Vec3b>(py, px);
                    }
                }
            }
        }
    }
}

double calc_MAD(const cv::Mat &first, int fy, int fx, const cv::Mat &second, int sy, int sx)
{
    int SAD = 0;
    int valid_pixels = 0;

    for (int i = 0; i < BLOCK_S; i++)
    {
        for (int j = 0; j < BLOCK_S; j++)
        {
            if (fy + i >= 0 && fy + i < FRAME_H &&
                fx + j >= 0 && fx + j < FRAME_W &&
                sy + i >= 0 && sy + i < FRAME_H &&
                sx + j >= 0 && sx + j < FRAME_W)
            {
                valid_pixels++;

                int fgray = (red(first, fy + i, fx + j) + green(first, fy + i, fx + j) + blue(first, fy + i, fx + j)) / 3;
                int sgray = (red(second, fy + i, fx + j) + green(second, fy + i, fx + j) + blue(second, fy + i, fx + j)) / 3;

                SAD += std::abs(fgray - sgray);
            }
        }
    }

    if (valid_pixels)
    {
        return SAD / valid_pixels;
    }
    else
    {
        return 256.0; // Maximum possible in normal conditions is 255, shouldn't ever happen
    }
}