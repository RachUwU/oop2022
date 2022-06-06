#ifndef INC_2LAB3_3LAB_H
#define INC_2LAB3_3LAB_H
#include <sstream>
#include <iostream>
#include <cmath>
namespace BinaryVector{
    class BinVector{
    private:
        char* array;
        int size;
    public:
        BinVector(): size(0), array(nullptr){};
        BinVector(const BinVector& q);
        BinVector& operator =(const BinVector& a);
        ~BinVector() {delete[] array;};
        BinVector SetBinVector(int c);
        BinVector SetBinVector(const char* str);

        [[nodiscard]] int getsize() const {return size;};
        std::ostream & PrintVector(std::ostream &c = std::cout) const;
        [[nodiscard]] BinVector logic_AND(const BinVector &r)const;
        [[nodiscard]] BinVector logic_XOR(const BinVector &r)const;
        BinVector LimitedVector();
        BinVector operator -();
        BinVector operator ++();
        void operator +=(const BinVector& q);
        const BinVector operator++(int t);
        char& operator[](int i);
        friend std::istream & operator >>(std::istream & istream, BinVector & vec);
        friend std::ostream & operator <<(std::ostream & ostream, BinVector & vec);
        friend BinVector operator |(BinVector & a, BinVector & b);
    };
}
#endif //INC_2LAB3_3LAB_H
