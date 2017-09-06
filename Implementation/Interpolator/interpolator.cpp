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
    if (progress_callback != nullptr)
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

cv::Vec3b Interpolator::blend_pixels(const cv::Vec3b& pixel1, const cv::Vec3b& pixel2, double ratio)
{
    unsigned int b = (ratio * pixel1[0] + (1 - ratio) * pixel2[0]);
    unsigned int g = (ratio * pixel1[1] + (1 - ratio) * pixel2[1]);
    unsigned int r = (ratio * pixel1[2] + (1 - ratio) * pixel2[2]);
    return cv::Vec3b(b, g, r);
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

        Optical_flow_field& opt_flow_field = opt_flow_calculator->calculate();
        correct_motion_vectors(opt_flow_field);
        render_next_frame(opt_flow_field, frame_idx);
    }

    frames_processed++;
    report_progress();
}

void Interpolator::correct_motion_vectors(Optical_flow_field& opt_flow_field)
{
    return; // For now
}

void Interpolator::render_next_frame(const Optical_flow_field& opt_flow_field, int frame_idx)
{
    paste_pixels(opt_flow_field, frame_idx);
    if (interpolator_options.fix_holes)
        fill_unknown_pixels(frame_idx);

    // No boundary map generation, that's the next step
    // Then fix the edges, and voila
}

void Interpolator::paste_pixels(const Optical_flow_field& opt_flow_field, int frame_idx)
{
    // Needs to include boundary maps
    for (auto& row : known_pixel_map)
        std::fill(row.begin(), row.end(), 0);

    for (int i = 0; i < previous_frame.rows; i++)
    {
        for (int j = 0; j < previous_frame.cols; j++)
        {
            Vec2 projected_position = Vec2(j, i) + (opt_flow_field.data[i][j] *
                    (((double)frame_idx + 1) / (interpolator_options.frames_to_generate + 1)));

            if (is_legal(projected_position))
            {
                auto& current_pixel = previous_frame.at<cv::Vec3b>(i, j);
                auto& other_pixel = interpolated_frames[frame_idx].
                        at<cv::Vec3b>(projected_position.y, projected_position.x);

                if (known_pixel_map[projected_position.y][projected_position.x] != 0 && interpolator_options.blur_overlaps)
                    other_pixel = blend_pixels(current_pixel, other_pixel);
                else
                    other_pixel = current_pixel;

                known_pixel_map[projected_position.y][projected_position.x] = 1;
            }

        }
    }
}

void Interpolator::fill_unknown_pixels(int frame_idx)
{
    double frame_distance = (frame_idx + 1) / (interpolator_options.frames_to_generate + 1);

    for (int i = 0; i < previous_frame.rows; i++)
    {
        for (int j = 0; j < previous_frame.cols; j++)
        {
            if (known_pixel_map[i][j] == 0)
            {
                auto& mid_pixel = interpolated_frames[frame_idx].at<cv::Vec3b>(i, j);
                auto& previous_pixel = previous_frame.at<cv::Vec3b>(i, j);
                auto& next_pixel = next_frame.at<cv::Vec3b>(i, j);
                mid_pixel = blend_pixels(previous_pixel, next_pixel, frame_distance);
            }
        }
    }
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

    total_frames = video_info.frame_count;
    frames_processed = 0;

    video_writer.open(output_file_name, CV_FOURCC('H', '2', '6', '4'),
                      video_info.fps, cv::Size(video_info.width, video_info.height)); // Should be changed to a different framerate
    if (!video_writer.isOpened())
        throw std::logic_error("Can\'t open video writer!");

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
