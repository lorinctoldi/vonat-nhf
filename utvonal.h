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

  Utvonal &operator=(const Utvonal &other);

  // Allomas csereje az utvonalon.
  // @param index - az allomas indexe, amelyet cserelni kivanunk
  // @param allomas - beszurni kivant allomas
  void changeAllomas(size_t index, Allomas allomas);

  // Allomas eltavolitasa az utvonalrol.
  // @param index - az eltavolitani kivant allomas indexe
  void removeAllomas(size_t index);

  void write(std::ostream &os) const
  {
    os << "===== Utvonal =====\n";
    os << "utvonal azonosito:\n";
    os << utvonal_azonosito << '\n';
    os << "allomasok szama:\n";
    os << allomasok_szama << '\n';
    for (size_t i = 0; i < allomasok_szama; ++i)
    {
      allomasok[i].write(os);
    }
  }

  void read(std::istream &is)
  {
    std::string header;
    std::getline(is, header); // "===== Utvonal ====="
    std::getline(is, header); // "utvonal azonosito:"
    is >> utvonal_azonosito;
    is.ignore();              // Ignore newline character
    std::getline(is, header); // "allomasok szama:"
    is >> allomasok_szama;
    is.ignore(); // Ignore newline character
    allomasok = new Allomas[allomasok_szama];
    for (size_t i = 0; i < allomasok_szama; ++i)
    {
      allomasok[i].read(is);
    }
  }

  // Az osztaly destruktora.
  ~Utvonal();
};

#endif // UTVONAL_H