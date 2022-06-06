#ifndef INC_2LAB4WITHTEMPLATE_DIALOG_H
#define INC_2LAB4WITHTEMPLATE_DIALOG_H
#include <iostream>
#include "Table.h"
using namespace SportTeam;
namespace Dialog {
    template<class T>
    int getNum(T &a) {
        std::cin >> a;
        if (!std::cin.good())
            return -1;
        return 1;
    }

    int dialog(const char *msgs[], int N);
    int D_Show(Table& table);
    int D_Add(Table& table);
    int D_Find(Table& table);
    int D_Delete(Table& table);
    int D_MofifyGame(Table& table);
    int D_ChangeCoach(Table& table);
    int D_ChangeTeamname(Table& table);
    int D1_ChangeName(Game& game);
    int D1_ChangeDate(Game& game);
    int D1_AddPlayer(Game& game);
    int D1_ChangeIngametime(Game& game);
    int D1_ChangePenaltytime(Game& game);
    int D1_ChangeGoalkeeper(Game& game);
    int D1_ChangeGoalkeeperSuc(Game& game);
    int D1_ChangeStriker(Game& game);
    int D1_ChangeStrikerSuc(Game& game);
    int D1_Show(Game& game);
    int D1_DeletePlayer(Game& game);
    int D1_ChangePLayerInitials(Game& game);
    bool correct(const std::string &str);
    void getDate(std::string& str);
    std::string entername(Game& game);
}
#endif //INC_2LAB4WITHTEMPLATE_DIALOG_H
