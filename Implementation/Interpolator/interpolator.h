#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <string>
#include <functional>

#include <opencv2/opencv.hpp>

#include "interpolator_options.h"
#include "mv_corrector.h"
#include "boundary_smoothener.h"
#include "optical_flow_calculator.h"
#include "boundary_smoothener.h"

class Interpolator
{    
public:
    Interpolator();
    void set_input_file_name(const std::string& input_name);
    void set_output_file_name(const std::string& output_name);
    Interpolator_options& options();
    void set_progress_callback(std::function<void(double)> callback_fn);
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
    cv::Mat interpolated_frame;
    Interpolator_options options;
    Optical_flow_calculator* optical_flow_calculator;
    MV_corrector* mv_corrector;
    Boundary_smoothener smoothener;
    int total_frames;
    int frames_processed;
    std::function<void(double)> progress_callback;
    std::vector<std::vector<char>> boundary_map_horizontal;
    std::vector<std::vector<char>> boundary_map_vertical;

    void report_progress();
    void generate_next_frame();
    void correct_motion_vectors();
    //void render_next_frame(const Optical_flow_field& opt_flow_field);
};

#endif // INTERPOLATOR_H
