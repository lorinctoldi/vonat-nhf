#ifndef ALLOMAS_HPP
#define ALLOMAS_HPP

#include <cstddef>
#include "utvonal.hpp"

class Allomas
{
  size_t allomas_azonosito;
  const char *nev;
  int indulas_ora;
  int indulas_perc;
  int erkezes_ora;
  int erkezes_perc;
public:
  Allomas();
  Allomas(const Allomas &other);
  Allomas(size_t azonosito, const char* nev, int indulas_ora, int indulas_perc,  int erkezes_ora, int erkezes_perc);
  void changeErkezes(int ora, int perc);
  void changeIndulas(int ora, int perc);
  void changeNev(const char *other);
  ~Allomas() {};
};

#endif // ALLOMAS_HPP
