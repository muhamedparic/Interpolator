#ifndef INTERPOLATOR_OPTIONS_H
#define INTERPOLATOR_OPTIONS_H

#include "algorithm.h"

struct Interpolator_options
{
    int frames_to_generate;
    Algorithm opt_flow_algorithm;
    Algorithm mv_correction_algorithm;
    int block_size;
    bool fix_holes;
    bool smooth_edges;
    bool blur_overlaps;
};

#endif // INTERPOLATOR_OPTIONS_H
