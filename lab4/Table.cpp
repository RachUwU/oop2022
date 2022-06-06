#include <utility>

#include "Table.h"
namespace SportTeam{
    using namespace std;
    //player
    player& player::setName(string name){
        initials = std::move(name);
        return *this;
    }
    player & player::setingametime(int time){
        ingametime = time;
        return *this;
    }
    player& player::setpenaltytime(int time){
        penaltytime = time;
        return *this;
    }
    std::ostream& operator<<(ostream & os, const player& player){
        return player.print(os);
    }
    ostream& player::show(ostream& os) const{
        cout<<"Initials: "<<initials<<"\nTime on the field: "<<ingametime<<"\nPenalty time: "<<penaltytime<<endl;
        return os;
    }
    ostream& player::printRole(ostream& os) const{
        int role = getRole();
        if(role == goalkeeperrole){
            return os<<"\nGoalkeeper\n";
        }
        else if(role == defenderrole){
            return os<<"\nDefender\n";
        }
        else return os<<"\nStriker\n";
    }
    //goalkeeper
    class goalkeeper& goalkeeper::setSuccess(int suc){
        successfulldefence = suc;
        return *this;
    }
    class goalkeeper& goalkeeper::setShots(int shots){
        shotsatgoal = shots;
        return *this;
    }
    ostream& goalkeeper::print(ostream &os) const {
        printRole(os);
        this->show(os)<<"Shots on goal: "<<shotsatgoal<<"\nCatched: "<<successfulldefence<<"\nMissed goals: "<< shotsatgoal-successfulldefence<<endl;
        return os;
    }
    //defender
    ostream& defender::print(ostream &os) const {
        printRole(os);
        this->show(os);
        return os;
    }
    //striker
    class striker& striker::setGoals(int goal){
        goals = goal;
        return *this;
    }
    class striker& striker::setNongoals(int nongoal){
        nongoals = nongoal;
        return *this;
    }
    ostream& striker::print(ostream &os) const {
        printRole(os);
        this->show(os)<<"Goals: "<<goals<<"\nMisses: "<<nongoals<<endl;
        return os;
    }
    //Game
    Game::Game(int size) {
        if(size < 0) throw invalid_argument("Size is lower than 0\n");
        date = "00.00.00";
        enemyteam = "enemy";
        team.reserve(size);
        for(int i = 0; i < size; i++){
            team.push_back(new defender);
        }
        teamsize = size;
    }
    Game::Game(int goal, int def, int str, string dat, string name){
        date = move(dat);
        enemyteam = move(name);
        teamsize = goal + def + str;
        team.reserve(teamsize);
        for(int i = 0; i < goal; ++i){
            team.push_back(new goalkeeper);
        }
        for(int i = 0; i < def; ++i){
            team.push_back(new defender);
        }
        for(int i = 0; i < str; ++i){
            team.push_back(new striker);
        }
    }
    Game& Game::setDate(int day, int month, int year){
        string dat = to_string(day)+"."+to_string(month) + "."+to_string(year);
        date = dat;
        return *this;
    }
    void Game::getTeamInfo() const{
        for(auto iter : team) {
            cout << *iter << endl;
        };
    }
    Game& Game::addNew(string name, int role){
        if(findbyname(name) == team.end()) {
            if (role == goalkeeperrole) {
                team.push_back(new goalkeeper(move(name)));
            } else if (role == defenderrole) {
                team.push_back(new defender(move(name)));
            } else team.push_back(new striker(move(name)));
            teamsize++;
        }
        return *this;
    }
    Game& Game::changePlayerName(string oldname, string name){
        auto it = findbyname(std::move(oldname));
        if(it == team.end()){
            cout<<"No player with this name\n";
        }
        else{
            (*it)->setName(move(name));
        }
        return *this;
    }
    Game& Game::changePlayerInGameTime(string name, int time){
        auto it = findbyname(std::move(name));
        if(it == team.end()){
            cout<<"No player with this name\n";
        }
        else{
            (*it)->setingametime(time);
        }
        return *this;
    }
    Game& Game::changePlayerPenaltyTime(string name, int time){
        auto it = findbyname(std::move(name));
        if(it == team.end()){
            cout<<"No player with this name\n";
        }
        else{
            (*it)->setpenaltytime(time);
        }
        return *this;
    }
    Game& Game::changeGoalkeeperShots(string name, int shots){
        auto it = findbyname(std::move(name));

        if((*it)->getRole() != goalkeeperrole){
            throw invalid_argument("It's not goalkeeper\n");
        }
        auto g = dynamic_cast<goalkeeper *>(*it);
        g->setShots(shots);
        return *this;
    }
    Game& Game::changeGoalkeeperSuccess(string name, int suc){
        auto it = findbyname(std::move(name));
        if((*it)->getRole() != goalkeeperrole){
            throw invalid_argument("It's not goalkeeper\n");
        }
        auto g = dynamic_cast<goalkeeper *>(*it);
        g->setSuccess(suc);
        return *this;
    }
    Game& Game::changeStrikerGoals(string name, int goal){
        auto it = findbyname(std::move(name));
        if((*it)->getRole() != strikerrole){
            throw invalid_argument("It's not striker\n");
        }
        auto g = dynamic_cast<striker *>(*it);
        g->setGoals(goal);
        return *this;
    }
    Game& Game::changeStrikerNongoals(string name, int nongoal){
        auto it = findbyname(std::move(name));
        if((*it)->getRole() != strikerrole){
            throw invalid_argument("It's not striker\n");
        }
        auto g = dynamic_cast<striker *>(*it);
        g->setNongoals(nongoal);
        return *this;
    }
    std::ostream& operator<<(ostream & os, const Game& game){
        cout<<"Enemy team: "<<game.enemyteam<<" Team size: "<<game.teamsize<<endl;
        for(auto it: game.team){
            cout<<*it;
        }
        return os;
    }
    Game& Game::delPlayer(string name){
        auto it = findbyname(move(name));
        if(it == team.end()){
            cout<<"No player with this name\n";
        }
        else {
            team.erase(it);
            teamsize--;
        }
        return *this;
    }
    vector<player*>::iterator Game::findbyname(string name){
        auto it = team.begin();
        for(auto end = team.end(); it != end; it++){
            if((*it)->getname() == name){
                return it;
            }
        }
        return it;
    }
    //Table
    Table& Table::addMatch(Game& game){
        matches.add(game.getDate(), game);
        return *this;
    }
    Game* Table::findGame(string date) {
        auto i = matches.find(date);
        if(!i){
            return nullptr;
        }
        return i;
    }
    Table& Table::deleteGame(string date){
        auto game = findGame(date);
        if(!game){
            std::cout<<"No game with this name\n";
        }
        else matches.delItem(date);
        return *this;
    }
    Table& Table::showTable(){
        for(const auto & matche : matches){
            cout<<matche.first<<" "<<matche.second;
        }
        return *this;
    }
    std::ostream& operator<<(ostream & os, const Table& table){
        cout<<"Team: "<<table.teamname<<" Coach: "<<table.coach<<endl;
        for(int i = 0; i < table.matches.getcsize(); i++){
            cout<<table.matches[i].second.getDate()<<"  Against: ";
            cout<<table.matches[i].second.getEnemyTeam()<<endl;
        }
        return os;
    }
}