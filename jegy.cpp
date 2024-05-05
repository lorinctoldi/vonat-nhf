#include "jegy.hpp"

// jegy -- start
int Jegy::getAr()
{
  if (indulo == nullptr || cel == nullptr)
  {
    throw "hianyzo allomas";
    return 0;
  }
  return ((cel->getErkezesOra() * 60 + cel->getErkezesPerc()) - (indulo->getIndulasOra() * 60 + indulo->getIndulasPerc())) * (kedvezmeny ? kedvezmeny : 1);
}

Jegy::Jegy(const Jegy &other) : jegy_azonosito(other.jegy_azonosito), helyszam(0), kocsi_szam(other.kocsi_szam), vonat_szam(other.vonat_szam), indulo(other.indulo), cel(other.cel), kedvezmeny(other.kedvezmeny), ar(getAr()) {}

Jegy::Jegy() : jegy_azonosito(0), helyszam(0), kocsi_szam(0), vonat_szam(0), indulo(nullptr), cel(nullptr), kedvezmeny(1), ar(getAr()) {}

Jegy::Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel)
    : jegy_azonosito(azonosito), helyszam(hely), kocsi_szam(kocsi), vonat_szam(vonat), indulo(indulo), cel(cel), ar(getAr()) {}

bool Jegy::operator==(const Jegy &other) const {
  return (
    jegy_azonosito == other.jegy_azonosito &&
    helyszam == other.helyszam &&
    kocsi_szam == other.kocsi_szam &&
    vonat_szam == other.vonat_szam &&
    indulo == other.indulo &&
    cel == other.cel &&
    kedvezmeny == other.kedvezmeny &&
    ar == other.ar
  );
}

bool Jegy::operator!=(const Jegy &other) const {
  return !(*this == other);
};
// jegy -- end

// elso osztaly -- start
ElsoOsztalyJegy::ElsoOsztalyJegy() : Jegy(), tipus(new char[strlen("elso osztaly") + 1])
{
  strcpy(tipus, "elso osztaly");
}

ElsoOsztalyJegy::ElsoOsztalyJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel, double kedvezmeny)
    : Jegy(azonosito, hely, kocsi, vonat, indulo, cel), tipus(new char[strlen("elso osztaly") + 1])
{
  strcpy(tipus, "elso osztaly");
}

ElsoOsztalyJegy::~ElsoOsztalyJegy()
{
  if (tipus != nullptr)
    delete[] tipus;
}

void ElsoOsztalyJegy::kiir() const
{
  // Implement the kiir function for ElsoOsztalyJegy
}
// elso osztaly -- end
