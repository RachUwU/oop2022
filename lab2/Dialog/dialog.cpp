#include "2lab.h"
namespace Cassini {
    int dialog(const char *msgs[], int N) {
        const char *errmsg = "";
        int rc;
        int i, n;
        do {
            puts(errmsg);
            errmsg = "You are wrong. Repeat, please!";
            for (i = 0; i < N; ++i) {
                puts(msgs[i]);
            }
            puts("Make your choice:--> ");
            n = getNum(rc);
            if (n == 0) rc = 0;
        } while (rc < 0 || rc >= N);
        return rc;
    }

    int D_Set(Curve &curve) {
        const char *pr = "";
        double a, c;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter a:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(a) < 0)
                return 0;
        } while (a < 0);
        pr = "";
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter c:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(c) < 0)
                return 0;
        } while (c < 0);
        curve.set(a, c);
        return 1;
    }

    int D_SetA(Curve &curve) {
        const char *pr = "";
        double a;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter a:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(a) < 0)
                return 0;
        } while (a < 0);
        curve.set_a(a);
        return 1;
    }

    int D_SetC(Curve &curve) {
        const char *pr = "";
        double c;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter c:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(c) < 0)
                return 0;
        } while (c < 0);
        curve.set_c(c);
        return 1;
    }

    int D_Getform(Curve &curve) {
        int a = curve.getform();
        if(a == 0){
            std::cout << "2 dots" << std::endl;
        }
        else if(a == 1){
            std::cout << "2 ovals" << std::endl;
        }
        else if(a == 2){
            std::cout << "Lemniscate of Bernoulli" << std::endl;
        }
        else if( a == 3){
            std::cout << "Oval with folds" << std::endl;
        }
        else if( a == 4){
            std::cout << "Oval" << std::endl;
        }
        else if(a == 5){
            std::cout << "Circle" << std::endl;
        }
        return 1;
    }

    int D_FindR(Curve &curve) {
        double phi;
        std::cout << "Enter angle in radian:" << std::endl;
        if (getNum(phi) < 0) return 0;
        double d = curve.getR(phi);
        if(d == -1){
            std::cout<<"No connection"<<std::endl;
        }
        else{
            std::cout<<"R = "<<d<<std::endl;
        }
        return 1;
    }

    int D_FindCurvature(Curve &curve) {
        double phi;
        std::cout << "Enter angle in radian:" << std::endl;
        if (getNum(phi) < 0) return 0;
        double d = curve.getCurvature(phi);
        if(d == -1){
            std::cout<<"No connection"<<std::endl;
        }
        else{
            std::cout<<"Radius of curvature R = "<<d<<std::endl;
        }
        return 1;
    }

    int D_GetCoordinates(Curve &curve) {
        Pol_Coordinate *arr = curve.getInflectionpoint();
        if (arr) {
            for (int i = 0; i < 4; ++i) {
                std::cout << "p = " << arr[i].p << " phi = " << arr[i].phi << std::endl;
            }
        }
        else{
            std::cout<<"No connection"<<std::endl;
        }
        return 1;
    }

    int D_GetFormula(Curve &curve) {
        char* buf = new char[80];
        curve.getFormula(buf);
        std::cout << buf<<std::endl;
        delete[](buf);
        return 1;
    }
}