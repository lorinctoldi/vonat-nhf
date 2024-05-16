#include "allomas.h"

#include <cstring>
#include <cstddef>
#include <iostream>

Allomas::Allomas()
    : allomas_azonosito(0),
     nev(""),
      indulas(0, 0),
      erkezes(0, 0)
{
}

Allomas::Allomas(const Allomas &other)
    : allomas_azonosito(other.allomas_azonosito),
      nev(other.nev),
      indulas(other.indulas),
      erkezes(other.erkezes)
{
}

Allomas &Allomas::operator=(const Allomas &other)
{
  if (this != &other)
  {
    allomas_azonosito = other.allomas_azonosito;
    nev = other.nev;
    indulas = other.indulas;
    erkezes = other.erkezes;
  }
  return *this;
}

Allomas::Allomas(size_t azonosito, const std::string &nev, int indulas_ora, int indulas_perc, int erkezes_ora, int erkezes_perc)
    : allomas_azonosito(azonosito),
      nev(nev),
      indulas(indulas_ora, indulas_perc),
      erkezes(erkezes_ora, erkezes_perc)
{
}

void Allomas::changeErkezes(int ora, int perc)
{
  erkezes.setIdo(ora, perc);
}

void Allomas::changeIndulas(int ora, int perc)
{
  indulas.setIdo(ora, perc);
}

void Allomas::changeNev(const std::string &other)
{
  nev = other;
}

int Allomas::getIndulasOra()
{
  return indulas.getOra();
}

int Allomas::getIndulasPerc()
{
  return indulas.getPerc();
}

int Allomas::getErkezesOra()
{
  return erkezes.getOra();
}

int Allomas::getErkezesPerc()
{
  return erkezes.getPerc();
}

std::string &Allomas::getNev()
{
  return nev;
}

Allomas::~Allomas()
{
};
