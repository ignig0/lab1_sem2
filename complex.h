#pragma once
#include "typeinfo.h"


typedef struct {
    double real;
    double imag;
} Complex;
const TypeInfo *getComplexTypeInfo();
