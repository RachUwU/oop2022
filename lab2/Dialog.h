#ifndef INC_2LAB3_DIALOG_H
#define INC_2LAB3_DIALOG_H
#include "dinamic.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace BinaryVector;
namespace Dialog{
    template<class T>
    int getNum(T &a) {
        std::cin >> a;
        if (!std::cin.good())
            return -1;
        return 1;
    }

    int dialog(const char *msgs[], int N);
    int D_SetWithInt(BinVector& a);
    int D_SetWithString(BinVector& a);
    int D_GetSize(BinVector& a);
    int D_Print(BinVector& a);
    int D_String(BinVector& a);
    int D_OR(BinVector& a);
    int D_AND(BinVector& a);
    int D_XOR(BinVector& a);
    int D_Addition(BinVector& a);
    int D_LimitedVector(BinVector& a);
    int D_PLUSPLUS(BinVector& a);
    int D_GetElement(BinVector& a);
    int D_Sum(BinVector& a);
}
#endif //INC_2LAB3_DIALOG_H
