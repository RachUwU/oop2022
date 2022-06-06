#ifndef INC_2LAB4_DIALOG_H
#define INC_2LAB4_DIALOG_H
#include "Dialog.h"
#include <limits>
namespace Dialog {
    int enterdialog(const char* msg, int min, int max, int& m){//ввод в переменную m с проверкой на то чтобы оно было бльше min  и меньше max
        const char *pr = "";
        do{
            std::cout << pr << std::endl;
            std::cout << msg<<std::endl;
            pr = "you are wrong repeat input";
            if(getNum(m) < 0)
                return 0;
        }while( m > max || m < min);
        return 1;
    }
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
    int D_Show(Table& table){
        std::cout<<table;
        return 1;
    }
    int D_Add(Table& table){
        int games;
        enterdialog("How many games", 0, INT_MAX, games);
        int choice;
        std::cout<<"Choose metod: \n";
        enterdialog("1. empty\n2. manually\n", 0, 3, choice);
        if(choice == 1){
            for(int i = 0; i < games; i++){
                string date;
                getDate(date);
                table.addMatch(*(new Game(move(date))));
            }
        }
        else if (choice == 2){
            for(int i = 0; i < games; i++){
                string enemyteam, date;
                getDate(date);
                std::cout<<"Please enter enemyteamname\n";
                std::cin>>enemyteam;
                int goal;
                enterdialog("Please enter how many goalkeepers:\n", 0, 10, goal);
                int defenders;
                enterdialog("Please enter how many defenders:\n", 0, 10, defenders);
                int strikers;
                enterdialog("Please enter how many striker:\n", 0, 10, strikers);
                auto game = new Game(date, enemyteam);
                for(int j = 0; j < goal; j++){
                    std::cout<<"Please enter goalkeeper's name:\n";
                    string name;
                    cin>>name;
                    game->addNew(name, goalkeeperrole);
                }
                for(int j = 0; j < defenders; j++){
                    std::cout<<"Please enter defender's name:\n";
                    string name;
                    cin>>name;
                    game->addNew(name, defenderrole);
                }
                for(int j = 0; j < strikers; j++){
                    std::cout<<"Please enter striker's name:\n";
                    string name;
                    cin>>name;
                    game->addNew(name, strikerrole);
                }
                table.addMatch(*game);
            }
        }
        return 1;
    }
    int D_Find(Table& table){
        string date;
        getDate(date);
        if(auto game = table.findGame(date)) {
            cout << *game;
        }
        else{
            std::cout<<"No game was found\n";
        }
        return 1;
    }
    int D_Delete(Table& table){
        string date;
        getDate(date);
        table.deleteGame(date);
        return 1;
    }
    int D_MofifyGame(Table& table){
        string date;
        getDate(date);
        if(auto game = table.findGame(date)) {
            const char *msgs[] = {"0. Quit modifier", "1. Change enemy team", "2. Change date", "3. Add new player",
                                  "4. Change ingametime", "5. Change penaltytime",
                                  "6. Change Goalkeeper's shots at goal", "7. Change Goalkeeper's successful defence",
                                  "8. Change Strikers Goals", "9. Change striker's nonGoals", "10. Show",
                                  "11. Delete Player", "12. Change player name"};
            const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
            int (*fptr[])(Game &) = {nullptr, D1_ChangeName, D1_ChangeDate, D1_AddPlayer, D1_ChangeIngametime,
                                     D1_ChangePenaltytime, D1_ChangeGoalkeeper, D1_ChangeGoalkeeperSuc,
                                     D1_ChangeStriker, D1_ChangeStrikerSuc, D1_Show, D1_DeletePlayer, D1_ChangePLayerInitials};
            int rc;
            while ((rc = dialog(msgs, NMsgs))) {
                if (!fptr[rc](*game)) break;
            }
        }
        else{
            std::cout<<"No game was found\n";
        }
        return 1;
    }
    int D_ChangeTeamname(Table& table){
        std::cout<<"Please enter new team name:\n";
        string name;
        cin>>name;
        table.setTeamName(name);
        return 1;
    }
    int D_ChangeCoach(Table& table){
        std::cout<<"Please enter new Coach name:\n";
        string name;
        cin>>name;
        table.setCoachName(name);
        return 1;
    }
    int D1_ChangeName(Game& game){
        std::cout<<"Please enter enemy team:\n";
        string enemyteam;
        cin>>enemyteam;
        game.setEnemyteam(enemyteam);
        return 1;
    }
    int D1_ChangeDate(Game& game){
        string date;
        getDate(date);
        game.setDate(date);
        return 1;
    }
    int D1_AddPlayer(Game& game){
        std::cout<<"Please enter player's name:\n";
        string name;
        cin>>name;
        string role;
        std::cout<<"Please enter role\n";
        cin>>role;
        if(role == "defender"){
            game.addNew(name, defenderrole);
        }
        else if(role == "striker"){
            game.addNew(name, strikerrole);
        }
        else if(role == "goalkeeper"){
            game.addNew(name, goalkeeperrole);
        }
        else std::cout<<"No such role. You can only set defender, striker, goalkeeper\n";
        return 1;
    }
    int D1_ChangeIngametime(Game& game){
        string name;
        std::cout<<"Please enter name:\n";
        std::cin>>name;
        int time;
        enterdialog("Change ingame time\n", 0, 90, time);
        game.changePlayerInGameTime(name, time);
        return 1;
    }
    int D1_ChangePenaltytime(Game& game){
        string name;
        std::cout<<"Please enter name:\n";
        std::cin>>name;
        int time;
        enterdialog("Change penalty time\n", 0, 90, time);
        game.changePlayerPenaltyTime(name, time);
        return 1;
    }
    int D1_ChangeGoalkeeper(Game& game){
        string name;
        std::cout<<"Please enter name:\n";
        std::cin>>name;
        auto it = game.findbyname(name);
        if(it != game.end()) {
            if ((*it)->getRole() != goalkeeperrole) {
                cout << "It's not a goalkeeper\n";
                return 1;
            }
            int shots;
            enterdialog("Change goalkeeper's shots at goal\n", 0, 90, shots);
            game.changeGoalkeeperShots(name, shots);
        }
        else{
            cout<<"No player with this name\n";
        }
        return 1;
    }
    int D1_ChangeGoalkeeperSuc(Game& game){
        string name;
        std::cout<<"Please enter name:\n";
        std::cin>>name;
        auto it = game.findbyname(name);
        if(it != game.end()) {
            if ((*it)->getRole() != goalkeeperrole) {
                cout << "It's not a goalkeeper\n";
                return 1;
            }
            int shots;
            enterdialog("Change goalkeeper's successful defence\n", 0, 90, shots);
            game.changeGoalkeeperSuccess(name, shots);
        }
        else{
            cout<<"No player with this name\n";
        }
        return 1;
    }
    int D1_ChangeStriker(Game& game){
        string name;
        std::cout<<"Please enter name:\n";
        std::cin>>name;
        auto it = game.findbyname(name);
        if(it != game.end()) {
            if ((*it)->getRole() != strikerrole) {
                cout << "It's not a striker\n";
                return 1;
            }
            int shots;
            enterdialog("Change striker's goals\n", 0, 90, shots);
            game.changeStrikerGoals(name, shots);
        }
        return 1;
    }
    int D1_ChangeStrikerSuc(Game& game){
        string name;
        std::cout<<"Please enter name:\n";
        std::cin>>name;
        auto it = game.findbyname(name);
        if(it != game.end()) {
            if ((*it)->getRole() != strikerrole) {
                cout << "It's not a striker\n";
                return 1;
            }
            int shots;
            enterdialog("Change striker's non-goals\n", 0, 90, shots);
            game.changeStrikerNongoals(name, shots);
        }
        else{
            cout<<"No player with this name\n";
        }
        return 1;
    }
    int D1_Show(Game& game){
        cout<<game;
        return 1;
    }
    int D1_DeletePlayer(Game& game){
        cout<<"Please enter name:\n";
        string name;
        cin>>name;
        game.delPlayer(name);
        return 1;
    }
    int D1_ChangePLayerInitials(Game& game){
        cout<<"Please enter player who you want to chage name:\n";
        string name;
        cin>>name;
        auto player = game.findbyname(move(name));
        if(player != game.end()){
            string newname = entername(game);
            (*player)->setName(move(newname));
        }
        else{
            std::cout<<"No player with this name was found\n";
        }
        return 1;
    }
    bool correct(const std::string &str)
    {
        if (str.size() != 8)
            return false; // incorrect form
        std::size_t firstColon = str.find('.');
        std::size_t secondColon = str.rfind('.'); // searches from end to begin
        if (firstColon != 2 || secondColon != 5)
            return false; // incorrect positions of colon(s)
        std::string DD = str.substr(0, 2);
        std::string MM = str.substr(3, 2);
        std::string YY = str.substr(6, 2);
        char* end;
        int H = std::stoi(DD);
        int M = std::stoi(MM);
        int S = std::stoi(YY);
        // if all of these statements resturn true, function returns false
        return !(H < 1 || H > 31 || M < 1 || M > 12 || S < 0 || S > 99);
    }
    void getDate(std::string& str){
        const char *pr = "";
        do {
            std::cout <<pr<< "Please enter date in format(DD.MM.YY):\n";
            std::cin >> str;
            pr = "You are wrong!\n";
        }while(!correct(str));
    }
    std::string entername(Game& game){
        string str;
        vector<player*>::iterator it;
        const char* ermes = "";
        do{
            std::cout<<ermes<<"Please enter new name:\n";
            std::cin>>str;
            ermes = "This name is already used by another player!\n";
            it = game.findbyname(str);
        } while(it != game.end());
        return str;
    }
}
#endif //INC_2LAB4_DIALOG_H
