#include <stdexcept>
#include <algorithm>

#include "interpolator.h"
#include "arps.h"
#include "diamond_search.h"
#include "lucas_kanade.h"
#include "horn_schunck.h"

Interpolator::Interpolator()
{
    opt_flow_calculator = nullptr;
    // Probably needs more initialization
}

Interpolator::~Interpolator()
{
    if (opt_flow_calculator != nullptr)
        delete opt_flow_calculator;
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

Optical_flow_calculator* Interpolator::create_opt_flow_calculator() const
{
    switch (interpolator_options.opt_flow_algorithm)
    {
    case Algorithm::ARPS:
        return new ARPS();
        break;
    case Algorithm::diamond_search:
        return new Diamond_search();
        break;
    case Algorithm::lucas_kanade:
        return new Lucas_kanade();
        break;
    case Algorithm::horn_schunck:
        return new Horn_schunck();
        break;
    default:
        throw std::domain_error("Invalid optical flow algorithm");
    }
}

void Interpolator::generate_intermediate_frames()
{
    if (opt_flow_calculator == nullptr)
        opt_flow_calculator = create_opt_flow_calculator();

    if (interpolated_frames.size() < interpolator_options.frames_to_generate)
    {
        interpolated_frames.resize(interpolator_options.frames_to_generate);
        for (auto& frame : interpolated_frames)
            frame = previous_frame.clone();
        // Slow but should only run once per video
    }

    for (int frame_idx = 0; frame_idx < interpolator_options.frames_to_generate; frame_idx++)
    {
        opt_flow_calculator->set_prev_frame(&previous_frame);
        opt_flow_calculator->set_next_frame(&next_frame);

        const Optical_flow_field& opt_flow_field = opt_flow_calculator->calculate();
        render_next_frame(opt_flow_field, frame_idx);
    }
}

void Interpolator::correct_motion_vectors()
{

}

void Interpolator::render_next_frame(const Optical_flow_field& opt_flow_field, int frame_idx)
{

}

void Interpolator::run()
{
    if (input_file_name.empty())
        throw std::logic_error("Input file name not present");
    if (output_file_name.empty())
        throw std::logic_error("Output file name not present");
    if (interpolator_options.frames_to_generate < 1)
        throw std::domain_error("frames_to_generate has to be at least 1");

    video_capture.open(input_file_name);
    video_info.fourcc = (int)video_capture.get(CV_CAP_PROP_FOURCC);
    video_info.fps = (int)video_capture.get(CV_CAP_PROP_FPS);
    video_info.height = (int)video_capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    video_info.width = (int)video_capture.get(CV_CAP_PROP_FRAME_WIDTH);
    video_info.frame_count = (int)video_capture.get(CV_CAP_PROP_FRAME_COUNT);
    known_pixel_map = std::vector<std::vector<char> >(video_info.height, std::vector<char>(video_info.width, 0));
    boundary_map_horizontal = known_pixel_map;
    boundary_map_vertical = known_pixel_map; // Just for brevity, they all have the same dimensions

    video_writer.open(output_file_name, video_info.fourcc,
                      video_info.fps, cv::Size(video_info.width, video_info.height));

    while (true) // Maybe bad idea?
    {
        if (previous_frame.empty())
        {
            video_capture >> previous_frame;
            video_capture >> next_frame;

            if (previous_frame.empty() || next_frame.empty())
                throw std::logic_error("Problem with video, stopping");
        }
        else
        {
            std::swap(previous_frame, next_frame);
            video_capture >> next_frame;

            if (next_frame.empty())
            {
                video_writer << previous_frame;
                return; // The only exit out of the infinite loop, please work
            }
        }

        generate_intermediate_frames();
        video_writer << previous_frame;

        for (const auto& interpolated_frame : interpolated_frames)
            video_writer << interpolated_frame;
    }
}
