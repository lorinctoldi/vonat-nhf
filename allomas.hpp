#ifndef ALLOMAS_HPP
#define ALLOMAS_HPP

#include <cstddef>

class Allomas
{
  size_t allomas_azonosito;
  char *nev;
  int indulas_ora;
  int indulas_perc;
  int erkezes_ora;
  int erkezes_perc;
public:
  Allomas();
  Allomas(const Allomas &other);
  Allomas(size_t azonosito, char* nev, int indulas_ora, int indulas_perc,  int erkezes_ora, int erkezes_perc);
  void changeErkezes(int ora, int perc);
  void changeIndulas(int ora, int perc);
  void changeNev(char *other);
  int getIndulasOra();
  int getIndulasPerc();  
  int getErkezesOra();
  int getErkezesPerc();  
  ~Allomas();
};

#endif // ALLOMAS_HPP

// done
// red-flag : cstring
