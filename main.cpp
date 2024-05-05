#include "jegy.hpp"
#include "allomas.hpp"
#include "kocsi.hpp"
#include "vonat.hpp"
#include "menetrend.hpp"

#include <iostream>

#include "memtrace.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

// TESZT 1: Jegy létrehozása és kiíratása.
void test_1() {
    cout << "---- Test 1: Jegy létrehozása és kiíratása ----" << endl;
    Allomas indulo(1, const_cast<char*>("Budapest"), 10, 30, 12, 0);
    Allomas cel(2, const_cast<char*>("Debrecen"), 14, 45, 17, 30);
    Jegy jegy(1, 10, 3, 5, &indulo, &cel);
    jegy.kiir(cout);
}

// TESZT 2: Kedvezményes jegy létrehozása és kiíratása.
void test_2() {
    cout << "---- Test 2: Kedvezményes jegy létrehozása és kiíratása ----" << endl;
    Allomas indulo(1, const_cast<char*>("Szeged"), 9, 0, 10, 30);
    Allomas cel(2, const_cast<char*>("Pécs"), 13, 0, 16, 45);
    KedvezmenyesJegy kedv_jegy(2, 20, 4, 8, &indulo, &cel, 15.0, const_cast<char*>("Diák"));
    kedv_jegy.kiir(cout);
}

// TESZT 3: Feláras jegy létrehozása és kiíratása.
void test_3() {
    cout << "---- Test 3: Feláras jegy létrehozása és kiíratása ----" << endl;
    Allomas indulo(1, const_cast<char*>("Szombathely"), 8, 15, 10, 30);
    Allomas cel(2, const_cast<char*>("Miskolc"), 12, 0, 14, 45);
    FelarasJegy felaras_jegy(3, 15, 2, 6, &indulo, &cel, 25.0, const_cast<char*>("Extra"));
    felaras_jegy.kiir(cout);
}

// TESZT 4: Allomas módosításának tesztelése.
void test_4() {
    cout << "---- Test 4: Allomas módosításának tesztelése ----" << endl;
    Allomas allomas(1, const_cast<char*>("Győr"), 10, 30, 12, 0);
    cout << "Indulási idő előtti módosítás: ";
    allomas.changeIndulas(8, 0);
    cout << "Indulási idő utáni módosítás: ";
    allomas.changeIndulas(13, 0);
    cout << "Érkezési idő előtti módosítás: ";
    allomas.changeErkezes(11, 45);
    cout << "Érkezési idő utáni módosítás: ";
    allomas.changeErkezes(15, 30);
}

// TESZT 5: Vonat létrehozása és kiíratása.
void test_5() {
    cout << "---- Test 5: Vonat létrehozása és kiíratása ----" << endl;
    Utvonal utvonal;
    Vonat vonat(1, 3, nullptr, utvonal, 0, nullptr);
    vonat.setUtvonal(utvonal);
    cout << "Vonat azonosito: " << vonat.getAzonosito() << endl;
}

// TESZT 6: Menetrend létrehozása és kiíratása.
void test_6() {
    cout << "---- Test 6: Menetrend létrehozása és kiíratása ----" << endl;
    Vonat vonat1(1, 3, nullptr, Utvonal(), 0, nullptr);
    Vonat vonat2(2, 4, nullptr, Utvonal(), 0, nullptr);
    Vonat vonat3(3, 2, nullptr, Utvonal(), 0, nullptr);
    Vonat vonatok[] = {vonat1, vonat2, vonat3};
    Menetrend menetrend(vonatok, 3);
    menetrend.kiir();
}

// TESZT 7: Mély másolat vizsgáláta
void test_7() { }

// TESZT 8: Stream-re való kiírás vizsgáláta
void test_8() { }

// TESZT 9: Stream-ről való beolvasás vizsgáláta
void test_9() { }

int main() {
try {
      int nr;
      cin >> nr;
      switch (nr) {
            case 1:
                test_1();
                break;
            case 2:
                test_2();
                break;
            case 3:
                test_3();
                break;
            case 4:
                test_4();
                break;
            case 5:
                test_5();
                break;
            case 6:
                test_6();
                break;
            default:
                cout << "Invalid test number!" << endl;
                break;
        }
    } catch (std::exception& e) {
        cerr << e.what() << endl;
    } catch (const char *e) {
        cerr << "Sajat kivetel jott" << endl;
    } catch (...) {
        cerr << "*** Nagy baj van! ****" << endl;
    }
	return 0;
}