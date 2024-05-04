#ifndef ALLOMAS_HPP
#define ALLOMAS_HPP

class Allomas
{
  size_t allomas_azonosito;
  char *nev;
  int erkezes_ora;
  int erkezes_perc;
  int indulas_ora;
  int indulas_perc;

public:
  Allomas();
  Allomas(const Allomas &other);
  Allomas(const char *nev, int erkezes_ora, int erkezes_perc, int indulas_ora, int indulas_perc);
  Utvonal getUtvonal() const;
  void changeErkezes(int, int);
  void changeIndulas(int, int);
  void changeNev(const char *other);
  ~Allomas();
}

#endif // ALLOMAS_HPP
