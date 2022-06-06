#ifndef INC_2LAB4_TABLE_H
#define INC_2LAB4_TABLE_H
#include <iostream>
#include <utility>
#include <vector>
#include "simpletable.h"
namespace SportTeam{
    using namespace std;
    enum Roles{
        goalkeeperrole,
        defenderrole,
        strikerrole,
    };
    ///\brief This is abstract class which describes common parameters of players
    ///
    ///This class is the foundation for another classes: class goalkeeper, class defender, class striker.
    ///It contains information about how much the player was in the game, how much time he received, and also contains his initials
    class player{
    private:
        int ingametime;
        string initials;
        int penaltytime;
    protected:
        ///This virtual function is used for output for stream
        ///@see friend operator<<
        virtual ostream& print(ostream& os) const = 0;
        ///This function is used for output for stream main player's information
        ostream& show(ostream & os) const;
    public:
        ///default constructor
        explicit player(int igtime = 0, string  name = "defaultov", int ptime = 0): ingametime(igtime), initials(std::move(name)), penaltytime(ptime){};
        ///getter for initials
        [[nodiscard]] string getname() const{return initials;};
        ///getter for ingametime
        [[nodiscard]] int getIngametime() const{return  ingametime;};
        ///getter fot penaltytime
        [[nodiscard]] int getPenaltytime() const{return  penaltytime;};
        ///setter for initials
        player & setName(string name);
        ///setter for ingametime
        player & setingametime(int time);
        ///setter for penaltytime
        player& setpenaltytime(int time);
        ///This function returns role of the player
        [[nodiscard]] virtual int getRole() const = 0;
        ///This metod is used for printing info in output stream
        ostream& printRole(ostream& os) const;
        friend std::ostream& operator<<(ostream & os, const player& player);
    };
    class goalkeeper: public player{
    private:
        int shotsatgoal;
        int successfulldefence;
    protected:
        ///This metod is used for printing info in output stream
        virtual ostream & print(ostream& os)const;
    public:
        ///construcor with initials
        explicit goalkeeper(string name):player(0, std::move(name), 0), shotsatgoal(0), successfulldefence(0){};
        ///default constructor
        explicit goalkeeper(int igtime = 0, string  name = "vratarev", int ptime = 0, int goal = 0, int suc = 0):player(igtime, std::move(name), ptime), shotsatgoal(goal), successfulldefence(suc){};
        ///setter for successful
        goalkeeper& setSuccess(int suc);
        ///setter for unsucceessful
        goalkeeper& setShots(int shot);
        ///getter for successful
        [[nodiscard]] int getSuccess() const {return successfulldefence;};
        ///getter for unsuccessfull
        [[nodiscard]] int getUnuccess() const{return shotsatgoal - successfulldefence;};
        [[nodiscard]] virtual int getRole() const{ return goalkeeperrole;};
    };
    class defender: public player{
    protected:
        virtual ostream & print(ostream& os)const;
    public:
        ///this is constructer initialised with initials
        explicit defender(int igtime = 0, string  name = "zashitnik", int ptime = 0): player(igtime, std::move(name), ptime){};
        ///this is default constructor
        explicit defender(string name): player(0, std::move(name), 0){};
        [[nodiscard]] virtual int getRole() const{return defenderrole;};
    };
    class striker: public player{
    private:
        int goals;
        int nongoals;
    protected:
        virtual ostream & print(ostream& os)const;
    public:
        ///this is default constructor
        explicit striker(int igtime = 0, string  name = "napadayushiy", int ptime = 0, int goal = 0, int nongoal = 0):player(igtime, std::move(name), ptime), goals(goal), nongoals(nongoal){};
        ///this is constructor for initialisation with initials
        explicit striker(string  name): player(0, std::move(name), 0), goals(0), nongoals(0){};
        ///this i s setter for goals
        striker& setGoals(int goal);
        ///this is setter for nongoals
        striker& setNongoals(int nongoal);
        ///this is getter for goals
        [[nodiscard]] int getGoals() const{return goals;};
        ///this is getter for nongoals
        [[nodiscard]] int getNongoals() const{return nongoals;};
        [[nodiscard]] virtual int getRole() const{return strikerrole;};
    };
    class Game{
    private:
        string date;
        string enemyteam;
        int teamsize;
        vector<player*> team;
    public:
        ///this is empty constructor
        explicit Game(string date = "00.00.00", string name = "enemy"): teamsize(0), date(std::move(date)), enemyteam(move(name)){};
        ///this is constructor with initialisation with size
        explicit Game(int size);
        ///This constructor for initiallisation
        Game(int goal, int def, int str, string date = "00.00.00", string name = "enemy");
        ///This is setter for date
        Game& setDate(string dat){ date = move(dat); return *this;};
        ///This is setter for date in another format
        Game& setDate(int day, int month, int year);
        ///This is setter for enemy team name
        Game& setEnemyteam(string name){enemyteam = move(name); return *this;};
        ///This is getter for date
        [[nodiscard]] string getDate() const{return date;};
        ///THis is getter for enemy team
        [[nodiscard]] string getEnemyTeam() const{return enemyteam;};
        ///This is getter for Team info
        void getTeamInfo() const;
        ///This is getter for team size
        [[nodiscard]] int getTeamSize() const{return teamsize;};
        ///This method is for adding another player in game
        Game& addNew(string name, int role);
        ///This method is for changing player in game info
        Game& changePlayerName(string oldname, string name);
        ///This method is for changing player's in game time
        Game& changePlayerInGameTime(string name, int time);
        ///This method is for changing player in game penalty time
        Game& changePlayerPenaltyTime(string name, int time);
        ///This method is for changing player in game shots
        Game& changeGoalkeeperShots(string name, int shots);
        ///This method is for changing player in game successful
        Game& changeGoalkeeperSuccess(string name, int suc);
        ///This method is for changing player in game goals
        Game& changeStrikerGoals(string name, int goal);
        ///This method is for changing player in game nongoals
        Game& changeStrikerNongoals(string name, int nongoal);
        ///This method is for deleting player from game
        Game& delPlayer(string name);
        ///This method is for finding players by name
        vector<player*>::iterator findbyname(string name);
        vector<player*>::iterator end(){return team.end();}
        friend std::ostream& operator<<(ostream & os, const Game& game);
    };
    typedef pair<string , Game> Game_Pair;
    class Table{
    private:
        string teamname;
        string coach;
        simpletable<string, Game> matches;
    public:
        ///This is default constructor
        Table(): teamname("team"), coach("Mr x"){};
        ///This is getter for team name
        [[nodiscard]] string getTeamName() const{return teamname;};
        ///This getter for coach name
        [[nodiscard]] string getCoahName() const{return coach;};
        ///This method is for adding new game
        Table& addMatch(Game& game);
        ///This method is for finding by date
        Game* findGame(string date);
        ///This method is for deleting by date
        Table& deleteGame(string date);
        ///This method is for output
        Table& showTable();
        Table& setTeamName(string name){teamname = std::move(name); return *this;};
        Table& setCoachName(string name){coach = std::move(name); return *this;};
        friend std::ostream& operator<<(ostream & os, const Table& table);
    };
}
#endif //INC_2LAB4_TABLE_H
