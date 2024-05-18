#ifndef UTVONAL_H
#define UTVONAL_H

#include "allomas.h"

#include "memtrace.h"
#include "serializable.h"

// Az Utvonal osztaly az egyes vonatutvonalakat reprezentalja.
// Tartalmazza az utvonal azonositojat, az allomasok szamat, valamint az allomasokat.
class Utvonal : public Serializable
{
  size_t utvonal_azonosito; // Az utvonal azonositoja
  size_t allomasok_szama;   // Az allomasok szama az utvonalon
  Allomas *allomasok;       // Az allomasok tombje az utvonalon.
public:
  // Az osztaly alapertelmezett konstruktora.
  Utvonal();

  // Az osztaly masolo konstruktora.
  // @param other - masolni kivant Utvonal objektum
  Utvonal(const Utvonal &other);

  // Allomas hozzaadasa az utvonalhoz.
  // @param allomas - hozzaadni kivant allomas
  void addAllomas(Allomas allomas);

  void createAllomas(std::string nev,  int indulas_ora, int indulas_perc, int erkezes_ora, int erkezes_perc);

  Utvonal &operator=(const Utvonal &other);

  // Allomas csereje az utvonalon.
  // @param index - az allomas indexe, amelyet cserelni kivanunk
  // @param allomas - beszurni kivant allomas
  void changeAllomas(size_t index, Allomas allomas);

  // Allomas eltavolitasa az utvonalrol.
  // @param index - az eltavolitani kivant allomas indexe
  void removeAllomas(size_t index);

  size_t getAllomasokSzama() const;

  Allomas& getAllomas(size_t i) const;

  void kiir(std::ostream &os) const;

  void write(std::ostream &os) const;

  void read(std::istream &is);

  // Az osztaly destruktora.
  ~Utvonal();
};

#endif // UTVONAL_H
