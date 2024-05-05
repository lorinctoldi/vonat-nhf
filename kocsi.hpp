#ifndef KOCSI_HPP
#define KOCSI_HPP

#include <cstddef>
#include <iostream>

#include "memtrace.h"

// A Kocsi osztaly reprezentalja a vonatkocsikat.
// Tartalmazza a kocsi azonositojat, a szekek szamat, valamint a foglalt szekek szamat.
class Kocsi {
  size_t kocsi_azonosito;       // A kocsi azonositoja.
  size_t szekek_szama;          // A kocsihoz tartozo szekek szama.
  size_t foglalt_szekek_szama;  // A kocsihoz tartozo foglalt szekek szama.
public:
  // Az osztaly alapertelmezett konstruktora.
  Kocsi();
  
  // Az osztaly masoloi konstruktora.
  // @param other - masolni kivant Kocsi objektum
  Kocsi(const Kocsi& other);
  
  // Egyedi konstruktor.
  // @param azonosito - a kocsi azonositoja
  // @param szekek - a kocsihoz tartozo szekek szama
  Kocsi(size_t azonosito, size_t szekek);
  
  // Szekek foglalasa a kocsiban.
  void szek_foglal();
  
  // Szekek szamanak lekerdezese.
  // @return A kocsihoz tartozo szekek szama.
  size_t getSzekek_szama() const;

  // Operátor túlterhelés: Streambe írás a Kocsi osztályhoz.
  // @param os - referencia a kimeneti streamre
  // @param kocsi - referencia a kiírandó Kocsi objektumra
  // @return A kimeneti stream referenciaja
  friend std::ostream &operator<<(std::ostream &os, const Kocsi &kocsi);

  // Operátor túlterhelés: Streamből olvasás a Kocsi osztályhoz.
  // @param is - referencia a bemeneti streamre
  // @param kocsi - referencia a beolvasandó Kocsi objektumra
  // @return A bemeneti stream referenciaja
  friend std::istream &operator>>(std::istream &is, Kocsi &kocsi);
  
  // Az osztaly destruktora.
  ~Kocsi();
};

#endif // KOCSI_HPP
