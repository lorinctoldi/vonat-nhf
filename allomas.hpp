#ifndef ALLOMAS_HPP
#define ALLOMAS_HPP

#include <cstddef>
#include <iostream>
#include <cstring>

#include "memtrace.h"

class Allomas
{
  size_t allomas_azonosito;   // Az allomas azonositoja.
  char *nev;                  // Az allomas neve.
  int indulas_ora;            // Az indulasi ora.
  int indulas_perc;           // Az indulasi perc.
  int erkezes_ora;            // Az erkezesi ora.
  int erkezes_perc;           // Az erkezesi perc.
public:
  // Az osztaly alapertelmezett konstruktora.
  Allomas();

  // Masolo konstruktor.
  // @param other - masolni kivant Allomas objektum
  Allomas(const Allomas &other);

  // Egyedi konstruktor.
  // @param azonosito - az allomas azonositoja
  // @param nev - az allomas neve
  // @param indulas_ora - az indulasi ora
  // @param indulas_perc - az indulasi perc
  // @param erkezes_ora - az erkezesi ora
  // @param erkezes_perc - az erkezesi perc
  Allomas(size_t azonosito, char* nev, int indulas_ora, int indulas_perc,  int erkezes_ora, int erkezes_perc);

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
  void changeNev(char *other);

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

  // Az allomas nevenek lekerdezese.
  // @return Az allomas neve
  const char* getNev();

  // Operátor túlterhelés: Streambe írás a Allomas osztályhoz.
  // @param os - referencia a kimeneti streamre
  // @param allomas - referencia a kiírandó Allomas objektumra
  // @return A kimeneti stream referenciaja
  friend std::ostream &operator<<(std::ostream &os, const Allomas &allomas);

  // Operátor túlterhelés: Streamből olvasás a Allomas osztályhoz.
  // @param is - referencia a bemeneti streamre
  // @param allomas - referencia a beolvasandó Allomas objektumra
  // @return A bemeneti stream referenciaja
  friend std::istream &operator>>(std::istream &is, Allomas &allomas);

  // Az osztaly destruktora.
  ~Allomas();
};

#endif // ALLOMAS_HPP
