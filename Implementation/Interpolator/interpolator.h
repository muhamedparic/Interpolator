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
#include "vec2.h"

class Interpolator
{    
public:
    Interpolator();
    ~Interpolator();
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
    Optical_flow_calculator* opt_flow_calculator;

    void report_progress();
    void generate_intermediate_frames();
    void correct_motion_vectors(Optical_flow_field& opt_flow_field);
    void render_next_frame(const Optical_flow_field& opt_flow_field, int frame_idx);
    void paste_pixels(const Optical_flow_field& opt_flow_field, int frame_idx);
    void fill_unknown_pixels(int frame_idx);
    Optical_flow_calculator* create_opt_flow_calculator() const;
    void create_boundary_map(const Optical_flow_field& opt_flow_field);
    void smooth_edges(int frame_idx);
    inline bool is_legal(Vec2 pos) const
    {
        return pos.x >= 0 && pos.y >= 0 && pos.y < previous_frame.rows && pos.x < previous_frame.cols;
    }
    static cv::Vec3b blend_pixels(const cv::Vec3b& pixel1, const cv::Vec3b& pixel2, double ratio = 0.5);
};

#endif // INTERPOLATOR_H
