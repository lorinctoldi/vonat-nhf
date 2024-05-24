#include "allomas.h"

#include <cstring>
#include <cstddef>
#include <iostream>

Allomas::Allomas()
    : allomas_azonosito(0),
      nev(nullptr),
      indulas(0, 0),
      erkezes(0, 0)
{
}

Allomas::Allomas(const Allomas &other)
    : allomas_azonosito(other.allomas_azonosito),
      indulas(other.indulas),
      erkezes(other.erkezes)
{
  if (other.nev != nullptr)
  {
    nev = new char[strlen(other.nev) + 1];
    std::strcpy(nev, other.nev);
  }
  else
  {
    nev = nullptr;
  }
}

Allomas &Allomas::operator=(const Allomas &other)
{
  if (this != &other)
  {
    allomas_azonosito = other.allomas_azonosito;
    indulas = other.indulas;
    erkezes = other.erkezes;

    if (nev != nullptr)
    {
      delete[] nev;
    }

    if (other.nev != nullptr)
    {
      nev = new char[strlen(other.nev) + 1];
      std::strcpy(nev, other.nev);
    }
    else
    {
      nev = nullptr;
    }
  }
  return *this;
}

Allomas::Allomas(int azonosito, const char *nev, int erkezes_ora, int erkezes_perc, int indulas_ora, int indulas_perc)
    : allomas_azonosito(azonosito),
      indulas(indulas_ora, indulas_perc),
      erkezes(erkezes_ora, erkezes_perc)
{
  if (indulas_ora < erkezes_ora || (erkezes_ora == indulas_ora && indulas_perc < erkezes_perc))
    throw "Az indulas nem tortenhet elobb mint az erkezes!";

  this->nev = new char[strlen(nev) + 1];
  std::strcpy(this->nev, nev);
}

void Allomas::changeErkezes(int ora, int perc)
{
  int indulas_ora = indulas.getOra(), indulas_perc = indulas.getPerc();
  if (indulas_ora < ora || (ora == indulas_ora && indulas_perc < perc))
    throw "Az indulas nem tortenhet elobb mint az erkezes!";
  erkezes.setIdo(ora, perc);
}

void Allomas::changeIndulas(int ora, int perc)
{
  int erkezes_ora = erkezes.getOra(), erkezes_perc = erkezes.getPerc();
  if (erkezes_ora > ora || (ora == erkezes_ora && erkezes_perc > perc))
    throw "Az erkezes nem tortenhet kesobb mint az indulas!";
  indulas.setIdo(ora, perc);
}

void Allomas::changeNev(const char *other)
{
  delete[] nev;
  nev = new char[strlen(other) + 1];
  std::strcpy(nev, other);
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

const char *Allomas::getNev() const
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

  char buffer[256];
  is.getline(buffer, 256);

  delete[] nev;
  nev = new char[strlen(buffer) + 1];
  std::strcpy(nev, buffer);

  std::getline(is, header);
  erkezes.read(is);
  std::getline(is, header);
  indulas.read(is);
}

Allomas::~Allomas()
{
  delete[] nev;
};
