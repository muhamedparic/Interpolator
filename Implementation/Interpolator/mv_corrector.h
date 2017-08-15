#ifndef MV_CORRECTOR_H
#define MV_CORRECTOR_H

#include "optical_flow_field.h"

class MV_corrector
{
public:
    virtual void run(Optical_flow_field& opt_flow_field) = 0;
};

#endif // MV_CORRECTOR_H
