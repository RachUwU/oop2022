#include "2lab.h"
using namespace Cassini;
int main() {
    Curve curve;
    const char *msgs[] = {"0. Quit", "1. Set", "2. Set a", "3. Set c","4. GetForm", "5. Find R", "6. Find Curvature", "7. Find Coord of Inflect points", "8. Get formula"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*fptr[])(Curve&) = {nullptr, D_Set, D_SetA, D_SetC, D_Getform, D_FindR, D_FindCurvature, D_GetCoordinates, D_GetFormula};
    int rc;
    while ((rc = dialog(msgs, NMsgs))){
        if (!fptr[rc](curve)) break;
    }
    return 0;
}
