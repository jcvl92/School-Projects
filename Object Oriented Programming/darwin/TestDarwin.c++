// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public

#include "Darwin.h"

// -----------
// TestCollatz
// -----------

struct TestDarwin : CppUnit::TestFixture {

	void testGrid1()
    {
        Grid g(101, 97);
        CPPUNIT_ASSERT(g.x==97 && g.y==101);
    }
    void testGrid2()
    {
        Grid g(10, 7);
        CPPUNIT_ASSERT(g.x==7 && g.y==10);
    }
    void testGrid3()
    {
        Grid g(1, 1);
        CPPUNIT_ASSERT(g.x==1 && g.y==1);
    }

    void testCreature1()
    {
        Creature c;
        CPPUNIT_ASSERT(c.mySpecies.program[0].length() == 0);
    }
    void testCreature2()
    {
        Creature c(Species("0: instruction", 'd'), north);
        Species s = Species("0: instruction", 'd');
        CPPUNIT_ASSERT(c.mySpecies.letter == s.letter);
    }
    void testCreature3()
    {
        Creature c(Species(
        "0: if_enemy 3\n"
        "1: left\n"
        "2: go 0\n"
        "3: infect\n"
        "4: go 0",
        't'
        ), south);

        CPPUNIT_ASSERT(c.mySpecies.program[2] == "2: go 0");
    }
    void testTurn1()
    {
        Grid g(10,10);
        g.place(Creature(Species("string", 'X'), north),5,5);
        g.current = &g.grid[5][5];
        g.left();
        CPPUNIT_ASSERT(g.grid[5][5].dir == west);
    }
    void testTurn2()
    {
        Grid g(200,200);
        g.place(Creature(Species("string", 'X'), north),5,5);
        g.current = &g.grid[5][5];
        g.right();
        CPPUNIT_ASSERT(g.grid[5][5].dir == east);
    }
    void testTurn3()
    {
        Grid g(6,6);
        g.place(Creature(Species("string", 'X'), north),5,5);
        g.current = &g.grid[5][5];
        g.right();
        g.left();
        CPPUNIT_ASSERT(g.grid[5][5].dir == north);
    }
    void testPlace1()
    {
        Grid g(4,13);
        g.place(Creature(Species("string", 'X'), north),2,6);
        CPPUNIT_ASSERT(g.grid[2][6].mySpecies.letter == 'X');
    }
    void testPlace2()
    {
        Grid g(13,4);
        g.place(Creature(Species("string", 'X'), north),6,2);
        CPPUNIT_ASSERT(g.grid[6][2].mySpecies.letter == 'X');
    }
    void testPlace3()
    {
        Grid g(4,4);
        g.place(Creature(Species("string", 'X'), north),2,2);
        CPPUNIT_ASSERT(g.grid[2][2].mySpecies.letter == 'X');
    }
    void testHop1()
    {
        Grid g(11,11);
        g.place(Creature(Species("string", 'X'), west),6,5);
        g.current = &g.grid[6][5];
        g.currentY = 6;
        g.currentX = 5;
        g.hop();
        CPPUNIT_ASSERT(g.grid[6][4].mySpecies.letter == 'X');
    }
    void testHop2()
    {
        Grid g(1,2);
        g.place(Creature(Species("string", 'X'), east),0,0);
        g.current = &g.grid[0][0];
        g.currentY = 0;
        g.currentX = 0;
        g.hop();
        CPPUNIT_ASSERT(g.grid[0][1].mySpecies.letter == 'X');
    }
    void testHop3()
    {
        Grid g(11,11);
        g.place(Creature(Species("string", 'X'), east),6,5);
        g.current = &g.grid[6][5];
        g.currentY = 6;
        g.currentX = 5;
        g.hop();
        CPPUNIT_ASSERT(g.grid[6][6].mySpecies.letter == 'X');
    }
    void testInfect1()
    {
        Grid g(20,20);
        g.place(Creature(Species("string", 'X'), east),10,10);
        g.place(Creature(Species("string", 'Y'), north),11,10);
        g.current = &g.grid[11][10];
        g.currentY = 11;
        g.currentX = 10;
        g.infect();
        CPPUNIT_ASSERT(g.grid[10][10].mySpecies.letter == 'Y');
    }
    void testInfect2()
    {
        Grid g(1,2);
        g.place(Creature(Species("string", 'X'), east),0,0);
        g.place(Creature(Species("string", 'Y'), north),0,1);
        g.current = &g.grid[0][0];
        g.currentY = 0;
        g.currentX = 0;
        g.infect();
        CPPUNIT_ASSERT(g.grid[0][1].mySpecies.letter == 'X');
    }
    void testInfect3()
    {
        Grid g(200,200);
        g.place(Creature(Species("string", 'X'), east),100,100);
        g.place(Creature(Species("string", 'Y'), north),101,100);
        g.current = &g.grid[101][100];
        g.currentY = 101;
        g.currentX = 100;
        g.infect();
        CPPUNIT_ASSERT(g.grid[100][100].mySpecies.letter == 'Y');
    }
    void testSpin1()
    {
        Grid g(8,8);
        g.place(Creature(Species("string", 'Z'), north),4,4);
        g.current = &g.grid[4][4];
        g.left();
        g.left();
        g.left();
        g.left();
        CPPUNIT_ASSERT(g.grid[4][4].dir == north);
    }
    void testSpin2()
    {
        Grid g(1,1);
        g.place(Creature(Species("string", 'Z'), north),0,0);
        g.current = &g.grid[0][0];
        g.left();
        g.right();
        g.left();
        g.right();
        CPPUNIT_ASSERT(g.grid[0][0].dir == north);
    }
    void testSpin3()
    {
        Grid g(8,8);
        g.place(Creature(Species("string", 'Z'), north),4,4);
        g.current = &g.grid[4][4];
        g.right();
        g.right();
        g.right();
        g.right();
        CPPUNIT_ASSERT(g.grid[4][4].dir == north);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(testGrid1);
    CPPUNIT_TEST(testGrid2);
    CPPUNIT_TEST(testGrid3);
    CPPUNIT_TEST(testCreature1);
    CPPUNIT_TEST(testCreature2);
    CPPUNIT_TEST(testCreature3);
    CPPUNIT_TEST(testTurn1);
    CPPUNIT_TEST(testTurn2);
    CPPUNIT_TEST(testTurn3);
    CPPUNIT_TEST(testPlace1);
    CPPUNIT_TEST(testPlace2);
    CPPUNIT_TEST(testPlace3);
    CPPUNIT_TEST(testHop1);
    CPPUNIT_TEST(testHop2);
    CPPUNIT_TEST(testHop3);
    CPPUNIT_TEST(testInfect1);
    CPPUNIT_TEST(testInfect2);
    CPPUNIT_TEST(testInfect3);
    CPPUNIT_TEST(testSpin1);
    CPPUNIT_TEST(testSpin2);
    CPPUNIT_TEST(testSpin3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
