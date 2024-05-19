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

int main()
{
  // Ido osztaly kiiras funkciojanak vizsgalata
  TEST(IdoKiiras, Test1)
  {
    // Stream letrehozasa
    std::stringstream ss;

    // Ido objektumok letrehozasa konstruktorral
    Ido i1(10, 12);
    Ido i2(2, 1);

    // Ido objektumok kiirasa a streamre
    i1.kiir(ss); // vart: "10:12"
    i2.kiir(ss); // vart: "02:01"

    // Kiirt erteket vizsgalata
    EXPECT_STREQ("10:12\n02:01\n", ss.str().c_str());
  }
  END

  // Ido osztaly perzisztenciajanak vizsgalata
  TEST(IdoPerzisztencia, Test2)
  {
    // Stream letrehozasa
    std::stringstream ss;

    // Ido objektumok letrehozasa
    Ido ido1(8, 30);
    Ido ido2;

    // Az ido1 objektumot kiirjuk egy stringstreambe
    ido1.write(ss);

    // Ezutan az ido2 objektumot beolvassuk ugyanabbol a stringstreambol
    ido2.read(ss);

    EXPECT_TRUE(ido1 == ido2);
  }
  END

  // Ido osztaly alapveto muveleteinek vizsgalata
  TEST(IdoMuveletek, Test3)
  {
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
  }
  END

  // Allomas osztaly alapertelmezett konstruktoranak vizsgalata
  TEST(AllomasKonstruktor, Test4)
  {
    // Allomas objektum letrehozasa konstruktorral
    Allomas allomas;

    // Ellenorizzuk, hogy az alapertelmezett ertekek helyesen vannak beallitva
    EXPECT_EQ(0, allomas.getIndulasOra());
    EXPECT_EQ(0, allomas.getIndulasPerc());
    EXPECT_EQ(0, allomas.getErkezesOra());
    EXPECT_EQ(0, allomas.getErkezesPerc());
    EXPECT_EQ("", allomas.getNev());

    // Allomas objektum letrehozasa parameters konstruktorral
    Allomas allomas_2(123, "Teszt Allomas", 10, 30, 12, 45);

    // Ellenorizzuk, hogy az ertekek helyesen vannak beallitva
    EXPECT_EQ(12, allomas_2.getIndulasOra());
    EXPECT_EQ(45, allomas_2.getIndulasPerc());
    EXPECT_EQ(10, allomas_2.getErkezesOra());
    EXPECT_EQ(30, allomas_2.getErkezesPerc());
    EXPECT_EQ("Teszt Allomas", allomas_2.getNev());
  }
  END

  // Allomas osztaly attributumainak modositasanak vizsgalata
  TEST(AllomasModositas, Test5)
  {
    // Allomas objektum letrehozasa parameters konstruktorral
    Allomas allomas(123, "Teszt Allomas", 10, 30, 12, 45);

    // Modositjuk az indulasi es erkezesi idoket
    allomas.changeIndulas(11, 0);
    allomas.changeErkezes(10, 45);

    // Ellenorizzuk, hogy az idok helyesen lettek-e modositva
    EXPECT_EQ(11, allomas.getIndulasOra());
    EXPECT_EQ(0, allomas.getIndulasPerc());
    EXPECT_EQ(10, allomas.getErkezesOra());
    EXPECT_EQ(45, allomas.getErkezesPerc());

    // Allomas objektum letrehozasa parameters konstruktorral
    Allomas allomas_2(123, "Teszt Allomas", 10, 30, 12, 45);

    // Modositjuk a nevet
    allomas_2.changeNev("Uj Teszt Allomas");

    // Ellenorizzuk, hogy a nev helyesen lett-e modositva
    EXPECT_EQ("Uj Teszt Allomas", allomas_2.getNev());
  }
  END

  // Allomas osztaly perzisztenciajanak vizsgalata
  TEST(AllomasPerzisztencia, Test1)
  {
    // Stream letrehozasa
    std::stringstream ss;

    // Allomas objektum letrehozasa parameteres konstruktorral
    Allomas allomas1(123, "Teszt Allomas", 10, 30, 12, 45);
    Allomas allomas2;

    // allomas1 objektum kiirasa stringstreambe
    allomas1.write(ss);

    // allomas2 objektumot beolvasasa stringstreambol
    allomas2.read(ss);

    // eredeti es beolvasott objektum egyezesenek vizsgalata
    EXPECT_EQ(allomas1.getNev(), allomas2.getNev());
    EXPECT_EQ(allomas1.getIndulasOra(), allomas2.getIndulasOra());
    EXPECT_EQ(allomas1.getIndulasPerc(), allomas2.getIndulasPerc());
    EXPECT_EQ(allomas1.getErkezesOra(), allomas2.getErkezesOra());
    EXPECT_EQ(allomas1.getErkezesPerc(), allomas2.getErkezesPerc());
  }
  END

  // Utvonal osztaly allomas hozzaadas funkciojanak tesztelese
  TEST(Utvonal, AddAllomas)
  {
    // Utvonal objektum letrehozasa
    Utvonal utvonal;
    // Allomas objektumok letrehozasa parameteres konstruktorral
    Allomas allomas1(1, "Allomas1", 9, 0, 9, 5);
    Allomas allomas2(2, "Allomas2", 10, 0, 10, 5);

    // utvonal objektum bovitese az allomas objektumokkal
    utvonal.addAllomas(allomas1);
    utvonal.addAllomas(allomas2);

    // utvonal objektumban tarolt allomas objektumok ellenorzese
    EXPECT_EQ(2, utvonal.getAllomasokSzama());
    EXPECT_EQ("Allomas1", utvonal.getAllomas(0).getNev());
    EXPECT_EQ("Allomas2", utvonal.getAllomas(1).getNev());
  }
  END

  // Utvonal allomas cserejenek tesztelese
  TEST(Utvonal, ChangeAllomas)
  {
    // Utvonal objektum letrehozasa
    Utvonal utvonal;
    // Allomas objektumok letrehozasa parameteres konstruktorral
    Allomas allomas1(1, "Allomas1", 9, 0, 9, 5);
    Allomas allomas2(2, "Allomas2", 10, 0, 10, 5);
    Allomas allomas3(3, "Allomas3", 11, 0, 11, 5);

    // utvonal objektum bovitese az allomas objektumokkal
    utvonal.addAllomas(allomas1);
    utvonal.addAllomas(allomas2);

    // utvonal objektumban tarolt 2. allomas csereje masik allomas objektumra
    utvonal.changeAllomas(1, allomas3);

    // utvonal objektumban tarolt allomas objektumok ellenorzese (csereles utan)
    EXPECT_EQ(2, utvonal.getAllomasokSzama());
    EXPECT_EQ("Allomas1", utvonal.getAllomas(0).getNev());
    EXPECT_EQ("Allomas3", utvonal.getAllomas(1).getNev());
  }
  END

  // Utvonal perzisztenciajanak tesztelese
  TEST(Utvonal, Perzisztencia)
  {
    // Utvonal objektum letrehozasa
    Utvonal utvonal;
    // Allomas objektumok letrehozasa parameteres konstruktorral
    Allomas allomas1(1, "Allomas1", 9, 0, 9, 5);
    Allomas allomas2(2, "Allomas2", 10, 0, 10, 5);

    // utvonal objektum bovitese az allomas objektumokkal
    utvonal.addAllomas(allomas1);
    utvonal.addAllomas(allomas2);

    // Stream letrehozasa
    std::stringstream ss;
    // utvonal objektum kiirasa stringstreambe
    utvonal.write(ss);

    // Utvonal objektum letrehozasa beolvasashoz
    Utvonal utvonal2;
    // utvonal objektum beolvasa stringstreambol
    utvonal2.read(ss);

    // eredeti es beolvasott utvonal objektumok egyezesenek vizsgalata
    EXPECT_EQ(utvonal.getAllomasokSzama(), utvonal2.getAllomasokSzama());
    EXPECT_EQ(utvonal.getAllomas(0).getNev(), utvonal2.getAllomas(0).getNev());
    EXPECT_EQ(utvonal.getAllomas(1).getNev(), utvonal2.getAllomas(1).getNev());
  }
  END

  // Kocsi osztaly szek foglalas funkciojanak tesztelese
  TEST(Kocsi, ReserveHely)
  {
    // Kocsi objektum letrehozasa 5 ulohellyel
    Kocsi kocsi(1, 5);

    // minden ulohely lefoglalasa
    EXPECT_EQ(0, kocsi.reserveHely());
    EXPECT_EQ(1, kocsi.reserveHely());
    EXPECT_EQ(2, kocsi.reserveHely());
    EXPECT_EQ(3, kocsi.reserveHely());
    EXPECT_EQ(4, kocsi.reserveHely());

    // nincs tobb szabad ulohely igy hibat kell dobnia
    EXPECT_THROW(kocsi.reserveHely(), const char *);
  }
  END

  // Kocsi teljes foglaltsag tesztelese
  TEST(Kocsi, Tele)
  {
    // Kocsi objektum letrehozasa 2 ulohellyel
    Kocsi kocsi(2, 2);

    // van szabad hely, igy a tele fuggveny hamis erteket kell adjon
    EXPECT_FALSE(kocsi.tele());

    // minden ulohely lefoglalasa
    kocsi.reserveHely();
    kocsi.reserveHely();

    // nincs szabad hely, igy a tele fuggveny igaz erteket kell adjon
    EXPECT_TRUE(kocsi.tele());
  }
  END

  // Kocsi perzisztenciajanak tesztelese
  TEST(Kocsi, Persistency)
  {
    // Kocsi objektum letrehozasa 3 ulohellyel
    Kocsi kocsi1(3, 3);
    // 1 ulohely lefoglalasa
    kocsi1.reserveHely();

    // Stream letrehozasa
    std::stringstream ss;
    // kocsi objektum kiirasa stringstreambe
    kocsi1.write(ss);

    // Utvonal objektum letrehozasa beolvasashoz
    Kocsi kocsi2;
    // utvonal objektum beolvasa stringstreambol
    kocsi2.read(ss);

    // eredeti es beolvasott kocsi objektumok egyezesenek vizsgalata
    EXPECT_EQ(kocsi1.getAzonosito(), kocsi2.getAzonosito());
    EXPECT_EQ(kocsi1.getSzekek_szama(), kocsi2.getSzekek_szama());
    EXPECT_EQ(kocsi1.reserveHely(), kocsi2.reserveHely());
  }
  END

  // Vonat osztaly utvonal beallito es lekerdezo fuggvenyeinek vizsgalata
  TEST(VonatTest, UtvonalBeallitasEsLekerdezes)
  {
    // Utvonal objektum letrehozasa
    Utvonal utvonal;
    // Allomas objektumok letrehozasa az utvonal objektumon belul
    utvonal.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal.createAllomas("Debrecen", 12, 0, 14, 45);
    // Vonat objektum letrehozasa
    Vonat vonat;

    // utvonal beallitasa
    vonat.setUtvonal(utvonal);
    // utvonal lekerdezese es objektumban valo eltarolasa
    Utvonal kapott_utvonal = vonat.getUtvonal();

    // eredeti es vonat-bol kapott utvonalalak egyezesenek vizsgalata
    EXPECT_EQ(2, kapott_utvonal.getAllomasokSzama());
    EXPECT_EQ("Budapest", kapott_utvonal.getAllomas(0).getNev());
    EXPECT_EQ("Debrecen", kapott_utvonal.getAllomas(1).getNev());
  }
  END

  // Vonat osztály jegy hozzáadásának tesztelése
  TEST(VonatTest, JegyHozzaadas)
  {

    // Vonat objektumok letrehozasa
    Vonat vonat;

    // Ido objektumok letrehozasa a jegy-hez
    Ido indulo_idopont(8, 0);
    Ido cel_idopont(10, 30);

    // Jegy objektumok letrehozasa
    Jegy jegy(1, 12, 2, 3, "Budapest", indulo_idopont, "Debrecen", cel_idopont);

    // jegy hozzadasa a vonathoz
    vonat.addJegy(jegy);

    // eredeti es vonat-bol kapott jegyek egyezesenek vizsgalata
    EXPECT_EQ(true, (jegy == *vonat.getJegy(1)));
  }
  END

  // Vonat osztály indulási idő különbségének tesztelése
  TEST(VonatTest, IndulasiIdoKulonbseg)
  {
    // Utvonal objektum letrehozasa
    Utvonal utvonal;
    // Allomas objektumok letrehozasa az utvonal objektumon belul
    utvonal.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal.createAllomas("Debrecen", 12, 0, 14, 45);

    // Vonat objektum letrehozasa
    Vonat vonat;
    // utvonal beallitasa
    vonat.setUtvonal(utvonal);

    // Indulási idő különbség lekérdezése
    int kulonbseg = vonat.indulasiIdoKulonbseg("Budapest", 10, 9);

    // A különbség ellenőrzése
    // Az indulás ideje 10:30, ami 21 percel később van mint 10:9 perc
    EXPECT_EQ(21, kulonbseg); 
  }
  END

      return 0;
}