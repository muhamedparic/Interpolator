#include <opencv2/opencv.hpp>
#include <string>

namespace mp
{
	struct Pixel
	{
		uchar r;
		uchar g;
		uchar b;
	};

	struct Ref_pixel
	{
		uchar& r;
		uchar& g;
		uchar& b;
	};

	class Image
	{
		cv::Mat cv_image;

	public:

		Image();
		Image(const std::string&, bool color = true);
		Image(const Image&);
		bool open(const std::string&, bool color = true);
		bool empty() const;
		int width() const;
		int height() const;
		Pixel at(int, int) const;
		Ref_pixel at(int, int);
		bool save(const std::string&) const;
	};

	enum class Vid_mode
	{
		read,
		write
	};

	class Video
	{
		cv::VideoWriter writer;
		cv::VideoCapture reader;
		Vid_mode mode;

	public:

		Video();
		Video(const std::string&, Vid_mode, double framerate = -1, int width = -1, int height = -1, bool color = true);
		Video(const Video&);
		//bool open(const std::string&);
		int width() const;
		int height() const;
		double framerate() const;
		int frame_count() const;
		void write(const Image&);
		bool read(Image&);
		bool save();
	};

	Image::Image()
	{}

	Image::Image(const std::string& path, bool color)
	{
		open(path, color);
	}

	Image::Image(const Image& original) : cv_image(original.cv_image)
	{}

	bool Image::open(const std::string& path, bool color)
	{
		cv_image = cv::imread(path, (color) ? cv::IMREAD_COLOR : cv::IMREAD_GRAYSCALE);
	}

	bool Image::empty() const
	{
		return cv_image.empty();
	}

	int Image::width() const
	{
		return cv_image.cols;
	}

	int Image::height() const
	{
		return cv_image.rows;
	}

	Pixel Image::at(int row, int col) const
	{
		cv::Vec3b pixel = cv_image.at<cv::Vec3b>(row, col);
		return {pixel[2], pixel[1], pixel[0]};
	}

	Ref_pixel Image::at(int row, int col)
	{
		cv::Vec3b& pixel = cv_image.at<cv::Vec3b>(row, col);
		return {pixel[2], pixel[1], pixel[0]};
	}

	bool Image::save(const std::string& path) const
	{
		return cv::imwrite(path, cv_image);
	}

	Video::Video()
	{}

	Video::Video(const std::string& path, Vid_mode mode, double framerate, int width, int height, bool color)
	{
		Video::mode = mode;
		if (mode == Vid_mode::read)
		{
			reader.open(path);
		}
		else
		{
			writer.open(path, CV_FOURCC('H', '2', '6', '4'), framerate, cv::Size(width, height), color);
		}
	}

	Video::Video(const Video& original) : mode(original.mode)
	{	
		if (original.mode == Vid_mode::read)
		{
			reader = cv::VideoCapture(original.reader);
		}
		else
		{
			writer = cv::VideoWriter(original.writer);
		}
	}

	int Video::width() const
	{
		if (mode == Vid_mode::read)
		{
			return reader.get(cv::CAP_PROP_FRAME_WIDTH);
		}
		else
		{
			return -1;
		}
	}

	int Video::height() const
	{
		if (mode == Vid_mode::read)
		{
			return reader.get(cv::CAP_PROP_FRAME_HEIGHT);
		}
		else
		{
			return -1;
		}
	}

	double Video::framerate() const
	{
		if (mode == Vid_mode::read)
		{
			return reader.get(cv::CAP_PROP_FPS);
		}
		else
		{
			return -1;
		}
	}

	int Video::frame_count() const
	{
		if (mode == Vid_mode::read)
		{
			return reader.get(cv::CAP_PROP_FRAME_COUNT);
		}
		else
		{
			return -1;
		}
	}

	void Video::write(const Image& frame)
	{
		writer.write(frame);
	}

	bool Video::read(Image& frame)
	{
		return reader.read(frame);
	}

	bool Video::save()
	{
		writer.release();
	}
}