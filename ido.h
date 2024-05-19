#ifndef IDO_H
#define IDO_H

// Szabványos bemenet és kimenet kezeléséhez.
#include <iostream>

// Interfész az objektumok sorosításához és deszerializálásához.
#include "serializable.h"

// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"

// Az Idő osztály reprezentál egy időpontot.
// Tartalmazza az időpontot alkotó órát és percet.
class Ido : public Serializable
{
private:
    int ora;  // Az idő objektumban tárolt óra. (0-23)
    int perc; // Az idő objektumban tárolt perc. (0-59)
public:
    // Az osztály alapértelmezett konstruktora.
    Ido();

    // Paraméteres konstruktor.
    // @param o - A tárolni kívánt óra.
    // @param p - A tárolni kívánt perc.
    Ido(int o, int p);

    // Az osztály másoló konstruktora.
    // @param other - Másolni kívánt Ido objektum.
    Ido(const Ido &other);

    // Getter függvény az óra lekérdezéséhez.
    // @return Az aktuális óra értéke.
    int getOra() const;

    // Getter függvény a perc lekérdezéséhez.
    // @return Az aktuális perc értéke.
    int getPerc() const;

    // Setter függvény az óra beállításához.
    // @param o - A beállítandó óra értéke.
    void setOra(int o);

    // Setter függvény a perc beállításához.
    // @param p - A beállítandó perc értéke.
    void setPerc(int p);

    // Idő beállítása adott óra és perc értékekkel.
    // @param o - A beállítandó óra értéke.
    // @param p - A beállítandó perc értéke.
    void setIdo(int o, int p);

    // Perc hozzáadása az aktuális időhöz.
    // @param p - A hozzáadandó perc értéke.
    void addPerc(int p);

    // Óra hozzáadása az aktuális időhöz.
    // @param o - A hozzáadandó óra értéke.
    void addOra(int o);

    // Egyenlőség operátor.
    // @param other - A másik idő, amivel az egyenlőség vizsgálat történik.
    // @return igaz, ha az idők megegyeznek, különben hamis.
    bool operator==(const Ido &other) const;

    // Nem egyenlőség operátor.
    // @param other - A másik idő, amivel a nem egyenlőség vizsgálat történik.
    // @return igaz, ha az idők nem egyeznek meg, különben hamis.
    bool operator!=(const Ido &other) const;

    // Objektum kiírása adatfolyamba esztétikus formában.
    // @param os - Az írásra használt kimeneti adatfolyam.
    void kiir(std::ostream &os) const;

    // Serializable interfész implementációja: objektum írása adatfolyamba.
    // @param os - Az írásra használt kimeneti adatfolyam.
    void write(std::ostream &os) const;

    // Serializable interfész implementációja: objektum olvasása adatfolyamból.
    // @param is - A beolvasásra használt bemeneti adatfolyam.
    void read(std::istream &is);

    // Az osztály destruktora.
    ~Ido();
};

#endif // IDO_H
