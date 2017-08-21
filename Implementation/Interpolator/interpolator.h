#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <string>
#include <functional>
#include <vector>

#include <opencv2/opencv.hpp>

#include "interpolator_options.h"
#include "mv_corrector.h"
#include "boundary_smoothener.h"
#include "optical_flow_calculator.h"
#include "boundary_smoothener.h"
#include "optical_flow_field.h"
#include "algorithm.h"
#include "video_info.h"

class Interpolator
{    
public:
    Interpolator();
    void set_input_file_name(const std::string& input_name);
    void set_output_file_name(const std::string& output_name);
    Interpolator_options& options();
    void set_progress_callback(const std::function<void(double)> &callback_fn);
    void set_optical_flow_algorithm(Algorithm algorithm);
    void set_mv_correction_algorithm(Algorithm algorithm);
    double progress();
    void save_video();
    void run();
private:
    std::string input_file_name;
    std::string output_file_name;
    cv::VideoCapture video_capture;
    cv::VideoWriter video_writer;
    cv::Mat previous_frame;
    cv::Mat next_frame;
    std::vector<cv::Mat> interpolated_frames;
    Interpolator_options interpolator_options;
    Boundary_smoothener smoothener;
    int total_frames;
    int frames_processed;
    std::function<void(double)> progress_callback;
    std::vector<std::vector<char> > known_pixel_map;
    std::vector<std::vector<char> > boundary_map_horizontal;
    std::vector<std::vector<char> > boundary_map_vertical;
    Video_info video_info;

    void report_progress();
    void generate_intermediate_frames();
    void correct_motion_vectors();
    void render_next_frame(const Optical_flow_field& opt_flow_field);
};

#endif // INTERPOLATOR_H
