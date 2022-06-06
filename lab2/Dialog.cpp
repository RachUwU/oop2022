#include "dinamic.h"
#include "Dialog.h"
namespace Dialog {
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
    int D_SetWithInt(BinVector& a){
        const char *pr = "";
        int t;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter int:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(t) < 0)
                return 0;
        } while (t < 0);
        a.SetBinVector(t);
        return 1;
    }
    int D_SetWithString(BinVector& a){
        const char *pr = "";
        int t;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter int:"<<std::endl;
            pr = "you are wrong repeat input";
            if (getNum(t) < 0)
                return 0;
        } while (t < 0);
        std::cout << "Enter str["<<t<<"]:" << std::endl;
        char* str = new char[t];
        for(int i = 0; i < t; i++) {
            std::cin >> str[i];
        }
        str[t] = '\0';
        a.SetBinVector(str);
        delete[] str;
        return 1;
    }
    int D_GetSize(BinVector& a){
        std::cout<<"Size: "<<a.getsize()<<std::endl;
        return 1;
    }
    int D_Print(BinVector& a){
        std::cout<<"BinVector: "<<a<<std::endl;
        return 1;
    }
    int D_String(BinVector& a){
        std::cin>>a;
        return 1;
    }
    int D_OR(BinVector& a){
        const char *pr = "";
        int t;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter int:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(t) < 0)
                return 0;
        } while (t < 0);
        BinVector b;
        b.SetBinVector(t);
        BinVector c;
        c = a|b;
        a.PrintVector(std::cout);
        b.PrintVector(std::cout);
        std::cout<<"\n";
        c.PrintVector(std::cout);
        return 1;
    }
    int D_AND(BinVector& a){
        const char *pr = "";
        int t;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter int:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(t) < 0)
                return 0;
        } while (t < 0);
        BinVector b;
        b.SetBinVector(t);
        BinVector c;
        c = a.logic_AND(b);
        a.PrintVector(std::cout);
        b.PrintVector(std::cout);
        std::cout<<"\n";
        c.PrintVector(std::cout);
        return 1;
    }
    int D_XOR(BinVector& a){
        const char *pr = "";
        int t;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter int:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(t) < 0)
                return 0;
        } while (t < 0);
        BinVector b;
        b.SetBinVector(t);
        BinVector c;
        c = a.logic_XOR(b);
        a.PrintVector(std::cout);
        b.PrintVector(std::cout);
        std::cout<<"\n";
        c.PrintVector(std::cout);
        return 1;
    }
    int D_Addition(BinVector& a) {
        std::cout<<"Addition:\n";
        BinVector b;
        b = -a;
        a.PrintVector(std::cout);
        std::cout<<"\n";
        b.PrintVector(std::cout);
        return 1;
    }
    int D_LimitedVector(BinVector& a) {
        std::cout<<"Limited:\n";
        BinVector b;
        b = a.LimitedVector();
        a.PrintVector(std::cout);
        std::cout<<"\n";
        b.PrintVector(std::cout);
        return 1;
    }
    int D_PLUSPLUS(BinVector& a){
        BinVector a1(a);
        BinVector b = a++;
        std::cout<<"Postfix:\n"<<b;
        a.PrintVector();
        BinVector c = ++a1;
        std::cout<<"Prefix:\n"<<c;
        std::cout<<a1;
        return 1;
    }
    int D_GetElement(BinVector& a){

        const char *pr = "";
        int k = a.getsize();
        printf("size: %d\n", k);
        int t;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter int:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(t) < 0)
                return 0;
        } while (t < 0 || t >= k);
        printf("char: %d\n", a[t]);
        return 1;
    }
    int D_Sum(BinVector& a){
        const char *pr = "";
        int t;
        do {
            std::cout << pr << std::endl;
            std::cout << "Enter int:" << std::endl;
            pr = "you are wrong repeat input";
            if (getNum(t) < 0)
                return 0;
        } while (t < 0);
        BinVector b;
        b.SetBinVector(t);
        std::cout<<a<<"+\n"<<b<<"=\n";
        a += b;
        std::cout<<a<<std::endl;
        return 1;
    }
}