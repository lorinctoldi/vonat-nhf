#include "menetrend.h"
#include "vonat.h"
#include "jegy.h"
#include "utvonal.h"
#include "ido.h"
#include "allomas.h"
#include "kocsi.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "memtrace.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

// TESZT 1: Jegy létrehozása és kiíratása.
void test_1()
{
    Allomas allomas1(1, "Budapest", 8, 9, 8, 12);
    Allomas allomas2(1, "Hargita", 9, 10, 9, 12);
    Allomas allomas3(1, "Teknoshat", 10, 30, 10, 32);
    Allomas allomas4(2, "Debrecen", 12, 0, 12, 6);
    Utvonal utvonal1;
    utvonal1.addAllomas(allomas1);
    utvonal1.addAllomas(allomas2);
    utvonal1.addAllomas(allomas3);
    utvonal1.addAllomas(allomas4);
    Vonat vonat1;
    vonat1.setUtvonal(utvonal1);
    Kocsi k(1,100);
    Kocsi k2(2,100);
    vonat1.addKocsi(k);
    vonat1.addKocsi(k2);

    for(size_t i = 0; i < 102; ++i) {
        size_t j = vonat1.createJegy("Budapest", "Teknoshat");
        Jegy* jegy = vonat1.getJegy(j);
        jegy->kiir(std::cout);
    }
}

// TESZT 2: Kedvezményes jegy létrehozása és kiíratása.
void test_2()
{
    Allomas allomas1(1, "Budapest", 8, 9, 8, 12);
    Allomas allomas2(1, "Hargita", 9, 10, 9, 12);
    Allomas allomas3(1, "Teknoshat", 10, 30, 10, 32);
    Allomas allomas4(2, "Debrecen", 12, 0, 12, 6);
    Utvonal utvonal1;
    utvonal1.addAllomas(allomas1);
    utvonal1.addAllomas(allomas2);
    utvonal1.addAllomas(allomas3);
    utvonal1.addAllomas(allomas4);
    Vonat vonat1;
    vonat1.setUtvonal(utvonal1);
    Kocsi k(1,100);
    vonat1.addKocsi(k);

    Allomas allomas5(1, "Budapest", 9, 10, 9, 12);
    Allomas allomas6(1, "Hargita", 10, 10, 10, 12);
    Allomas allomas7(1, "Teknoshat", 11, 30, 11, 32);
    Allomas allomas8(2, "Debrecen", 13, 0, 13, 6);
    Utvonal utvonal2;
    utvonal2.addAllomas(allomas5);
    utvonal2.addAllomas(allomas6);
    utvonal2.addAllomas(allomas7);
    utvonal2.addAllomas(allomas8);
    Vonat vonat2;
    vonat2.setUtvonal(utvonal2);
    Kocsi k2(1,100);
    vonat2.addKocsi(k2);

    Menetrend m;
    m.addVonat(vonat1);
    m.addVonat(vonat2);

    m.createJegy("Budapest", "Teknoshat", 9, 7, -0.4);
}

// TESZT 3: Feláras jegy létrehozása és kiíratása.
void test_3()
{
    // cout << "---- Test 3: Feláras jegy létrehozása és kiíratása ----" << endl;
    // Allomas indulo(1, const_cast<char*>("Szombathely"), 8, 15, 10, 30);
    // Allomas cel(2, const_cast<char*>("Miskolc"), 12, 0, 14, 45);
    // FelarasJegy felaras_jegy(3, 15, 2, 6, &indulo, &cel, 25.0, const_cast<char*>("Extra"));
    // felaras_jegy.kiir(cout);
}

