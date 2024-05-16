#ifndef ALLOMAS_H
#define ALLOMAS_H

#include "ido.h"

#include <iostream>

#include "memtrace.h"
#include "serializable.h"

class Allomas : public Serializable
{
  size_t allomas_azonosito; // Az allomas azonositoja.
  std::string nev;               // Az allomas neve.
  Ido indulas;              // Az indulasi idopontjanak taroloja.
  Ido erkezes;              // Az erkezesi idopontjanak taroloja.
public:
  // Az osztaly alapertelmezett konstruktora.
  Allomas();

  // Masolo konstruktor.
  // @param other - masolni kivant Allomas objektum
  Allomas(const Allomas &other);

  Allomas &operator=(const Allomas &other);

  // Egyedi konstruktor.
  // @param azonosito - az allomas azonositoja
  // @param nev - az allomas neve
  // @param indulas_ora - az indulasi ora
  // @param indulas_perc - az indulasi perc
  // @param erkezes_ora - az erkezesi ora
  // @param erkezes_perc - az erkezesi perc
  Allomas(size_t azonosito, const std::string &nev, int indulas_ora, int indulas_perc, int erkezes_ora, int erkezes_perc);

  // Az erkezesi ido modositasa.
  // @param ora - az uj erkezesi ora
  // @param perc - az uj erkezesi perc
  void changeErkezes(int ora, int perc);

  // Az indulasi ido modositasa.
  // @param ora - az uj indulasi ora
  // @param perc - az uj indulasi perc
  void changeIndulas(int ora, int perc);

  // Az allomas nevenek modositasa.
  // @param other - az uj nev
  void changeNev(const std::string &other);

  // Az indulasi ora lekerdezese.
  // @return Az indulasi ora
  int getIndulasOra();

  // Az indulasi perc lekerdezese.
  // @return Az indulasi perc
  int getIndulasPerc();

  // Az erkezesi ora lekerdezese.
  // @return Az erkezesi ora
  int getErkezesOra();

  // Az erkezesi perc lekerdezese.
  // @return Az erkezesi perc
  int getErkezesPerc();

  Ido& getIndulas() {
    return indulas;
  }

  Ido& getErkezes() {
    return erkezes;
  }

  // Az allomas nevenek lekerdezese.
  // @return Az allomas neve
  std::string &getNev();

  void write(std::ostream &os) const
  {
       os << "===== Allomas =====\n";
    os << "allomas azonosito:\n";
    os << allomas_azonosito << '\n';
    os << "nev:\n";
    os << nev << '\n';
    os << "indulas:\n";
    indulas.write(os);
    os << "erkezes:\n";
    erkezes.write(os);
  }

  void read(std::istream &is)
  {
    std::string header;
    std::getline(is, header); // "===== Allomas ====="
    std::getline(is, header); // "allomas azonosito:"
    is >> allomas_azonosito;
    is.ignore();              // Ignore newline character
    std::getline(is, header); // "nev:"
    std::getline(is, nev);    // Directly read into std::string
    std::getline(is, header); // "indulas:"
    indulas.read(is);
    std::getline(is, header); // "erkezes:"
    erkezes.read(is);
  }

  // Az osztaly destruktora.
  ~Allomas();
};

#endif // ALLOMAS_H
