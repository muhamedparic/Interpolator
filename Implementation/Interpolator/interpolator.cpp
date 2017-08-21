#include <stdexcept>

#include "interpolator.h"

Interpolator::Interpolator()
{

}

void Interpolator::set_input_file_name(const std::string& input_name)
{
    input_file_name = input_name;
}

void Interpolator::set_output_file_name(const std::string& output_name)
{
    output_file_name = output_name;
}

Interpolator_options& Interpolator::options()
{
    return interpolator_options;
}

void Interpolator::set_progress_callback(const std::function<void(double)>& callback_fn)
{
    progress_callback = callback_fn;
}

double Interpolator::progress()
{
    if (total_frames == 0)
        throw std::domain_error("Video has 0 total frames, can't calculate progress");
    return (double)frames_processed / total_frames;
}

void Interpolator::save_video()
{
    if (!video_writer.isOpened())
        throw std::logic_error("Video writer not open, can't save");
    video_writer.release();
}

void Interpolator::report_progress()
{
    if (progress_callback == nullptr)
        throw std::logic_error("No callback set, can't report progress");
    progress_callback(progress());
}

void Interpolator::set_optical_flow_algorithm(Algorithm algorithm)
{
    interpolator_options.opt_flow_algorithm = algorithm;
}

void Interpolator::set_mv_correction_algorithm(Algorithm algorithm)
{
    interpolator_options.mv_correction_algorithm = algorithm;
}

void Interpolator::generate_next_frame()
{

}

void Interpolator::correct_motion_vectors()
{

}

void Interpolator::render_next_frame(const Optical_flow_field& opt_flow_field)
{

}

void Interpolator::run()
{
    if (input_file_name.empty())
        throw std::logic_error("Input file name not present");
    if (output_file_name.empty())
        throw std::logic_error("Output file name not present");

    video_capture.open(input_file_name);
    video_info.fourcc = (int)video_capture.get(CV_CAP_PROP_FOURCC);
    video_info.fps = (int)video_capture.get(CV_CAP_PROP_FPS);
    video_info.height = (int)video_capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    video_info.width = (int)video_capture.get(CV_CAP_PROP_FRAME_WIDTH);
    video_info.frame_count = (int)video_capture.get(CV_CAP_PROP_FRAME_COUNT);

    video_writer.open(output_file_name, video_info.fourcc,
                      video_info.fps, cv::Size(video_info.width, video_info.height));
    // INCOMPLETE
}
