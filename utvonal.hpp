#ifndef UTVONAL_HPP
#define UTVONAL_HPP

#include "allomas.hpp"

#include "memtrace.h"

// Az Utvonal osztaly az egyes vonatutvonalakat reprezentalja.
// Tartalmazza az utvonal azonositojat, az allomasok szamat, valamint az allomasokat.
class Utvonal {
  size_t utvonal_azonosito; // Az utvonal azonositoja
  size_t allomasok_szama;   // Az allomasok szama az utvonalon
  Allomas *allomasok;       // Az allomasok tombje az utvonalon.
public:
  // Az osztaly alapertelmezett konstruktora.
  Utvonal();

  // Az osztaly masolo konstruktora.
  // @param other - masolni kivant Utvonal objektum
  Utvonal(const Utvonal& other);

  // Allomas hozzaadasa az utvonalhoz.
  // @param allomas - hozzaadni kivant allomas
  void addAllomas(Allomas allomas);

  // Allomas csereje az utvonalon.
  // @param index - az allomas indexe, amelyet cserelni kivanunk
  // @param allomas - beszurni kivant allomas
  void changeAllomas(size_t index, Allomas allomas);

  // Allomas eltavolitasa az utvonalrol.
  // @param index - az eltavolitani kivant allomas indexe
  void removeAllomas(size_t index);

  // Operátor túlterhelés: Streambe írás a Utvonal osztályhoz.
  // @param os - referencia a kimeneti streamre
  // @param utvonal - referencia a kiírandó Utvonal objektumra
  // @return A kimeneti stream referenciaja
  friend std::ostream &operator<<(std::ostream &os, const Utvonal &utvonal);

  // Operátor túlterhelés: Streamből olvasás a Utvonal osztályhoz.
  // @param is - referencia a bemeneti streamre
  // @param utvonal - referencia a beolvasandó Utvonal objektumra
  // @return A bemeneti stream referenciaja
  friend std::istream &operator>>(std::istream &is, Utvonal &utvonal);

  // Az osztaly destruktora.
  ~Utvonal();
};

#endif // UTVONAL_HPP
