#ifndef CASSINI_LIBRARY_H
#define CASSINI_LIBRARY_H

namespace Cassini {
    struct Pol_Coordinate{
        double p;
        double phi;
    };
    class Curve {
        double a;
        double c;
    public:
        Curve();
        Curve(double a, double c);
        Curve *set(double x, double y);
        Curve *set_a(double x);
        Curve *set_c( double y);
        inline double get_a() const;
        inline double get_c() const;
        int getform() const;
        double getR(double phi, int state = 1) const;
        double getCurvature(double phi) const;
        Pol_Coordinate* getInflectionpoint() const;
        void getFormula(char *& buf) const;
    };
}

#endif //CASSINI_LIBRARY_H
