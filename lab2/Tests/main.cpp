#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Tests/Cassini.h"
TEST(Constructor,1){
    Cassini::Curve curve;
    EXPECT_EQ(0, curve.a);
    EXPECT_EQ(1, curve.c);
}
TEST(Constructor,2){
    Cassini::Curve curve(2, 3);
    EXPECT_EQ(2, curve.a);
    EXPECT_EQ(3, curve.c);
}
TEST(Getter, ac){
    Cassini::Curve curve(1.1,1);
    ASSERT_DOUBLE_EQ(1.1,curve.get_a());
    ASSERT_DOUBLE_EQ(1, curve.get_c());
}
TEST(Constructor, Exception)
{
    ASSERT_ANY_THROW(Cassini::Curve(3, -1.005));
    ASSERT_ANY_THROW(Cassini::Curve(-1.005, 3));
    ASSERT_ANY_THROW(Cassini::Curve(-3, -1.005));
}
TEST(Setting,setAC){
    Cassini::Curve curve(2, 3);
    curve.set(5,6);
    EXPECT_EQ(5, curve.a);
    EXPECT_EQ(6, curve.c);
}
TEST(Setting,setA){
    Cassini::Curve curve(2, 3);
    curve.set_a(4);
    EXPECT_EQ(4, curve.a);
}
TEST(Setting,setC){
    Cassini::Curve curve(2, 3);
    curve.set_c(6);
    EXPECT_EQ(6, curve.c);
}
TEST(Math, form){
    Cassini::Curve curve(2, 3);
    int a = curve.getform();
    EXPECT_EQ(a, 1);
    curve.set(1,1);
    EXPECT_EQ(curve.getform(), 2);
    curve.set(1.1,1);
    EXPECT_EQ(curve.getform(), 3);
    curve.set(1.7,1);
    EXPECT_EQ(curve.getform(), 4);
    curve.set(0,1);
    EXPECT_EQ(curve.getform(), 0);
    curve.set(1,0);
    EXPECT_EQ(curve.getform(), 5);
    curve.set(1,1);
    EXPECT_EQ(curve.getform(), 2);
}
TEST(Math, getR) {
    Cassini::Curve curve(1.1, 1);
    double D = std::pow(1, 4) * std::pow(cos(2 * 40), 2) - pow(1, 2) + pow(1.1, 4);
    double t = std::pow(1, 2) * cos(2 * 40) + sqrt(D);
    double r = sqrt(t);
    ASSERT_NEAR(r, curve.getR(40), 0.03);
}
TEST(Math, getCurvature){
    Cassini::Curve curve(1.1, 1);
    double D = std::pow(1, 4) * std::pow(cos(2 * 40), 2) - pow(1, 2) + pow(1.1, 4);
    double t = std::pow(1, 2) * cos(2 * 40) + sqrt(D);
    double r = sqrt(t);
    double R = (2 * std::pow(1.1, 2) * std::pow(1, 3) * std::pow(r, 3)) /
               (std::pow(1, 4) - std::pow(1.1, 4) + 3 * std::pow(r, 4));
    ASSERT_NEAR(R, curve.getCurvature(40), 0.001);
}
TEST(Math, getInflectionPoints) {
    Cassini::Curve curve(1.1, 1);
    double p = std::pow((std::pow(curve.a, 4) - std::pow(curve.c, 4)) / 3, 0.25);
    double phi = acos(-sqrt((std::pow(curve.a, 4) / std::pow(curve.c, 4) - 1)) / 3) / 2;
    for(int i = 0; i < 4; i++) {
        ASSERT_NEAR(p, curve.getInflectionpoint()[i].p, 0.001);
    }
    ASSERT_NEAR(phi, curve.getInflectionpoint()[0].phi, 0.001);
    ASSERT_NEAR(M_PI - phi, curve.getInflectionpoint()[1].phi, 0.001);
    ASSERT_NEAR(M_PI + phi, curve.getInflectionpoint()[2].phi, 0.001);
    ASSERT_NEAR(2 * M_PI - phi, curve.getInflectionpoint()[3].phi, 0.001);
    curve.set(0.4, 1);
    ASSERT_EQ(nullptr, curve.getInflectionpoint());
}
TEST(Form, getForm) {
    Cassini::Curve curve(1.1, 1);
    char* a = new char[80];
    curve.getFormula(a);
    ASSERT_EQ(strcmp(a, "x^2 + 2.000000(x^2 - y^2) = 0.464100"), 0);
    curve.set(0.1, 1);
    curve.getFormula(a);
    ASSERT_EQ(strcmp(a, "x^2 + 2.000000(x^2 - y^2) = -0.999900"), 0);
    ASSERT_STREQ("x^2 + 2.000000(x^2 - y^2) = -0.999900", a);
}
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
