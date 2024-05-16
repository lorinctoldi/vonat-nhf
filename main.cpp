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
#include "gtest_lite.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

// Ido osztaly kiiras funkciojanak vizsgalata
void test_1()
{
  // Stream letrehozasa
  std::stringstream ss;

  // ===== KIIRAS =====
  // Ido objektumok letrehozasa konstruktorral
  Ido i1(10, 12);
  Ido i2(2, 1);

  // Ido objektumok kiirasa a streamre
  i1.kiir(ss); // vart: "10:12"
  i2.kiir(ss); // vart: "02:01"

  // Kiirt erteket vizsgalata
  EXPECT_STREQ("10:12\n02:01\n", ss.str().c_str());
  // ===== KIIRAS =====
}

// Ido osztaly perzisztenciajanak vizsgalata
void test_2()
{
  // Stream letrehozasa
  std::stringstream ss;

  // ===== PERZISZTENCIA =====
  // Ido objektumok letrehozasa
  Ido ido1(8, 30);
  Ido ido2;

  // Az ido1 objektumot kiirjuk egy stringstreambe
  ido1.write(ss);

  // Ezutan az ido2 objektumot beolvassuk ugyanabbol a stringstreambol
  ido2.read(ss);

  EXPECT_TRUE(ido1 == ido2);
  // ===== PERZISZTENCIA =====
}

// Ido osztaly alapveto muveleteinek vizsgalata
void test_3()
{
  // ===== EGYSZERU MUVELETEK =====
  // Ido objektum letrehozasa konstruktorral
  Ido i(2, 45);

  // Ellenorizzuk, hogy a konstruktor helyesen allitja be az erteket
  EXPECT_EQ(2, i.getOra());
  EXPECT_EQ(45, i.getPerc());

  // Uj ertekek beallitasa a setterek segitsegevel
  i.setOra(3);
  i.setPerc(15);

  // Ellenorizzuk, hogy a setterek helyesen mukodnek-e
  EXPECT_EQ(3, i.getOra());
  EXPECT_EQ(15, i.getPerc());

  // Orak es percek hozzaadasa
  i.addOra(2);
  i.addPerc(30);

  // Ellenorizzuk, hogy az aritmetikai muveletek helyesen mukodnek-e
  EXPECT_EQ(5, i.getOra());
  EXPECT_EQ(45, i.getPerc()); // 30 perccel valo novelesnek nem szabad befolyasolnia az ora erteket

  // Ujabb Ido objektum letrehozasa a konstruktorral
  Ido j(1, 30);

  // Egyenloseg operator ellenorzes
  EXPECT_FALSE(i == j);

  // Kulonbozoseg operator ellenorzes
  EXPECT_TRUE(i != j);
  // ===== EGYSZERU MUVELETEK =====
}

// Allomas osztaly alapertelmezett konstruktoranak vizsgalata
void test_4()
{
  // ===== KONSTRUKTOR =====
  Allomas allomas;

  // Ellenorizzuk, hogy az alapertelmezett ertekek helyesen vannak beallitva
  EXPECT_EQ(0, allomas.getIndulasOra());
  EXPECT_EQ(0, allomas.getIndulasPerc());
  EXPECT_EQ(0, allomas.getErkezesOra());
  EXPECT_EQ(0, allomas.getErkezesPerc());
  EXPECT_EQ("", allomas.getNev());

  Allomas allomas_2(123, "Teszt Allomas", 10, 30, 12, 45);

  // Ellenorizzuk, hogy az ertekek helyesen vannak beallitva
  EXPECT_EQ(10, allomas_2.getIndulasOra());
  EXPECT_EQ(30, allomas_2.getIndulasPerc());
  EXPECT_EQ(12, allomas_2.getErkezesOra());
  EXPECT_EQ(45, allomas_2.getErkezesPerc());
  EXPECT_EQ("Teszt Allomas", allomas_2.getNev());
  // ===== KONSTRUKTOR =====
}

// Allomas osztaly indulasi es erkezesi idejenek es nevenek modositasanak vizsgalata
void test_5()
{
  // ===== SETTEREK =====
  Allomas allomas(123, "Teszt Allomas", 10, 30, 12, 45);

  // Modositjuk az indulasi es erkezesi idoket
  allomas.changeIndulas(11, 0);
  allomas.changeErkezes(13, 15);

  // Ellenorizzuk, hogy az idok helyesen lettek-e modositva
  EXPECT_EQ(11, allomas.getIndulasOra());
  EXPECT_EQ(0, allomas.getIndulasPerc());
  EXPECT_EQ(13, allomas.getErkezesOra());
  EXPECT_EQ(15, allomas.getErkezesPerc());

  Allomas allomas_2(123, "Teszt Allomas", 10, 30, 12, 45);

  // Modositjuk a nevet
  allomas_2.changeNev("Uj Teszt Allomas");

  // Ellenorizzuk, hogy a nev helyesen lett-e modositva
  EXPECT_EQ("Uj Teszt Allomas", allomas_2.getNev());
  // ===== SETTEREK =====
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
    default:
      cout << "Hibas teszt szam!" << endl;
      break;
    }
  }
  catch (std::exception &err)
  {
    cerr << err.what() << endl;
  }
  catch (const char *err)
  {
    cerr << err << endl;
  }
  catch (...)
  {
    cerr << "*** Nagy baj van! ****" << endl;
  }
  return 0;
}