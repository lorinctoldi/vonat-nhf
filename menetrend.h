#ifndef MENETREND_H
#define MENETREND_H

#include "vonat.h"

#include "serializable.h"
#include "memtrace.h"

// A Menetrend osztaly reprezentalja a vonatok menetrendjet.
// Tartalmazza a vonatok szamat es a vonatokat.
class Menetrend : public Serializable
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
  Vonat &getVonat(size_t index) const;

  size_t getVonatokSzama() const;

  void removeVonat(size_t index);

  void createJegy(std::string indulo, std::string erkezo, int indulo_ora, int indulo_perc, double discountOrFee = 0, const std::string &tipus = "");

  void clear()
  {
    if (vonatok_szama > 0)
    {
      delete[] vonatok;
      vonatok = nullptr;
      vonatok_szama = 0;
    }
  }

  // Menetrend kiiratasa.
  void kiir(std::ostream &os, std::string indulo, std::string erkezo) const;

  virtual void write(std::ostream &os) const override
  {
    os << "===== Menetrend =====\n";
    os << "Vonatok szama:\n";
    os << vonatok_szama << '\n';
    for (size_t i = 0; i < vonatok_szama; ++i)
    {
      vonatok[i].write(os);
    }
  }

  virtual void read(std::istream &is) override
  {
    std::string header;
    std::getline(is, header); // "===== Menetrend ====="
    std::getline(is, header); // "Vonatok szama:"
    is >> vonatok_szama;
    is.ignore(); // Ignore newline character
    vonatok = new Vonat[vonatok_szama];
    for (size_t i = 0; i < vonatok_szama; ++i)
    {
      vonatok[i].read(is);
    }
  }

  // Az osztaly destruktora.
  ~Menetrend();
};

#endif // MENETREND_H
