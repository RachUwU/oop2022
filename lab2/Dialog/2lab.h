#ifndef INC_2LAB2WITHSTATIC_2LAB_H
#define INC_2LAB2WITHSTATIC_2LAB_H
#include "library.h"
#include <iostream>
#include <cmath>
#include <sstream>
namespace Cassini{
    template<class T>
    int getNum(T &a) {
        std::cin >> a;
        if (!std::cin.good())
            return -1;
        return 1;
    }

    int dialog(const char *msgs[], int N);

    int D_Set(Curve &curve);

    int D_Getform(Curve &curve);

    int D_SetA(Curve &curve);

    int D_SetC(Curve &curve);

    int D_FindR(Curve &curve);

    int D_FindCurvature(Curve &curve);

    int D_GetCoordinates(Curve &curve);

    int D_GetFormula(Curve &curve);

}
#endif //INC_2LAB2WITHSTATIC_2LAB_H
