#include <opencv2/opencv.hpp>
#include <string>

namespace mp
{
	std::vector<cv::Mat> extrframes(cv::VideoCapture video, const std::vector<int>& frames)
	{
		std::vector<cv::Mat> res;
		cv::Mat curframe;

		for (int frame = 0, towrite = 0; ; frame++)
		{
			video >> curframe;

			if (curframe.empty())
			{
				return res;
			}

			if (frame == frames[towrite])
			{
				res.push_back(curframe.clone());
				towrite++;

				if (towrite == frames.size())
				{
					return res;
				}
			}
		}
	}
}