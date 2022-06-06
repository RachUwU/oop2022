#include "Dialog.h"
using namespace Dialog;
using namespace BinaryVector;
int main() {
    BinVector binVector;
    const char *msgs[] = {"0. Quit", "1. Set with Int", "2. Set with char","3. Getsize", "4. Print","5. String", "6. OR", "7. AND", "8. XOR", "9. Addition", "10. Limited", "11. PlusPlus", "12. GetElement", "13. Sum"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*fptr[])(BinVector&) = {nullptr, D_SetWithInt, D_SetWithString, D_GetSize, D_Print, D_String, D_OR, D_AND, D_XOR, D_Addition, D_LimitedVector, D_PLUSPLUS, D_GetElement, D_Sum};
    int rc;
    while ((rc = dialog(msgs, NMsgs))){
        if (!fptr[rc](binVector)) break;
    }
    return 0;
}
