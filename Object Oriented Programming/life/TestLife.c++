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

#define cout out
std::filebuf fb;
std::ostream out(&fb);

#include "Life.h"


// -----------
// TestCollatz
// -----------

struct TestLife : CppUnit::TestFixture {

	void lifeProgress1()
    {
        Life<ConwayCell> l(1, 1, "*", ConwayCell());
        l.progress();
        CPPUNIT_ASSERT(l.grid[1][1].sign() == '.');
    }
    void lifeProgress2()
    {
        Life<FredkinCell> l(1, 1, "0", FredkinCell());
        l.progress();
        CPPUNIT_ASSERT(l.grid[1][1].sign() == '-');
    }
    void lifeProgress3()
    {
        Life<Cell> l(2, 1, "0-", new FredkinCell());
        l.progress();
        l.progress();
        l.progress();
        l.progress();
        l.progress();

        CPPUNIT_ASSERT(l.grid[1][2].sign() == '0');
    }
    void lifeConstruct1()
    {
        Life<FredkinCell> l(0, 0, "", FredkinCell());
        CPPUNIT_ASSERT(l.grid.size() == 2 && l.grid[0].size() == 2);
    }
    void lifeConstruct2()
    {
        Life<ConwayCell> l(1, 1, "*", ConwayCell());
        CPPUNIT_ASSERT(l.grid.size() == 3 && l.grid[0].size() == 3);
    }
    void lifeConstruct3()
    {
        Life<Cell> l(3, 2, "---\n000\n---", new FredkinCell());
        CPPUNIT_ASSERT(l.grid.size() == 4 && l.grid[0].size() == 5);
    }
    void lifeSimulate1()
    {
        Life<ConwayCell> l(3, 3, ".*.\n*.*\n.*.", ConwayCell());
        l.simulate(50);
        CPPUNIT_ASSERT(l.grid[2][1].sign() == '*');
    }
    void lifeSimulate2()
    {
        Life<FredkinCell> l(2, 1, "0-", FredkinCell());
        l.simulate(10);
        CPPUNIT_ASSERT(l.grid[1][1].sign() == '0');

        l.simulate(20);
        CPPUNIT_ASSERT(l.grid[1][1].sign() == '0');
    }
    void lifeSimulate3()
    {
        Life<Cell> l(3, 3, ".*.\n*.*\n.*.", new ConwayCell());
        l.simulate(50);
        CPPUNIT_ASSERT(l.grid[2][1].sign() == '*');
    }
    void lifePrint1()
    {
        Life<ConwayCell> l(0, 0, "", ConwayCell());
        l.print();
    }
    void lifePrint2()
    {
        Life<FredkinCell> l(0, 0, "", FredkinCell());
        l.print();
    }
    void lifePrint3()
    {
        Life<Cell> l(0, 0, "", new FredkinCell());
        l.print();
    }
    void clone1()
    {
        FredkinCell c;
        AbstractCell* a;
        a = c.clone();

        CPPUNIT_ASSERT(a->sign() == '-');
	Cell t(a);
    }
    void clone2()
    {
        ConwayCell c;
        AbstractCell* a;
        a = c.clone();

        CPPUNIT_ASSERT(a->sign() == '.');
	Cell t(a);
    }
    void clone3()
    {
        ConwayCell c;
        Cell a = c.clone();

        CPPUNIT_ASSERT(a.sign() == '.');
    }
    void ConwayRun1()
    {
        ConwayCell c;
        c.run(2, 1);

        CPPUNIT_ASSERT(c.sign() == '*');
    }
    void ConwayRun2()
    {
        ConwayCell c;
        c.setLife(true);
        c.run(0, 0);

        CPPUNIT_ASSERT(c.sign() == '.');
    }
    void ConwayRun3()
    {
        Cell a = new ConwayCell();
        a.run(0, 1);

        CPPUNIT_ASSERT(a.sign() == '.');
    }
    void FredkinRun1()
    {
        FredkinCell c;
        c.run(3, 0);

        CPPUNIT_ASSERT(c.sign() == '0');
    }
    void FredkinRun2()
    {
        FredkinCell c;
        c.setLife(true);
        c.run(0, 0);

        CPPUNIT_ASSERT(c.sign() == '-');
    }
    void FredkinRun3()
    {
        Cell a = new FredkinCell();
        a.run(2, 0);

        CPPUNIT_ASSERT(a.sign() == '-');
    }
    void ConwaySign1()
    {
        ConwayCell c;

        CPPUNIT_ASSERT(c.sign() == '.');
    }
    void ConwaySign2()
    {
        ConwayCell c;
        c.setLife(true);

        CPPUNIT_ASSERT(c.sign() == '*');
    }
    void ConwaySign3()
    {
        Cell a = new ConwayCell();

        CPPUNIT_ASSERT(a.sign() == '.');
    }
    void FredkinSign1()
    {
        FredkinCell c;

        CPPUNIT_ASSERT(c.sign() == '-');
    }
    void FredkinSign2()
    {
        FredkinCell c;
        c.setLife(true);

        CPPUNIT_ASSERT(c.sign() == '0');
    }
    void FredkinSign3()
    {
        Cell a = new FredkinCell();

        CPPUNIT_ASSERT(a.sign() == '-');
    }
    void isAlive1()
    {
        ConwayCell c;

        CPPUNIT_ASSERT(c.isAlive() == false);
    }
    void isAlive2()
    {
        FredkinCell c;
        c.setLife(true);

        CPPUNIT_ASSERT(c.isAlive() == true);
    }
    void isAlive3()
    {
        Cell a = new ConwayCell();

        CPPUNIT_ASSERT(a.isAlive() == false);
    }
    void setLife1()
    {
        ConwayCell c;
        c.setLife(true);
        c.setLife(false);

        CPPUNIT_ASSERT(c.isAlive() == false);
    }
    void setLife2()
    {
        FredkinCell c;
        c.setLife(true);
        c.setLife(false);
        c.setLife(false);
        c.setLife(true);

        CPPUNIT_ASSERT(c.isAlive() == true);
    }
    void setLife3()
    {
        Cell a = new FredkinCell();
        a.setLife(false);
        a.setLife(false);
        a.setLife(true);
        a.setLife(false);

        CPPUNIT_ASSERT(a.isAlive() == false);
    }
    void mutate1()
    {
        Life<ConwayCell> l(1, 1, "*", ConwayCell());
        l.grid[1][1].mutate();
        CPPUNIT_ASSERT(l.grid[1][1].sign() == '*');
    }
    void mutate2()
    {
        Life<FredkinCell> l(1, 1, "0", FredkinCell());
        l.grid[1][1].mutate();
        CPPUNIT_ASSERT(l.grid[1][1].sign() == '0');
    }
    void mutate3()
    {
        Life<Cell> l(1, 1, "0", new FredkinCell());
        l.grid[1][1].mutate();
        CPPUNIT_ASSERT(l.grid[1][1].sign() == '*');
    }

