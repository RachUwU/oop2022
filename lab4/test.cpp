#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Table.h"

using namespace SportTeam;
TEST(goalkeeper, EmptyConstructor){
goalkeeper a;
ASSERT_EQ(0, a.getSuccess());
ASSERT_EQ(0, a.getUnuccess());
ASSERT_EQ("vratarev", a.getname());
ASSERT_EQ(a.getRole(), goalkeeperrole);
ASSERT_EQ(0, a.getIngametime());
ASSERT_EQ(0, a.getPenaltytime());
}
TEST(goalkeeper, InitConstructor){
goalkeeper a(1, "aaa", 1, 1, 1);
ASSERT_EQ(1, a.getSuccess());
ASSERT_EQ(0, a.getUnuccess());
ASSERT_EQ("aaa", a.getname());
ASSERT_EQ(a.getRole(), goalkeeperrole);
ASSERT_EQ(1, a.getIngametime());
ASSERT_EQ(1, a.getPenaltytime());
}
TEST(goalkeeper, Setters){
goalkeeper a;
a.setSuccess(1);
a.setShots(1);
a.setName("aaaa");
a.setpenaltytime(1);
a.setingametime(1);
ASSERT_EQ(1, a.getSuccess());
ASSERT_EQ(0, a.getUnuccess());
ASSERT_EQ("aaaa", a.getname());
ASSERT_EQ(1, a.getIngametime());
ASSERT_EQ(1, a.getPenaltytime());
}
TEST(defender, EmptyConstructor){
defender a;
ASSERT_EQ("zashitnik", a.getname());
ASSERT_EQ(a.getRole(), defenderrole);
ASSERT_EQ(0, a.getIngametime());
ASSERT_EQ(0, a.getPenaltytime());
}
TEST(defender, InitConstructor){
defender a(1, "aaa", 1);
ASSERT_EQ("aaa", a.getname());
ASSERT_EQ(a.getRole(), defenderrole);
ASSERT_EQ(1, a.getIngametime());
ASSERT_EQ(1, a.getPenaltytime());
}
TEST(defender, Setters){
defender a;
a.setName("aaaa");
a.setpenaltytime(1);
a.setingametime(1);
ASSERT_EQ("aaaa", a.getname());
ASSERT_EQ(1, a.getIngametime());
ASSERT_EQ(1, a.getPenaltytime());
}
TEST(striker, EmptyConstructor){
striker a;
ASSERT_EQ(0, a.getGoals());
ASSERT_EQ(0, a.getNongoals());
ASSERT_EQ("napadayushiy", a.getname());
ASSERT_EQ(a.getRole(), strikerrole);
ASSERT_EQ(0, a.getIngametime());
ASSERT_EQ(0, a.getPenaltytime());
}
TEST(striker, InitConstructor){
striker a(1, "aaa", 1, 1, 1);
ASSERT_EQ(1, a.getGoals());
ASSERT_EQ(1, a.getNongoals());
ASSERT_EQ("aaa", a.getname());
ASSERT_EQ(a.getRole(), strikerrole);
ASSERT_EQ(1, a.getIngametime());
ASSERT_EQ(1, a.getPenaltytime());
}
TEST(striker, Setters){
striker a;
a.setGoals(1);
a.setNongoals(1);
a.setName("aaaa");
a.setpenaltytime(1);
a.setingametime(1);
ASSERT_EQ(1, a.getGoals());
ASSERT_EQ(1, a.getNongoals());
ASSERT_EQ("aaaa", a.getname());
ASSERT_EQ(1, a.getIngametime());
ASSERT_EQ(1, a.getPenaltytime());
}
TEST(Game, Empty_constructor){
Game game;
ASSERT_EQ(game.getDate(), "00.00.00");
ASSERT_EQ(game.getEnemyTeam(), "enemy");
ASSERT_EQ(game.getTeamSize(), 0);
}
TEST(Game, NameandDateConstructor){
Game game("01.01.12", "Barsuki");
ASSERT_EQ(game.getDate(), "01.01.12");
ASSERT_EQ(game.getEnemyTeam(), "Barsuki");
ASSERT_EQ(game.getTeamSize(), 0);
}
TEST(Game, InitConstructor){
Game game(1,1,1,"01.01.12", "Barsuki");
ASSERT_EQ(game.getDate(), "01.01.12");
ASSERT_EQ(game.getEnemyTeam(), "Barsuki");
ASSERT_EQ(game.getTeamSize(), 3);
ASSERT_EQ((*game.findbyname("zashitnik"))->getname(), "zashitnik");
ASSERT_EQ((*game.findbyname("vratarev"))->getname(), "vratarev");
ASSERT_EQ((*game.findbyname("napadayushiy"))->getname(), "napadayushiy");
}
TEST(Game, Setters){
Game game;
game.setDate("01.01.12");
game.setEnemyteam("Yar");
ASSERT_EQ(game.getDate(), "01.01.12");
ASSERT_EQ(game.getEnemyTeam(), "Yar");
}
TEST(Game, Changers){
Game game(1,1,1,"01.01.12", "Barsuki");
game.changePlayerName("zashitnik", "1");
ASSERT_EQ((*game.findbyname("1"))->getname(), "1");
game.changePlayerInGameTime("1", 1);
ASSERT_EQ((*game.findbyname("1"))->getIngametime(), 1);
game.changePlayerPenaltyTime("1", 2);
ASSERT_EQ((*game.findbyname("1"))->getPenaltytime(), 2);
auto player = dynamic_cast<goalkeeper *>(*game.findbyname("vratarev"));
game.changeGoalkeeperSuccess("vratarev", 3);
ASSERT_EQ(player->getSuccess(), 3);
game.changeGoalkeeperShots("vratarev", 4);
ASSERT_EQ(player->getUnuccess(), 1);
auto striker = dynamic_cast<SportTeam::striker *>(*game.findbyname("napadayushiy"));
game.changeStrikerGoals("napadayushiy", 5);
ASSERT_EQ(striker->getGoals(), 5);
game.changeStrikerNongoals("napadayushiy", 6);
ASSERT_EQ(striker->getNongoals(), 6);
}

