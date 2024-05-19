#include "test.h"

// Programhoz tartozó teszteket futtató függvény
// @param void
// @return void
void test()
{
  // Idő osztály kiiírás funkciójánák vizsgálata
  TEST(IdoKiiras, Test1)
  {
    // StringStream létrehozása a kiíráshoz
    std::stringstream ss;

    // idő objektumok létrehozása paraméteres konstruktorokkal
    Ido i1(10, 12); // 10 óra, 12 perc
    Ido i2(2, 1);   // 2 óra, 1 perc

    // idő objektumok kiírása
    i1.kiir(ss); // vart: "10:12"
    i2.kiir(ss); // vart: "02:01"

    // kiírt értékek vizsgálata
    EXPECT_STREQ("10:12\n02:01\n", ss.str().c_str());
  }
  END

  // Idő osztály perzisztenciájának vizsgálata
  TEST(IdoPerzisztencia, Test2)
  {
    // StringStream létrehozása
    std::stringstream ss;

    // idő objektum létrehozása paraméteres konstruktorokkal
    Ido ido1(8, 30); // 8 óra, 30 perc
    // idő objektum létrehozása beolvasáshoz
    Ido ido2;

    // ido1 objektum kiírása StringStream-be
    ido1.write(ss);

    // ido2 objektum beolvasása a StringStream-ből
    ido2.read(ss);

    // idő objektumok egyezésének vizsgálata
    EXPECT_TRUE(ido1 == ido2);
  }
  END

  // Ido osztály alapvető műveleteinek vizsgálata
  TEST(IdoMuveletek, Test3)
  {
    // idő objektum létrehozása paraméteres konstruktorokkal
    Ido i(2, 45); // 2 óra, 45 perc

    // konstruktor értékbeállításának vizsgálata
    EXPECT_EQ(2, i.getOra());
    EXPECT_EQ(45, i.getPerc());

    // új értékek beállítása setter függvényekel
    i.setOra(3);
    i.setPerc(15);

    // setterek működésének ellenőrzése
    EXPECT_EQ(3, i.getOra());
    EXPECT_EQ(15, i.getPerc());

    // órák és percek hozzáadása
    i.addOra(2);
    i.addPerc(30);

    // aritmetikai művelet ellenőrzése
    // 3 óra 15 perc + 2 óra 30 perc = 5 óra 45perc
    EXPECT_EQ(5, i.getOra());
    EXPECT_EQ(45, i.getPerc());

    // idő objektum létrehozása egyezés vizsgálathoz
    Ido j(1, 30);

    // egyenlőség operátor ellenőrzése
    EXPECT_FALSE(i == j);

    // különbözőség operátor ellenőrzése
    EXPECT_TRUE(i != j);
  }
  END

  // Állomás konstruktorának vizsgálata
  TEST(AllomasKonstruktor, Test4)
  {
    // állomás létrehozása konstruktorral
    Allomas allomas;

    // paraméterek helyes beállítottságának vizsgálata
    EXPECT_EQ(0, allomas.getIndulasOra());
    EXPECT_EQ(0, allomas.getIndulasPerc());
    EXPECT_EQ(0, allomas.getErkezesOra());
    EXPECT_EQ(0, allomas.getErkezesPerc());
    EXPECT_EQ("", allomas.getNev());

    // állomás létrehozása paraméteres konstruktorral
    Allomas allomas_2(123, "Teszt Allomas", 10, 30, 12, 45);

    // paraméterek helyes beállítottságának vizsgálata
    EXPECT_EQ(12, allomas_2.getIndulasOra());
    EXPECT_EQ(45, allomas_2.getIndulasPerc());
    EXPECT_EQ(10, allomas_2.getErkezesOra());
    EXPECT_EQ(30, allomas_2.getErkezesPerc());
    EXPECT_EQ("Teszt Allomas", allomas_2.getNev());
  }
  END

  // Állomás osztály attribútum változtatásának vizsgálata
  TEST(AllomasModositas, Test5)
  {
    // állomás létrehozása paraméteres konstruktorral
    Allomas allomas(123, "Teszt Allomas", 10, 30, 12, 45);

    // indulás és érkezés időpontjainak változtatása
    allomas.changeIndulas(11, 0);
    allomas.changeErkezes(10, 45);

    // indulás és érkezés sikeres változtatásának ellenőrzése
    EXPECT_EQ(11, allomas.getIndulasOra());
    EXPECT_EQ(0, allomas.getIndulasPerc());
    EXPECT_EQ(10, allomas.getErkezesOra());
    EXPECT_EQ(45, allomas.getErkezesPerc());

    // állomás létrehozása paraméteres konstruktorral
    Allomas allomas_2(123, "Teszt Allomas", 10, 30, 12, 45);

    // nev paraméter módosítása
    allomas_2.changeNev("Uj Teszt Allomas");

    // nev paraméter állításának ellenőrzése
    EXPECT_EQ("Uj Teszt Allomas", allomas_2.getNev());
  }
  END

  // Állomás osztály perzisztenciájának vizsgálata
  TEST(AllomasPerzisztencia, Test6)
  {
    // StringStream létrehozása
    std::stringstream ss;

    // állomás létrehozása paraméteres konstruktorral
    Allomas allomas1(123, "Teszt Allomas", 10, 30, 12, 45);
    // állomás létrehozása beolvasáshoz
    Allomas allomas2;

    // állomás kiírása StringStream-be
    allomas1.write(ss);

    // állomás beolvasása StringStream-ből
    allomas2.read(ss);

    // eredeti es beolvasott objektum egyezésének vizsgálata
    EXPECT_EQ(allomas1.getNev(), allomas2.getNev());
    EXPECT_EQ(allomas1.getIndulasOra(), allomas2.getIndulasOra());
    EXPECT_EQ(allomas1.getIndulasPerc(), allomas2.getIndulasPerc());
    EXPECT_EQ(allomas1.getErkezesOra(), allomas2.getErkezesOra());
    EXPECT_EQ(allomas1.getErkezesPerc(), allomas2.getErkezesPerc());
  }
  END

  // Útvonal osztály állomás hozzáadás függvényének vizsgálata
  TEST(UtvonalAllomasHozzaadas, Test7)
  {
    // Útvonal objektum létrehozása
    Utvonal utvonal;

    // állomás objektum létrehozása paraméteres konstruktorral
    Allomas allomas1(1, "Allomas1", 9, 0, 9, 5);
    Allomas allomas2(2, "Allomas2", 10, 0, 10, 5);

    // állomások hozzáadása az útvonalhoz
    utvonal.addAllomas(allomas1);
    utvonal.addAllomas(allomas2);

    // útvonalban tárolt állomások ellenőrzése
    EXPECT_EQ(2, utvonal.getAllomasokSzama());
    EXPECT_EQ("Allomas1", utvonal.getAllomas(0).getNev());
    EXPECT_EQ("Allomas2", utvonal.getAllomas(1).getNev());
  }
  END

  // Útvonal állomás cseréjének vizsgálata
  TEST(UtvonalAllomasCsere, Test8)
  {
    // Útvonal létrehozása
    Utvonal utvonal;

    // állomások létrehozása paraméteres konstruktorral
    Allomas allomas1(1, "Allomas1", 9, 0, 9, 5);
    Allomas allomas2(2, "Allomas2", 10, 0, 10, 5);
    Allomas allomas3(3, "Allomas3", 11, 0, 11, 5);

    // állomásokok hozzáadása az útvonalhoz
    utvonal.addAllomas(allomas1);
    utvonal.addAllomas(allomas2);

    // útvonalban tárolt 2. állomás cseréje másik állomásra
    utvonal.changeAllomas(1, allomas3);

    // útvonalban tárolt állomások vizsgálata a csere után
    EXPECT_EQ(2, utvonal.getAllomasokSzama());
    EXPECT_EQ("Allomas1", utvonal.getAllomas(0).getNev());
    EXPECT_EQ("Allomas3", utvonal.getAllomas(1).getNev());
  }
  END

  // Útvonal osztály perzisztenciájának vizsgálata
  TEST(UtvonalPerzisztencia, Test9)
  {
    // Útvonal létrehozása
    Utvonal utvonal;

    // állomások létrehozása paraméteres konstruktorral
    Allomas allomas1(1, "Allomas1", 9, 0, 9, 5);
    Allomas allomas2(2, "Allomas2", 10, 0, 10, 5);

    // állomásokok hozzáadása az útvonalhoz
    utvonal.addAllomas(allomas1);
    utvonal.addAllomas(allomas2);

    // StringStream létrehozása
    std::stringstream ss;
    // útvonal objektum kiírása StringStream-be
    utvonal.write(ss);

    // útvonal objektum létrehozása beolvasáshoz
    Utvonal utvonal2;

    // útvonal objektum beolvasása StringStream-ből
    utvonal2.read(ss);

    // útvonal objektumok egyezésének vizsgálata
    EXPECT_EQ(utvonal.getAllomasokSzama(), utvonal2.getAllomasokSzama());
    EXPECT_EQ(utvonal.getAllomas(0).getNev(), utvonal2.getAllomas(0).getNev());
    EXPECT_EQ(utvonal.getAllomas(1).getNev(), utvonal2.getAllomas(1).getNev());
  }
  END

  // Kocsi osztály szék foglalás funkciójának vizsgálata
  TEST(KocsiHelyFoglalas, Test10)
  {
    // Kocsi objektum létrehozása 5 űlőhely kapacitással
    Kocsi kocsi(1, 5);

    // minden űlőhely lefoglalasa
    EXPECT_EQ(0, kocsi.reserveHely());
    EXPECT_EQ(1, kocsi.reserveHely());
    EXPECT_EQ(2, kocsi.reserveHely());
    EXPECT_EQ(3, kocsi.reserveHely());
    EXPECT_EQ(4, kocsi.reserveHely());

    // nincs több szabad hely, foglalásnál hibát kell dobnia
    EXPECT_THROW(kocsi.reserveHely(), const char *);
  }
  END

  // Kocsi osztály foglaltság ellenőrző függvényének vizsgálata
  TEST(KocsiTele, Test11)
  {
    // Kocsi objektum létrehozása 2 űlőhely kapacitással
    Kocsi kocsi(2, 2);

    // van szabad hely, a tele függvény hamis értéket kell adjon
    EXPECT_FALSE(kocsi.tele());

    // minden űlőhely lefoglalasa
    kocsi.reserveHely();
    kocsi.reserveHely();

    // nincs több szabad hely,  a tele függvény igaz értéket kell adjon
    EXPECT_TRUE(kocsi.tele());
  }
  END

  // Kocsi osztály perzisztenciájának vizsgálata
  TEST(KocsiPerzisztencia, Test12)
  {
    // Kocsi objektum létrehozása 3 űlőhely kapacitással
    Kocsi kocsi1(3, 3);
    // 1 hely lefoglalása
    kocsi1.reserveHely();

    // StringStream létrehozása
    std::stringstream ss;

    // kocsi objektum kiírása StringStream-be
    kocsi1.write(ss);

    // kocsi objektum létrehozása beolvasáshoz
    Kocsi kocsi2;

    // kcosi objektum beolvasása a StringStream-ből
    kocsi2.read(ss);

    // kocsi objektumok egyezésének vizsgálata
    EXPECT_EQ(kocsi1.getAzonosito(), kocsi2.getAzonosito());
    EXPECT_EQ(kocsi1.getSzekek_szama(), kocsi2.getSzekek_szama());
    EXPECT_EQ(kocsi1.reserveHely(), kocsi2.reserveHely());
  }
  END

  // Vonat osztály útvonal beállíto és lekérdező függvényeinek vizsgálata
  TEST(VonatUtvonalBeallitas, Test13)
  {
    // Útvonal objektum létrehozása
    Utvonal utvonal;

    // állomások létrehozása az útvonalon
    utvonal.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal.createAllomas("Debrecen", 12, 0, 14, 45);

    // Vonat objektum létrehozása
    Vonat vonat;

    // útvonal beállítása
    vonat.setUtvonal(utvonal);

    // útvonal lekérdezése és eltárolása
    Utvonal kapott_utvonal = vonat.getUtvonal();

    // eredeti es beolvasott objektum egyezésének vizsgálata
    EXPECT_EQ(2, kapott_utvonal.getAllomasokSzama());
    EXPECT_EQ("Budapest", kapott_utvonal.getAllomas(0).getNev());
    EXPECT_EQ("Debrecen", kapott_utvonal.getAllomas(1).getNev());
  }
  END

  // Vonat osztály jegy hozzáadó függvényének vizsgálata
  TEST(VonatJegyHozzaadas, Test14)
  {
    // Vonat objektumok létrehozása
    Vonat vonat;

    // idő objektum létrehozása paraméteres konstruktorokkal
    Ido indulo_idopont(8, 0); // 8 óra, 0 perc
    Ido cel_idopont(10, 30);  // 10 óra, 30 perc

    // Jegy létrehozása
    Jegy jegy(1, 12, 2, 3, "Budapest", indulo_idopont, "Debrecen", cel_idopont);

    // jegy hozzáadása a vonathoz
    vonat.addJegy(jegy);

    // eredeti és vonat-ból kapott jegyek egyezésének vizsgálata
    EXPECT_EQ(true, (jegy == *vonat.getJegy(1)));
  }
  END

  // Vonat osztaly indulási idő különbség számító függvényének vizsgálata
  TEST(VonatIndulasiIdoKulonbseg, Test15)
  {
    // Útvonal objektum létrehozása
    Utvonal utvonal;

    // állomások létrehozása az útvonalon
    utvonal.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal.createAllomas("Debrecen", 12, 0, 14, 45);

    // Vonat objektum létrehozása
    Vonat vonat;

    // útvonal beállítása
    vonat.setUtvonal(utvonal);

    // idő különbség kiszámítása a vonat indulása Budapest állomásról és a megadott időpont között
    int kulonbseg = vonat.indulasiIdoKulonbseg("Budapest", 10, 9);

    // különbség ellenőzrése
    // az állomásról való indulás ideje 10:30, ami 21 percel később van mint a megadott 10:09
    EXPECT_EQ(21, kulonbseg);
  }
  END

  // Vonat osztály perzisztenciájának vizsgálata
  TEST(VonatPerzisztencia, Test16)
  {
    // Kocsik létrehozása
    Kocsi kocsi1(1, 50);
    Kocsi kocsi2(2, 60);
    Kocsi kocsik[] = {kocsi1, kocsi2};

    // Idő objektumok létrehozása
    Ido indulo_ido(8, 0);
    Ido cel_ido(10, 30);

    // Jegyek létrehozása
    Jegy jegy1(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido);
    KedvezmenyesJegy jegy2(1, 13, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido, -0.4, "Kedvezmenyes jegy");
    FelarasJegy jegy3(1, 13, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido, 0.4, "Felaras jegy");

    // jegyek tömbbe foglalása
    Jegy *jegyek[] = {&jegy1, &jegy2, &jegy3};

    // Útvonal létrehozása ás állomások hozzáadása
    Utvonal utvonal;

    // állomások létrehozása az útvonalon
    utvonal.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal.createAllomas("Debrecen", 12, 0, 14, 45);

    // Vonat létrehozása konstruktorral
    Vonat vonat1(1, 2, kocsik, utvonal, 3, jegyek);

    // StringStream létrehozása
    std::stringstream ss;

    // vonat objektum kiírása StringStream-be
    vonat1.write(ss);

    // vonat objektum létrehozása beolvasáshoz
    Vonat vonat2;

    // kcosi objektum beolvasása a StringStream-ből
    vonat2.read(ss);

    // vonatok egyezésének vizsgálata
    EXPECT_EQ(vonat1.getAzonosito(), vonat2.getAzonosito());
    EXPECT_EQ(vonat1.getUtvonal().getAllomasokSzama(), vonat2.getUtvonal().getAllomasokSzama());
    EXPECT_EQ(vonat1.getUtvonal().getAllomas(0).getNev(), vonat2.getUtvonal().getAllomas(0).getNev());
    EXPECT_EQ(vonat1.getUtvonal().getAllomas(1).getNev(), vonat2.getUtvonal().getAllomas(1).getNev());
    EXPECT_EQ(true, *vonat2.getJegy(1) == jegy1);
    EXPECT_EQ(true, *vonat2.getJegy(2) == jegy2);
    EXPECT_EQ(true, *vonat2.getJegy(3) == jegy3);
  }
  END

  // Jegy osztály == operátorának vizsgálata
  TEST(JegyEgyezes, Test17)
  {
    // idő objektumok létrehozása paraméteres konstruktorokkal
    Ido indulo_ido(8, 0);
    Ido cel_ido(10, 30);

    // jegyek létrehozása
    Jegy jegy1(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido);
    Jegy jegy2(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido);

    // jegyek egyezésének vizsgálata
    EXPECT_TRUE(jegy1 == jegy2);
  }
  END

  // Jegy osztály másoló konstruktorának vizsgálata
  TEST(JegyMásolóKonstruktor, Test18)
  {
    // idő objektumok létrehozása paraméteres konstruktorokkal
    Ido indulo_ido(8, 0);
    Ido cel_ido(10, 30);

    // jegy létrehozása
    Jegy jegy1(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido);
    // jegy létrehozása másoló konstruktorral
    Jegy jegy2(jegy1);

    // jegyek egyezésének vizsgálata
    EXPECT_TRUE(jegy1 == jegy2);
  }
  END

  //  Jegy osztály értékadó operátorának vizsgálata
  TEST(JegyErtekadoOperator, Test19)
  {
    // idő objektumok létrehozása paraméteres konstruktorokkal
    Ido indulo_ido(8, 0);
    Ido cel_ido(10, 30);

    // jegy létrehozása
    Jegy jegy1(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido);
    // jegy létrehozása értékadáshoz
    Jegy jegy2;

    // jegy értéküladása
    jegy2 = jegy1;

    // jegyek egyezésének vizsgálata
    EXPECT_TRUE(jegy1 == jegy2);
  }
  END

  // Jegy osztály perzisztenciájának vizsgálata
  TEST(JegyPerzisztencia, Test20)
  {
    // idő objektumok létrehozása paraméteres konstruktorokkal
    Ido indulo_ido(8, 0);
    Ido cel_ido(10, 30);

    // jegy létrehozása
    Jegy jegy1(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido);

    // StringStream létrehozása
    std::stringstream ss;

    // jegy kiírása StringStream-be
    jegy1.write(ss);

    // jegy létrehozása beolvasáshoz
    Jegy jegy2;

    // jegy beolvasása StringStream-ből
    jegy2.read(ss);

    // jegyek egyezésének vizsgálata
    EXPECT_TRUE(jegy1 == jegy2);
  }
  END

  // Felarasjegy osztály perzisztenciájának vizsgálata
  TEST(FelarasjegyPerzisztencia, Test21)
  {
    // idő objektumok létrehozása paraméteres konstruktorokkal
    Ido indulo_ido(8, 0);
    Ido cel_ido(10, 30);

    // felarasjegy létrehozása
    FelarasJegy jegy1(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido, 0.4, "jegy");

    // StringStream létrehozása
    std::stringstream ss;

    // jegy kiírása StringStream-be
    jegy1.write(ss);

    // jegy létrehozása beolvasáshoz
    FelarasJegy jegy2;

    // jegy beolvasása StringStream-ből
    jegy2.read(ss);

    // jegyek egyezésének vizsgálata
    EXPECT_TRUE(jegy1 == jegy2);
  }
  END

  // Kedvezmenyesjegy osztály perzisztenciájának vizsgálata
  TEST(KedvezmenyesjegyPerzisztencia, Test22)
  {
    // idő objektumok létrehozása paraméteres konstruktorokkal
    Ido indulo_ido(8, 0);
    Ido cel_ido(10, 30);

    // kedvezmenyesjegy létrehozása
    KedvezmenyesJegy jegy1(1, 12, 2, 3, "Budapest", indulo_ido, "Debrecen", cel_ido, 0.4, "jegy");

    // StringStream létrehozása
    std::stringstream ss;

    // jegy kiírása StringStream-be
    jegy1.write(ss);

    // jegy létrehozása beolvasáshoz
    FelarasJegy jegy2;

    // jegy beolvasása StringStream-ből
    jegy2.read(ss);

    // jegyek egyezésének vizsgálata
    EXPECT_TRUE(jegy1 == jegy2);
  }
  END

  // Állomás konstruktorának vizsgálata
  TEST(MenetrendKonstruktor, Test23)
  {
    // menetrend objektum létrehozása
    Menetrend menetrend;

    // paraméterek helyes beállítottságának vizsgálata
    EXPECT_EQ(0, menetrend.getVonatokSzama());
  }
  END

  // Menetrend vonat hozzáadó függvényének vizsgálata
  TEST(MenetrendVonatHozzaadas, Test24)
  {
    // menetrend objektum létrehozása
    Menetrend menetrend;

    // útvonal objektum létrehozása
    Utvonal utvonal;

    // állomások létrehozása az útvonalon
    utvonal.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal.createAllomas("Debrecen", 12, 0, 14, 45);

    // vonat lérehozása az útvonallal
    Vonat vonat(1, 0, nullptr, utvonal, 0, nullptr);

    // vonat hozzáadása a menetrendhez
    menetrend.addVonat(vonat);

    // vonat hozzáadásának ellenőrzése
    EXPECT_EQ(1, menetrend.getVonatokSzama());
  }
  END

  // Menetrend vonat módosításának vizsgálata
  TEST(MenetrendVonatCsere, Test24)
  {
    // menetrend objektum létrehozása
    Menetrend menetrend;

    // útvonal objektumok létrehozása
    Utvonal utvonal1, utvonal2;

    // állomások létrehozása az útvonalon
    utvonal1.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal1.createAllomas("Debrecen", 12, 0, 14, 45);
    utvonal2.createAllomas("Miskolc", 9, 0, 11, 30);
    utvonal2.createAllomas("Szeged", 13, 0, 15, 45);

    // vonatok lérehozása az útvonallal
    Vonat vonat1(1, 0, nullptr, utvonal1, 0, nullptr);
    Vonat vonat2(2, 0, nullptr, utvonal2, 0, nullptr);

    // vonat hozzáadása a menetrendhez
    menetrend.addVonat(vonat1);

    // hozzáadott vonat cseréje
    menetrend.changeVonat(vonat2, 0);

    // vonat cseréjének ellenőrzése
    EXPECT_EQ(1, menetrend.getVonatokSzama());
  }
  END

  // Menetrend osztály perzisztenciájának vizsgálata
  TEST(MenetrendPerzisztencia, Test25)
  {
    // menetrend objektum létrehozása
    Menetrend menetrend1;

    // útvonal objektum létrehozása
    Utvonal utvonal;

    // állomások létrehozása az útvonalon
    utvonal.createAllomas("Budapest", 8, 0, 10, 30);
    utvonal.createAllomas("Debrecen", 12, 0, 14, 45);

    // vonat lérehozása az útvonallal
    Vonat vonat(1, 0, nullptr, utvonal, 0, nullptr);

    // vonat hozzáadása a menetrendhez
    menetrend1.addVonat(vonat);

    // Menetrend kiírása StringStream-be
    std::stringstream ss;
    // menetrend kiírása StringStream-be
    menetrend1.write(ss);

    // Menetrend objektum létrehozása beolvasáshoz
    Menetrend menetrend2;
    // menetrend beolvasása StringStream-ből
    menetrend2.read(ss);

    // menetrendek egyezésének vizsgálata
    EXPECT_EQ(menetrend1.getVonatokSzama(), menetrend2.getVonatokSzama());
    EXPECT_EQ(menetrend1.getVonat(0).getAzonosito(), menetrend2.getVonat(0).getAzonosito());
  }
  END
}
