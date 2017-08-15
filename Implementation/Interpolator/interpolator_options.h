#ifndef INTERPOLATOR_OPTIONS_H
#define INTERPOLATOR_OPTIONS_H


struct Interpolator_options
{
    int frames_to_generate;
    //Algorithm opt_flow_algorithm;
    //Algorithm mv_correction_algorithm;
    bool fix_holes;
    bool smooth_edges;
};

#endif // INTERPOLATOR_OPTIONS_H
