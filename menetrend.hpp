#ifndef MENETREND_HPP
#define MENETREND_HPP

#include "vonat.hpp"

#include "memtrace.h"

// A Menetrend osztaly reprezentalja a vonatok menetrendjet.
// Tartalmazza a vonatok szamat es a vonatokat.
class Menetrend
{
  size_t vonatok_szama; // A menetrendben szereplo vonatok szama.
  Vonat *vonatok;       // A menetrendben szereplo vonatok tombje.
public:
  // Az osztaly alapertelmezett konstruktora.
  Menetrend() : vonatok_szama(0), vonatok(NULL) {}

  // Egyedi konstruktor.
  // @param v - hozzaadni kivant vonat
  Menetrend(Vonat v);

  // Egyedi konstruktor.
  // @param v - a vonatok tombje
  // @param meret - a vonatok tombjenek merete
  Menetrend(Vonat *v, size_t meret) : vonatok_szama(meret), vonatok(v) {}

  // Masolo konstruktor.
  // @param m - masolni kivant Menetrend objektum
  Menetrend(const Menetrend &m);

  // Vonat hozzaadasa a menetrendhez.
  // @param v - hozzaadni kivant vonat
  void addVonat(Vonat v);

  // Vonat modositasa a menetrendben.
  // @param v - a modositando vonat
  // @param index - a vonat indexe a menetrendben
  void changeVonat(Vonat v, size_t index);

  // Vonat lekerdezese a megadott indexen.
  // @param index - a kivant vonat indexe
  // @return Az adott indexen talalhato vonat
  Vonat getVonat(size_t index);

  // Menetrend kiiratasa.
  void kiir();

  // Operátor túlterhelés: Streambe írás a Menetrend osztályhoz.
  // @param os - referencia a kimeneti streamre
  // @param menetrend - referencia a kiírandó Menetrend objektumra
  // @return A kimeneti stream referenciaja
  friend std::ostream &operator<<(std::ostream &os, const Menetrend &menetrend);

  // Operátor túlterhelés: Streamből olvasás a Menetrend osztályhoz.
  // @param is - referencia a bemeneti streamre
  // @param menetrend - referencia a beolvasandó Menetrend objektumra
  // @return A bemeneti stream referenciaja
  friend std::istream &operator>>(std::istream &is, Menetrend &menetrend);

  // Az osztaly destruktora.
  ~Menetrend();
};

#endif // MENETREND_HPP
