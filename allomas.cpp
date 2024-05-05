#include "iostream"

// red-flag -- start
#include <cstring>
// red-flag -- end

#include "allomas.hpp"

Allomas::Allomas()
    : allomas_azonosito(0),
      nev(nullptr),
      erkezes_ora(0),
      erkezes_perc(0),
      indulas_ora(0),
      indulas_perc(0)
{ }

Allomas::Allomas(const Allomas &other)
    : allomas_azonosito(other.allomas_azonosito),
      nev(nullptr),
      erkezes_ora(other.erkezes_ora),
      erkezes_perc(other.erkezes_perc),
      indulas_ora(other.indulas_ora),
      indulas_perc(other.indulas_perc)
{
  if (other.nev != nullptr)
  {
    nev = new char[strlen(other.nev) + 1];
    strcpy(nev, other.nev);
  }
}

Allomas::Allomas(size_t azonosito, char *nev, int indulas_ora, int indulas_perc, int erkezes_ora, int erkezes_perc)
    : allomas_azonosito(azonosito),
      nev(nullptr),
      indulas_ora(indulas_ora),
      indulas_perc(indulas_perc),
      erkezes_ora(erkezes_ora),
      erkezes_perc(erkezes_perc)
{
  if (nev != nullptr)
  {
    this->nev = new char[strlen(nev) + 1];
    strcpy(this->nev, nev);
  }
}

void Allomas::changeErkezes(int ora, int perc)
{
  // unnecessary -- start
  std::cout
      << "Erkezes idopontja megvaltoztatva "
      << erkezes_ora
      << ":"
      << erkezes_perc
      << "-rol, "
      << ora
      << ":"
      << perc
      << "-ra."
      << std::endl;
  // unnecessary -- end

  erkezes_ora = ora;
  erkezes_perc = perc;
}

void Allomas::changeIndulas(int ora, int perc)
{
  // unnecessary -- start
  std::cout
      << "Indulas idopontja megvaltoztatva "
      << indulas_ora
      << ":"
      << indulas_perc
      << "-rol, "
      << ora
      << ":"
      << perc
      << "-ra."
      << std::endl;
  // unnecessary -- end

  indulas_ora = ora;
  indulas_perc = perc;
}

void Allomas::changeNev(char *other)
{
  if (nev != nullptr)
    delete[] nev;
  char *temp = new char[strlen(other) + 1];
  strcpy(nev, temp);
}

int Allomas::getIndulasOra() {
  return indulas_ora;
}

int Allomas::getIndulasPerc() {
  return indulas_perc;
}

int Allomas::getErkezesOra() {
  return erkezes_ora;
}

int Allomas::getErkezesPerc() {
  return erkezes_perc;
}


Allomas::~Allomas(){
  if (nev != nullptr)
    delete[] nev;
  std::cout << "Allomas torlve" << std::endl;
};

// done
// red-flag : cstring
