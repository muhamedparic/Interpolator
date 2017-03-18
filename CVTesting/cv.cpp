#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

int main()
{
	cv::Mat img = cv::imread("img1.png");
	uchar* data = img.data;

	for (int i = 0; i < 3 * img.cols * img.rows; i++)
	{
		data[i] = std::min((int)data[i] + 50, 255);
	}

	cv::imwrite("img1green.png", img);
}