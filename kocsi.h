#ifndef KOCSI_H
#define KOCSI_H

#include <cstddef>
#include <iostream>

#include "memtrace.h"
#include "serializable.h"

// A Kocsi osztaly reprezentalja a vonatkocsikat.
// Tartalmazza a kocsi azonositojat, a szekek szamat, valamint a foglalt szekek szamat.
class Kocsi : public Serializable
{
  size_t kocsi_azonosito;      // A kocsi azonositoja.
  size_t szekek_szama;         // A kocsihoz tartozo szekek szama.
  size_t foglalt_szekek_szama; // A kocsihoz tartozo foglalt szekek szama.
public:
  // Az osztaly alapertelmezett konstruktora.
  Kocsi();

  // Az osztaly masoloi konstruktora.
  // @param other - masolni kivant Kocsi objektum
  Kocsi(const Kocsi &other);

  // Egyedi konstruktor.
  // @param azonosito - a kocsi azonositoja
  // @param szekek - a kocsihoz tartozo szekek szama
  Kocsi(size_t azonosito, size_t szekek);

  bool tele() const;
  // Szekek foglalasa a kocsiban.
  size_t reserveHely();

  // Szekek szamanak lekerdezese.
  // @return A kocsihoz tartozo szekek szama.
  size_t getSzekek_szama() const;

  size_t getAzonosito() const;

  virtual void write(std::ostream &os) const override;

  virtual void read(std::istream &is) override;

  // Az osztaly destruktora.
  ~Kocsi();
};

#endif // KOCSI_H