TEST(Game, Exceptions){
Game game(1,1,1,"01.01.12","Barsuki");
ASSERT_ANY_THROW(game.changeStrikerNongoals("zashitnik", 1));
ASSERT_ANY_THROW(game.changeStrikerGoals("zashitnik", 1));
ASSERT_ANY_THROW(game.changeGoalkeeperSuccess("zashitnik", 1));
ASSERT_ANY_THROW(game.changeGoalkeeperShots("zashitnik", 1));
}
TEST(Game, Add_Del){
Game game(1,1,1, "01.01.12", "Barsuki");
game.addNew("new", goalkeeperrole);
ASSERT_EQ((*game.findbyname("new"))->getname(), "new");
game.delPlayer("new");
ASSERT_EQ(game.findbyname("new"), game.end());
}
TEST(Table, EmptyConstructor){
    Table table;
    ASSERT_EQ(table.getTeamName(), "team");
    ASSERT_EQ(table.getCoahName(), "Mr x");
}
TEST(Table, Setters){
    Table table;
    table.setCoachName("1");
    table.setTeamName("2");
    ASSERT_EQ(table.getTeamName(), "2");
    ASSERT_EQ(table.getCoahName(), "1");
}
TEST(Table, Add_Del){
    Table table;
    table.addMatch(*(new Game));
    ASSERT_TRUE(table.findGame("00.00.00"));
    table.deleteGame("00.00.00");
    ASSERT_EQ(table.findGame("00.00.00"), nullptr);
}
TEST(Simpletable, EmptyConstructor){
    simpletable<int, int> table;
    ASSERT_EQ(table.getcsize(), 0);
    ASSERT_EQ(table.getmsize(), 0);
}
TEST(Simpletable, Add_Del){
    simpletable<int, int> table;
    table.add(1,1);
    ASSERT_EQ(*table.find(1), 1);
    table.delItem(1);
    ASSERT_FALSE(table.find(1));
}
TEST(Simpletable, operators){
    simpletable<int, int> table;
    table.add(1,1);
    table.add(2,2);
    table.add(3,3);
    ASSERT_EQ(table[0], std::pair(1,1));
    table[0] = std::pair(4, 4);
    ASSERT_EQ(table[0], std::pair(4, 4));
    ASSERT_EQ(table.findbIndex(3), 2);
}
TEST(Simpletable, CopyConstructor){
    simpletable<int, int> table;
    table.add(1,1).add(2,2).add(3,3);
    simpletable<int, int> ctable(table);
    ASSERT_EQ(table.getcsize(), ctable.getcsize());
    ASSERT_EQ(table.getmsize(), ctable.getmsize());
    ASSERT_FALSE(&table[0] == &ctable[0]);
}
TEST(Simpletable, MoveConstructor){
    simpletable<int, int> table;
    table.add(1,1).add(2,2).add(3,3);
    simpletable<int, int> ctable(std::move(table));
    ASSERT_EQ(3, ctable.getcsize());
    ASSERT_EQ(10, ctable.getmsize());
    ASSERT_FALSE(table.getarray());
}
TEST(Simpletable, EqCopy){
    simpletable<int, int> table, ctable;
    table.add(1,1).add(2,2).add(3,3);
    ctable = table;
    ASSERT_EQ(table.getcsize(), ctable.getcsize());
    ASSERT_EQ(table.getmsize(), ctable.getmsize());
    ASSERT_FALSE(&table[0] == &ctable[0]);
}
TEST(Simpletable, EqMove){
    simpletable<int, int> table, ctable;
    table.add(1,1).add(2,2).add(3,3);
    ctable = std::move(table);
    ASSERT_EQ(3, ctable.getcsize());
    ASSERT_EQ(10, ctable.getmsize());
    ASSERT_FALSE(table.getarray());
}
TEST(Simpletable, iterator){
    simpletable<int, int> table;
    table.add(1,1).add(2,2).add(3,3);
    ConstsimpletableIt<int, int> it(&table[0]);
    ASSERT_EQ((*table.begin()), *it);
}
TEST(Iterator, EmptyConstr){
    ConstsimpletableIt<int, int > it;
    ASSERT_FALSE(it.getCur());
}
TEST(Iterator, InitConstr){
    std::pair<int, int> p(1,1);
    ConstsimpletableIt<int, int > it(&p);
    ASSERT_EQ(it.getCur(), &p);
}
TEST(Iterator, operators){
    std::pair<int, int> p(1,1);
    ConstsimpletableIt<int,int> it1(&p), it2(&p), it3(new std::pair<int, int> (1,1));
    ASSERT_TRUE(it1 == it2);
    ASSERT_TRUE(it1 != it3);
    ASSERT_TRUE(*it1 == p);
}
TEST(Iterator, plusplus){
    simpletable<int, int> table;
    table.add(1,1).add(2,2);
    auto it = table.begin();
    ASSERT_EQ(std::pair(2,2), *(++it));
    ASSERT_EQ(std::pair(2,2), *(it++));
}
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
