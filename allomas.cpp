#include "allomas.h"

#include <cstring>
#include <cstddef>
#include <iostream>

Allomas::Allomas()
    : allomas_azonosito(0),
      nev(""),
      indulas(0, 0),
      erkezes(0, 0)
{ }

Allomas::Allomas(const Allomas &other)
    : allomas_azonosito(other.allomas_azonosito),
      nev(other.nev),
      indulas(other.indulas),
      erkezes(other.erkezes)
{ }

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

Allomas::Allomas(size_t azonosito, const std::string &nev, int erkezes_ora, int erkezes_perc, int indulas_ora, int indulas_perc)
    : allomas_azonosito(azonosito),
      nev(nev),
      indulas(indulas_ora, indulas_perc),
      erkezes(erkezes_ora, erkezes_perc)
{
  if(indulas_ora < erkezes_ora || (erkezes_ora == indulas_ora && indulas_perc < erkezes_perc)) throw "Az indulas nem tortenhet elobb mint az erkezes!";
}

void Allomas::changeErkezes(int ora, int perc)
{
  int indulas_ora = indulas.getOra(), indulas_perc = indulas.getPerc();
  if(indulas_ora < ora || (ora == indulas_ora && indulas_perc < perc)) throw "Az indulas nem tortenhet elobb mint az erkezes!";
  erkezes.setIdo(ora, perc);
}

void Allomas::changeIndulas(int ora, int perc)
{
  int erkezes_ora = erkezes.getOra(), erkezes_perc = erkezes.getPerc();
  if(erkezes_ora > ora || (ora == erkezes_ora && erkezes_perc > perc)) throw "Az erkezes nem tortenhet kesobb mint az indulas!";
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

Ido &Allomas::getIndulas()
{
  return indulas;
}

Ido &Allomas::getErkezes()
{
  return erkezes;
}

void Allomas::write(std::ostream &os) const
{
  os << "===== Allomas =====\n";
  os << "allomas azonosito:\n";
  os << allomas_azonosito << '\n';
  os << "nev:\n";
  os << nev << '\n';
  os << "erkezes:\n";
  erkezes.write(os);
  os << "indulas:\n";
  indulas.write(os);
}

void Allomas::read(std::istream &is)
{
  std::string header;
  std::getline(is, header);
  std::getline(is, header);
  is >> allomas_azonosito;
  is.ignore();
  std::getline(is, header);
  std::getline(is, nev);
  std::getline(is, header);
  erkezes.read(is);
  std::getline(is, header);
  indulas.read(is);
}

Allomas::~Allomas(){};