// TESZT 4: Allomas módosításának tesztelése.
void test_4()
{
    cout << "---- Test 4: Allomas módosításának tesztelése ----" << endl;
    Allomas allomas(1, const_cast<char *>("Győr"), 10, 30, 12, 0);
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
void test_5()
{
    cout << "---- Test 5: Vonat létrehozása és kiíratása ----" << endl;
    Utvonal utvonal;
    Vonat vonat(1, 3, nullptr, utvonal, 0, nullptr);
    vonat.setUtvonal(utvonal);
    cout << "Vonat azonosito: " << vonat.getAzonosito() << endl;
}

// TESZT 6: Menetrend létrehozása és kiíratása.
void test_6()
{
    cout << "---- Test 6: Menetrend létrehozása és kiíratása ----" << endl;
    Vonat vonat1(1, 3, nullptr, Utvonal(), 0, nullptr);
    Vonat vonat2(2, 4, nullptr, Utvonal(), 0, nullptr);
    Vonat vonat3(3, 2, nullptr, Utvonal(), 0, nullptr);
    Vonat vonatok[] = {vonat1, vonat2, vonat3};
    Menetrend menetrend(vonatok, 3);
}

// TESZT 7: Mély másolat vizsgáláta
void test_7()
{
    Allomas allomas1(1, "Budapest", 8, 9, 10, 30);
    Allomas allomas2(2, "Debrecen", 12, 0, 14, 30);

    Kocsi kocsi1(1, 50);
    Kocsi kocsi2(2, 60);

    Utvonal utvonal1;
    utvonal1.addAllomas(allomas1);
    utvonal1.addAllomas(allomas2);

    FelarasJegy felaras(1, 1, 1, 1, allomas1.getNev(), allomas1.getIndulas(), allomas2.getNev(), allomas2.getErkezes(), 0.8, "nagyon kiraly jegy");
    Jegy jegy(1, 1, 1, 1, allomas1.getNev(), allomas1.getIndulas(), allomas2.getNev(), allomas2.getErkezes());
    Jegy *felarasArray[] = {&felaras, &jegy};
    Vonat vonat1(1, 1, &kocsi1, utvonal1, 2, felarasArray);
    // Vonat vonat2(2, 1, &kocsi2, utvonal1, 1, &jegy2);

    Menetrend menetrend;
    menetrend.addVonat(vonat1);
    // menetrend.addVonat(vonat2);

    std::stringstream ss;
    menetrend.write(ss);

    Menetrend deserializedMenetrend;
    deserializedMenetrend.read(ss);

    std::cout << "Eredeti menetrend:" << std::endl;
    menetrend.write(std::cout);

    std::cout << "\n\n\n\nDeszerelizialt menetrend:" << std::endl;
    deserializedMenetrend.write(std::cout);
}

// TESZT 8: Stream-re való kiírás vizsgáláta
void test_8()
{
    Allomas allomas1(1, "Budapest", 8, 9, 10, 30);
    Allomas allomas2(2, "Debrecen", 12, 0, 14, 30);

    Kocsi kocsi1(1, 50);

    Utvonal utvonal1;
    utvonal1.addAllomas(allomas1);
    utvonal1.addAllomas(allomas2);

    FelarasJegy felaras(1, 1, 1, 1, allomas1.getNev(), allomas1.getIndulas(), allomas2.getNev(), allomas2.getErkezes(), 0.8, "nagyon kiraly jegy");

    Jegy *felarasArray[] = {&felaras};
    Vonat vonat1(1, 1, &kocsi1, utvonal1, 1, felarasArray);
    KedvezmenyesJegy kedvezmeny(2, 2, 2, 1, allomas1.getNev(), allomas1.getIndulas(), allomas2.getNev(), allomas2.getErkezes(), 0.4, "kedvezmenyes fasza jegy");

    // std::stringstream ss;
    // vonat1.write(ss);

    // Vonat deserializedVonat;
    // deserializedVonat.read(ss);

    // std::cout << "Eredeti vonat:" << std::endl;
    // vonat1.write(std::cout);

    felaras.kiir(std::cout);
}

// TESZT 9: Stream-ről való beolvasás vizsgáláta
void test_9()
{
    Allomas allomas1(1, "Budapest", 8, 9, 10, 30);
    Allomas allomas2(2, "Debrecen", 12, 0, 14, 30);
    Kocsi kocsi1(1, 50);
    Utvonal utvonal1;
    utvonal1.addAllomas(allomas1);
    utvonal1.addAllomas(allomas2);
    FelarasJegy felaras(1, 1, 1, 1, allomas1.getNev(), allomas1.getIndulas(), allomas2.getNev(), allomas2.getErkezes(), 0.8, "nagyon kiraly jegy");
    Jegy *felarasArray[] = {&felaras};
    Vonat vonat1(1, 1, &kocsi1, utvonal1, 1, felarasArray);

    // Write Vonat object to file
    std::ofstream outFile("vonat_data.txt");
    if (outFile.is_open())
    {
        vonat1.write(outFile);
        outFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }

    // Read Vonat object from file
    std::ifstream inFile("vonat_data.txt");
    if (inFile.is_open())
    {
        Vonat deserializedVonat;
        deserializedVonat.read(inFile);
        inFile.close();

        // Print the original and deserialized Vonat objects
        std::cout << "Original Vonat:" << std::endl;
        vonat1.write(std::cout);
        std::cout << "\n\nDeserialized Vonat:" << std::endl;
        deserializedVonat.write(std::cout);
    }
    else
    {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
    }
}

void test_10()
{
    Allomas allomas1(1, "Budapest", 8, 9, 10, 30);
    Allomas allomas2(2, "Debrecen", 12, 0, 14, 30);

    Kocsi kocsi1(1, 50);

    Utvonal utvonal1;
    utvonal1.addAllomas(allomas1);
    utvonal1.addAllomas(allomas2);

    FelarasJegy felaras(1, 1, 1, 1, allomas1.getNev(), allomas1.getIndulas(), allomas2.getNev(), allomas2.getErkezes(), 0.8, "nagyon kiraly jegy");

    KedvezmenyesJegy kedvezmeny(2, 2, 2, 1, allomas1.getNev(), allomas1.getIndulas(), allomas2.getNev(), allomas2.getErkezes(), 0.4, "kedvezmenyes fasza jegy");
    Jegy *felarasArray[] = {&kedvezmeny};
    Vonat vonat1(1, 1, &kocsi1, utvonal1, 1, felarasArray);

    vonat1.addJegy(felaras);

    std::ofstream outFile("vonat_data.txt");
    if (outFile.is_open())
    {
        vonat1.write(outFile);
        outFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }

    // Read Vonat object from file
    std::ifstream inFile("vonat_data.txt");
    if (inFile.is_open())
    {
        Vonat deserializedVonat;
        deserializedVonat.read(inFile);
        inFile.close();

        // Print the original and deserialized Vonat objects
        std::cout << "Original Vonat:" << std::endl;
        vonat1.write(std::cout);
        std::cout << "\n\nDeserialized Vonat:" << std::endl;
        deserializedVonat.write(std::cout);
    }
    else
    {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
    }
}

void test_11() {
    Allomas allomas1(1, "Budapest", 8, 9, 8, 12);
    Allomas allomas2(1, "Hargita", 9, 10, 9, 12);
    Allomas allomas3(1, "Teknoshat", 10, 30, 10, 32);
    Allomas allomas4(2, "Debrecen", 12, 0, 12, 6);
    Utvonal utvonal1;
    utvonal1.addAllomas(allomas1);
    utvonal1.addAllomas(allomas2);
    utvonal1.addAllomas(allomas3);
    utvonal1.addAllomas(allomas4);
    Vonat vonat1;
    vonat1.setUtvonal(utvonal1);

    Menetrend m;
    m.addVonat(vonat1);
    m.kiir(std::cout, "Hargita", "Teknoshat");
}

int main()
{
    try
    {
        int nr;
        cin >> nr;
        switch (nr)
        {
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
        case 7:
            test_7();
            break;
        case 8:
            test_8();
            break;
        case 9:
            test_9();
            break;
        case 10:
            test_10();
            break;
        case 11:
            test_11();
            break;
        default:
            cout << "Invalid test number!" << endl;
            break;
        }
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
    catch (...)
    {
        cerr << "*** Nagy baj van! ****" << endl;
    }
    return 0;
}