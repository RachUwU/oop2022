#include "Dialog.h"

using namespace  Dialog;
int main() {
    Table table;
    const char *msgs[] = {"0. Quit", "1. Show table", "2. Add new Game in table", "3. Find by date", "4. Delete by date", "5. ModifyGame", "6. Change Team name", "7. Change Coach name"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*fptr[])(Table&) = {nullptr, D_Show, D_Add, D_Find, D_Delete, D_MofifyGame, D_ChangeTeamname, D_ChangeCoach};
    int rc;
    while ((rc = dialog(msgs, NMsgs))){
        if (!fptr[rc](table)) break;
    }
    return 0;
}
