#include "adapters.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string file;
	std::vector<int> frames;

	if (argc < 3)
	{
		return 0;
	}

	file = std::string(argv[1]);

	for (int arg = 2; arg < argc; arg++)
	{
		frames.push_back(std::stoi(std::string(argv[arg])));
	}

	auto outframes = mp::extrframes(cv::VideoCapture(file), frames);

	int fr = 0;

	for (cv::Mat& frame : outframes)
	{
		cv::imwrite(std::string("frames/frame") + std::to_string(fr) + std::string(".jpg"), frame);
		fr++;
	}
}