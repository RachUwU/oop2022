#include "dinamic.h"
#include <cstring>

namespace BinaryVector{
    BinVector::BinVector(const BinVector& q): size(q.size), array(nullptr) {
        std::cout<<"Copy constructor\n";
        if(size){
            array = new char[size];
        }
        for(int i = 0; i < q.size; i++){
            array[i] = q.array[i];
        }
    }
    BinVector& BinVector::operator =(const BinVector& a){
        if(this != &a){
            delete[] array;
            array = nullptr;
            if((size = a.size) != 0){
                array = new char[size];
                for (int i = 0; i < a.size; i++){
                    array[i] = a.array[i];
                }
            }
        }
        return *this;
    }
    BinVector BinVector::SetBinVector(int c){
        if(c < 0) throw std::exception();
        if(size){
            delete[] array;
            array = nullptr;
        }
        int c1 =c;
        int n = 0;
        while(c1 != 0){
            c1 = c1/2;
            n++;
        }
        size = n;
        array = new char[size];
        while(c != 0){
            if(c%2 == 0){
                array[n - 1] = (char) 0;
            }
            else{
                array[n - 1] = (char) 1;
            }
            c = c/2;
            n--;
        }
        return *this;
    }
    char& BinVector::operator []( int i){
        if(i < 0 || i >= size){
            throw std::exception();
        }
        return array[i];
    }
    BinVector BinVector::SetBinVector(const char* str){
        if(size){
            delete[] array;
            array = nullptr;
        }
        size = strlen(str);
        array = new char[size];
        for (int i = 0; i < size; i++) {
            if (str[i] == '0') {
                array[i] = (char) 0;
            } else if(str[i] == '1'){
                array[i] = (char) 1;
            }
            else{
                throw std::exception();
            }
        }
        return *this;
    }
    std::ostream & BinVector::PrintVector(std::ostream& c) const{
        for(int i = 0; i < size; i++) {
            c << (int)array[i];
        }
        c<<::std::endl;
        return c;
    }
    [[nodiscard]] BinVector BinVector::logic_AND(const BinVector &r)const{
        BinVector log;
        int siz;
        if(this->size > r.size){
            log.size = this->size;
            siz = r.size;
        }
        else{
            log.size = r.size;
            siz = this->size;
        }
        log.array = new char[log.size];
        int i = log.size - 1;
        for(int j = 1; i >= log.size - siz; i--, j++){
            log.array[i] = (char)(array[size-j] && r.array[r.size -j]);
        }

        for(; i >= 0; i--){
            log.array[i] = 0;
        }
        return log;
    }
    [[nodiscard]] BinVector BinVector::logic_XOR(const BinVector &r)const{
        BinVector log;
        int siz;
        int k;
        if(this->size > r.size){
            log.size = this->size;
            siz = r.size;
            k = 1;
        }
        else{
            log.size = r.size;
            siz = this->size;
            k = 2;
        }
        log.array = new char[log.size];
        int i = log.size - 1;
        for(int j = 1; i >=log.size - siz; i--, j++){
            log.array[i] = (char)(this->array[this->size - j] ^ r.array[r.size - j]);
        }
        if(k == 1){
            for(; i >= 0; i--){
                log.array[i] = (char)(this->array[i]^0);
            }
        }
        else{
            for(; i >= 0; i--){
                log.array[i] = (char)(r.array[i]^0);
            }
        }
        return log;
    }
    BinVector BinVector::LimitedVector(){
        BinVector log;
        int siz = size;
        int before = 0;
        for(int i = 0; i < size; i++){
            if(array[i] == 1)break;
            else{
                before++;
            }
        }
        int i = size - 1;
        while(array[i] == 0){
            i--;
            siz--;
        }
        siz-=before;
        log.size = siz;
        int j = siz - 1;
        log.array = new char[log.size];
        while(i >= before){
            log.array[j] = array[i];
            j--;
            i--;
        }
        return log;
    }
    std::istream & operator >>(std::istream & istream, BinVector & vec){
        int siz;
        istream>>siz;
        for (int i = 0; i < vec.size; i++) {
            char a;
            istream >> a;
            if (a == '0') {
                vec.array[i] = (char) 0;
            } else if( a == '1'){
                vec.array[i] = (char) 1;
            }
            else{
                throw std::exception();
            }
        }
        vec.size = siz;
        return istream;
    }
    std::ostream & operator <<(std::ostream & ostream, BinVector & vec){
        for(int i = 0; i < vec.size; i++) {
            ostream << (int)vec.array[i];
        }
        ostream<<::std::endl;
        return ostream;
    }
    BinVector BinVector::operator-(){
        BinVector log;
        int siz = this->size;
        log.size = siz;
        log.array = new char[log.size];
        for(int i = 0; i < log.size; i++){
            log.array[i] = (char)(array[i] == 0);
        }
        return log;
    }
    BinVector BinVector::operator++(){
        int i = size -1;
        while(i != - 1){
            if(array[i] == 0){
                array[i] = 1;
                break;
            }
            else{
                array[i] = 0;
                i--;
            }
        }
        if(i == - 1 && array[i+1] == 0){
            delete[] array;
            size++;
            array = new char[size];
            array[0] = 1;
            for(int j = 1; j < size; j++){
                array[j] = 0;
            }
        }
        return *this;
    }
    const BinVector BinVector::operator++(int t){
        BinVector log(*this);
        int i = size -1;
        while(i != - 1){
            if(array[i] == 0){
                array[i] = 1;
                break;
            }
            else{
                array[i] = 0;
                i--;
            }
        }
        if(i == - 1 && array[i+1] == 0){
            delete[] array;
            size++;
            array = new char[size];
            array[0] = 1;
            for(int j = 1; j < size; j++){
                array[j] = 0;
            }
        }
        return log;
    }
    BinVector operator |(BinVector & a, BinVector & b) {
        BinVector log;
        int siz;
        int k = -1;
        if(a.size > b.size){
            log.size = a.size;
            siz = b.size;
            k = 1;
        }
        else{
            log.size = b.size;
            siz = a.size;
            k = 2;
        }
        log.array = new char[log.size];
        int i = log.size - 1;
        for(int j = 1; i >=log.size - siz; i--, j++){
            log.array[i] = (char)(a.array[a.size - j] | b.array[b.size - j]);
        }
        if(k == 1){
            for(; i >= 0; i--){
                log.array[i] = (char)(a.array[i] | 0);
            }
        }
        else{
            for(; i >= 0; i--){
                log.array[i] = (char)(b.array[i] | 0);
            }
        }
        return log;
    }
    void BinVector::operator +=(const BinVector& q){
        BinVector c;
        if(this->size>= q.size) {
            c = *this;

        }
        else {
            c.size = q.size;
            c.array = new char[c.size];
            for(int i = 0; i < c.size - this->size; i++) {
                c.array[i] = 0;
            }
            for(int i = c.size - this->size, j = 0; i < c.size; i++, j++) {
                c.array[i] = this->array[j];
            }
        }
        int i = c.size - 1;
        int k = q.size -1;
        int rank = 0;
        while(i != c.size -1 - q.size){
            int sum = c.array[i] + q.array[k] + rank;
            if(sum == 0){
                c.array[i] = 0;
                rank = 0;
            }
            else if (sum == 1){
                c.array[i] = 1;
                rank = 0;
            }
            else if(sum == 2){
                c.array[i] = 0;
                rank = 1;
            }
            else {
                c.array[i] = 1;
                rank = 1;
            }
            i--;
            k--;
        }
        while(i != -1 && rank == 1){
            if(c.array[i] == 1){
                c.array[i] = 0;
            }
            else{
                c.array[i] = 1;
                rank = 0;
            }
            i--;
        }
        if(rank == 1 && i <= -1){
            BinVector d;
            d.size = c.size+1;
            d.array = new char[d.size];

            for(int j = 0; j < c.size; j++) {
                d.array[j + 1] = c.array[j];
            }
            d.array[0] = 1;
            c = d;
        }
        *this = c;
    }
}

