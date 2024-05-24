#ifndef VONAT_H
#define VONAT_H

#include <iostream>

#include "memtrace.h"

#include "serializable.h"
#include "kocsi.h"
#include "jegy.h"
#include "utvonal.h"

/// A Vonat osztály a reprezentálja a vonatokat.
/// Tartalmazza a vonat azonosítóját, a vonathoz tartozó kocsik számát, a kocsik tömbjét,
/// a vonathoz tartozó jegyeket, azok számát, valamint az útvonalát.
class Vonat : public Serializable
{
private:
    int vonat_azonosito; /// A vonat azonosítója.
    int kocsik_szama;    /// A vonathoz tartozó kocsik száma.
    int jegyek_szama;    /// A vonathoz tartozó jegyek száma.
    Kocsi *kocsik;          /// A vonathoz tartozó kocsik tömbje.
    Jegy **jegyek;          /// A vonathoz tartozó jegyek tömbje.
    Utvonal utvonal;        /// A vonathoz tartozó útvonal.
public:
    /// Az osztály alapértelmezett konstruktora.
    Vonat();

    /// Az osztály másoló konstruktora.
    /// @param other - Másolni kívánt Vonat objektum.
    Vonat(const Vonat &other);

    /// Értékadó operátor.
    /// @param other - Másolni kívánt Vonat objektum.
    /// @return Az értékadás eredménye, az új Vonat objektum referenciája.
    Vonat &operator=(const Vonat &other);

    /// Paraméteres konstruktor.
    /// @param azonosito - A vonat azonosítója.
    /// @param kocsik_sz - A vonathoz tartozó kocsik száma.
    /// @param kocsik_tomb - A kocsik tömbje.
    /// @param utv - Az útvonal, amelyhez a vonat tartozik.
    /// @param jegyek_sz - A vonathoz tartozó jegyek száma.
    /// @param jegyek_ptr - A jegyek tömbjére mutató pointer.
    Vonat(int azonosito, int kocsik_sz, Kocsi kocsik_tomb[], Utvonal utv, int jegyek_sz, Jegy **jegyek_ptr);

    /// Azonosító lekérdezése.
    /// @return A vonat azonosítója.
    int getAzonosito() const;

    /// Útvonal lekérdezése.
    /// @return Az útvonal, amelyhez a vonat tartozik.
    Utvonal getUtvonal() const;

    /// Azonosító beállítása.
    /// @param azonosito - Az új vonat azonosítója.
    void setAzonosito(int azonosito);

    /// Útvonal beállítása.
    /// @param utvonal - az útvonal, amelyhez a vonat tartozik
    void setUtvonal(const Utvonal &utvonal);

    /// Kocsi hozzáadása a vonathoz.
    /// @param kocsi - hozzáadni kívánt kocsi
    void addKocsi(Kocsi &kocsi);

    /// Új kocsi létrehozása a vonathoz.
    /// @param szekek - Az új kocsin elérhető székek száma.
    void createKocsi(int szekek);

    /// Jegy hozzáadása a vonathoz.
    /// @param jegy - hozzáadni kívánt jegy
    void addJegy(Jegy &jegy);

    /// Jegy lekérdezése adott indexen.
    /// @param index - A jegy indexe a tömbben.
    /// @return Az adott indexen található jegy pointer.
    Jegy *getJegy(int index) const;

    /// Ellenőrzi, hogy létezik-e útvonal az adott indulási és érkezési állomások között.
    /// @param indulo - Az indulási állomás neve.
    /// @param erkezo - Az érkezési állomás neve.
    /// @return igaz, ha létezik útvonal, különben hamis.
    bool routeExists(const char* indulo, const char* erkezo) const;

    /// Megkeresi az állomás indexét az állomás neve alapján.
    /// @param nev - Az állomás neve, aminek az indexét keresi.
    /// @return Az állomás indexe, vagy -1, ha nem található az állomás.
    int findAllomas(const char* nev) const;

    /// Meghatározza, hogy hány perc különbség van a megadott időpont és a vonat indulásának időpontja között.
    /// @param nev - Az állomás neve, ahonnan az indulási időt számítja.
    /// @param ora - Az indulási idő órája.
    /// @param perc - Az indulási idő perce.
    /// @return Perc különbség van a megadott időpont és a vonat indulásának időpontja között
    ///         vagy -1, ha az állomás nem található vagy a vonat hamarabb indul mint a megadott időpont.
    int indulasiIdoKulonbseg(const char* nev, int ora, int perc) const;

    /// Új jegy létrehozása az adott indulási és érkezési állomások között.
    /// @param indulo - Az indulási állomás neve.
    /// @param erkezo - Az érkezési állomás neve.
    /// @param indulo_ora - Az indulási idő órája (alapértelmezett érték: 0).
    /// @param indulo_perc - Az indulási idő perce (alapértelmezett érték: 0).
    /// @param discountOrFee - Kedvezmény vagy felár mértéke (alapértelmezett érték: 0).
    /// @param tipus - Jegy típusa (alapértelmezett érték: üres string).
    /// @return Az újonnan létrehozott jegy azonosítója.
    int createJegy(const char* indulo, const char* erkezo, int indulo_ora = 0, int indulo_perc = 0, double discountOrFee = 0, const char* tipus = "");

    /// Serializable interfész implementációja: objektum írása adatfolyamba.
    /// @param os - Az írásra használt kimeneti adatfolyam.
    void write(std::ostream &os) const;

    /// Serializable interfész implementációja: objektum olvasása adatfolyamból.
    /// @param is - A beolvasásra használt bemeneti adatfolyam.
    void read(std::istream &is);

    /// Az osztály destruktora.
    ~Vonat();
};

#endif /// VONAT_H