    //CPPUNIT_ASSERT(g.x==97 && g.y==101);
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
    CPPUNIT_TEST(lifeProgress1);
    CPPUNIT_TEST(lifeProgress2);
    CPPUNIT_TEST(lifeProgress3);
    CPPUNIT_TEST(lifeConstruct1);
    CPPUNIT_TEST(lifeConstruct2);
    CPPUNIT_TEST(lifeConstruct3);
    CPPUNIT_TEST(lifeSimulate1);
    CPPUNIT_TEST(lifeSimulate2);
    CPPUNIT_TEST(lifeSimulate3);
    CPPUNIT_TEST(lifePrint1);
    CPPUNIT_TEST(lifePrint2);
    CPPUNIT_TEST(lifePrint3);
    CPPUNIT_TEST(clone1);
    CPPUNIT_TEST(clone2);
    CPPUNIT_TEST(clone3);
    CPPUNIT_TEST(ConwayRun1);
    CPPUNIT_TEST(ConwayRun2);
    CPPUNIT_TEST(ConwayRun3);
    CPPUNIT_TEST(FredkinRun1);
    CPPUNIT_TEST(FredkinRun2);
    CPPUNIT_TEST(FredkinRun3);
    CPPUNIT_TEST(ConwaySign1);
    CPPUNIT_TEST(ConwaySign2);
    CPPUNIT_TEST(ConwaySign3);
    CPPUNIT_TEST(FredkinSign1);
    CPPUNIT_TEST(FredkinSign2);
    CPPUNIT_TEST(FredkinSign3);
    CPPUNIT_TEST(isAlive1);
    CPPUNIT_TEST(isAlive2);
    CPPUNIT_TEST(isAlive3);
    CPPUNIT_TEST(setLife1);
    CPPUNIT_TEST(setLife2);
    CPPUNIT_TEST(setLife3);
    CPPUNIT_TEST(mutate1);
    CPPUNIT_TEST(mutate2);
    CPPUNIT_TEST(mutate3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
