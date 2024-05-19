#ifndef KOCSI_H
#define KOCSI_H

// Szabványos bemenet és kimenet kezeléséhez.
#include <iostream>

// Interfész az objektumok sorosításához és deszerializálásához.
#include "serializable.h"

// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"

// A Kocsi osztaly reprezentalja a vonatkocsikat.
// Tartalmazza a kocsi azonositojat, a szekek szamat, valamint a foglalt szekek szamat.
class Kocsi : public Serializable
{
  size_t kocsi_azonosito;      // A kocsi azonositoja.
  size_t szekek_szama;         // A kocsihoz tartozo szekek szama.
  size_t foglalt_szekek_szama; // A kocsihoz tartozo foglalt szekek szama.
public:
  // Az osztály alapértelmezett konstruktora.
  Kocsi();

  // Az osztály másoló konstruktora.
  // @param other - Másolni kívánt Kocsi objektum.
  Kocsi(const Kocsi &other);

  // Egyedi konstruktor.
  // @param azonosito - A kocsi azonosítója.
  // @param szekek - A kocsiban található üres székek száma.
  Kocsi(size_t azonosito, size_t szekek);

  // Megvizsgálja, hogy a kocsiban van-e üres szék.
  // @return igaz, ha a kocsi tele van, különben hamis.
  bool tele() const;

  // Foglal egy helyet a kocsiban, és visszaadja a hely azonosítóját.
  // @return A foglalt hely azonosítója.
  size_t reserveHely();

  // Szákek számának lekérdezése.
  // @return A kocsihoz tartozó székek száma.
  size_t getSzekek_szama() const;

  // Az osztály azonosítójának lekérdezése.
  // @return A kocsi azonosítója.
  size_t getAzonosito() const;

  // Serializable interfész implementációja: objektum írása adatfolyamba.
  // @param os - Az írásra használt kimeneti adatfolyam.
  void write(std::ostream &os) const;

  // Serializable interfész implementációja: objektum olvasása adatfolyamból.
  // @param is - A beolvasásra használt bemeneti adatfolyam.
  void read(std::istream &is);

  // Az osztály destruktora.
  ~Kocsi();
};

#endif // KOCSI_H
