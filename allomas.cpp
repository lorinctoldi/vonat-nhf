// unnecessary -- start
#include "iostream"

using namespace std;
// unnecessary -- end

#include "allomas.hpp"

Allomas::Allomas(const Allomas &other)
    : allomas_azonosito(other.allomas_azonosito),
      nev(other.nev),
      erkezes_ora(other.erkezes_ora),
      erkezes_perc(other.erkezes_perc),
      indulas_ora(other.indulas_ora),
      indulas_perc(other.indulas_perc)
{ /* void */ }

Allomas::Allomas(size_t azonosito, const char *nev, int indulas_ora, int indulas_perc, int erkezes_ora, int erkezes_perc)
    : allomas_azonosito(azonosito), 
      nev(nev),
      indulas_ora(indulas_ora), 
      indulas_perc(indulas_perc), 
      erkezes_ora(erkezes_ora), 
      erkezes_perc(erkezes_perc)
{ /* void */ }

void Allomas::changeErkezes(int ora, int perc)
{
  // unnecessary -- start
  cout
      << "Erkezes megvaltoztatva "
      << erkezes_ora
      << ":"
      << erkezes_perc
      << "-rol, "
      << ora
      << ":"
      << perc
      << "-ra."
      << endl;
  // unnecessary -- end

  erkezes_ora = ora;
  erkezes_perc = perc;
}

void Allomas::changeIndulas(int ora, int perc)
{
  // unnecessary -- start
  cout
      << "Erkezes megvaltoztatva "
      << erkezes_ora
      << ":"
      << erkezes_perc
      << "-rol, "
      << ora
      << ":"
      << perc
      << "-ra."
      << endl;
  // unnecessary -- end
  
  indulas_ora = ora;
  indulas_perc = perc;
}

void Allomas::changeNev(const char *other) {
  delete nev;

}
