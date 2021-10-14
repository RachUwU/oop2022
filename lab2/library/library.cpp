#include "library.h"
#include <iostream>
#include <cmath>
#include <sstream>

namespace Cassini{
    Curve::Curve(){
        a = 0;
        c = 1;
    }
    Curve::Curve(double a, double c){
        Curve::a = a;
        Curve::c = c;
    }
    Curve *Curve::set(double x, double y) {
        a = x;
        c = y;
        return this;
    }
    Curve *Curve::set_a(double x) {
        a = x;
        return this;
    }
    Curve *Curve::set_c( double y) {
        c = y;
        return this;
    }
    inline double Curve::get_a() const{
        return a;
    }
    inline double Curve::get_c() const{
        return c;
    }
    int Curve::getform() const {
        if (a == 0) {
            //std::cout << "2 dots" << std::endl;
            return 0;
        }
        double ratio = c / a;
        if (1 < ratio) {
            //std::cout << "2 ovals" << std::endl;
            return 1;
        } else if (ratio == 1) {
            //std::cout << "Lemniscate of Bernoulli" << std::endl;
            return 2;
        } else if (sqrt(2) / 2 < ratio && ratio < 1) {
            //std::cout << "Oval with folds" << std::endl;
            return 3;
        } else if (0 < ratio && ratio <= sqrt(2) / 2) {
            //std::cout << "Oval" << std::endl;
            return 4;
        } else if (ratio == 0) {
            //std::cout << "Circle" << std::endl;
            return 5;
        }
        return -1;
    }
    double Curve::getR(double phi, int state) const{
        double D = std::pow(c, 4) * std::pow(cos(2*phi), 2) - pow(c,2) + pow(a,4);
        if(D < 0){
            //if(state == 1)std::cout<<"No connection"<<std::endl;
            return -1;
        }
        double t = std::pow(c, 2)* cos(2*phi) + sqrt(D);
        if(t < 0){
            //if (state == 1)std::cout<<"No connection"<<std::endl;
            return -1;
        }
        double k =  std::pow(c, 2)* cos(2*phi) - sqrt(D);
        double r = sqrt(t);
        //if(state ==1) std::cout<<"R = "<<r<<std::endl;
        if(k >= 0) {
            double t1 = sqrt(k);
            //if(state == 1) std::cout<< "There is another R ="<<t1<<std::endl;
        }
        return r;
    }
    double Curve::getCurvature(double phi) const{
        double p = getR(phi, 0);
        if(p == -1){
            //std::cout<<"No connection"<<std::endl;
            return -1;
        }
        double R = (2*std::pow(a,2)*std::pow(c,3) * std::pow(p, 3))/(std::pow(c,4)- std::pow(a,4) + 3*std::pow(p,4));
        //std::cout<<"Radius of curvature R = "<<R<<std::endl;
        return R;
    }
    Pol_Coordinate* Curve::getInflectionpoint() const{
        double ratio = c/a;
        if(!(sqrt(2) / 2 < ratio && ratio < 1)){
            //std::cout<<"No Inflect points"<<std::endl;
            return nullptr;
        }
        auto* array = new Pol_Coordinate[4];
        double p = std::pow((std::pow(a,4) - std::pow(c,4))/3,0.25);
        double phi = acos(-sqrt((std::pow(a, 4)/std::pow(c, 4) - 1))/3)/2;
        array[0] = {p, phi};
        array[1] = {p, M_PI - phi};
        array[2] = {p, M_PI + phi};
        array[3] = {p, 2 * M_PI - phi};
        return array;
    }
    void Curve::getFormula(char*& buf) const{
        double t = 2*std::pow(c, 2);
        double t1 = std::pow(a,4) - std::pow(c,4);
        sprintf(buf, "x^2 + %f(x^2 - y^2) = %f", t,t1);
    }
}
