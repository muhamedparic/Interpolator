#ifndef OPTICAL_FLOW_FIELD_H
#define OPTICAL_FLOW_FIELD_H

#include "vec2.h"

struct Optical_flow_field
{
    std::vector<std::vector<Vec2> > data;
    int rows;
    int cols;
};

#endif // OPTICAL_FLOW_FIELD_H
