#include "jegy.hpp"

int Jegy::getAr(double pred = 1)
{
  if (indulo == nullptr || cel == nullptr)
  {
    throw "hianyzo allomas";
    return 0;
  }
  return ((cel->getErkezesOra() * 60 + cel->getErkezesPerc()) - (indulo->getIndulasOra() * 60 + indulo->getIndulasPerc())) * (1 + pred);
}

Jegy::Jegy()
    : jegy_azonosito(0),
      helyszam(0),
      kocsi_szam(0),
      vonat_szam(0),
      indulo(nullptr),
      cel(nullptr),
      ar(0) {}

Jegy::Jegy(const Jegy &other)
    : jegy_azonosito(other.jegy_azonosito),
      helyszam(0),
      kocsi_szam(other.kocsi_szam),
      vonat_szam(other.vonat_szam),
      indulo(other.indulo),
      cel(other.cel),
      ar(other.ar) {}

Jegy::Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel)
    : jegy_azonosito(azonosito),
      helyszam(hely),
      kocsi_szam(kocsi),
      vonat_szam(vonat),
      indulo(indulo),
      cel(cel),
      ar(getAr())
{
}

Jegy::Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel, int pred)
    : jegy_azonosito(azonosito),
      helyszam(hely),
      kocsi_szam(kocsi),
      vonat_szam(vonat),
      indulo(indulo),
      cel(cel),
      ar(getAr(pred))
{
}

Jegy& Jegy::operator=(const Jegy& other)
{
    if (this != &other) 
    {
        jegy_azonosito = other.jegy_azonosito;
        helyszam = other.helyszam;
        kocsi_szam = other.kocsi_szam;
        vonat_szam = other.vonat_szam;
        indulo = other.indulo;
        cel = other.cel;
        ar = other.ar;
    }
    return *this;
}

bool Jegy::operator==(const Jegy &other) const
{
  return (
      jegy_azonosito == other.jegy_azonosito &&
      helyszam == other.helyszam &&
      kocsi_szam == other.kocsi_szam &&
      vonat_szam == other.vonat_szam &&
      indulo == other.indulo &&
      cel == other.cel &&
      ar == other.ar);
}

bool Jegy::operator!=(const Jegy &other) const
{
  return !(*this == other);
};

void Jegy::kiir(std::ostream &os) const
{
  if (indulo == nullptr || cel == nullptr)
  {
    os << "A jegy hibas." << std::endl;
    return;
  }
  os << "Jegy részletei:" << std::endl;
  os << "Jegy azonosító: " << jegy_azonosito << std::endl;
  os << "Helyszám: " << helyszam << std::endl;
  os << "Kocsi száma: " << kocsi_szam << std::endl;
  os << "Vonat száma: " << vonat_szam << std::endl;
  os << "Induló állomás: " << indulo->getNev() << std::endl;
  os << "Célállomás: " << cel->getNev() << std::endl;
  os << "Ár: " << ar << std::endl;
}

KedvezmenyesJegy::KedvezmenyesJegy() : Jegy()
{
  tipus = new char[strlen("kedvezmenyes jegy") + 1];
  strcpy(tipus, "kedvezmenyes jegy");
}

KedvezmenyesJegy::KedvezmenyesJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel, double kedvezmeny = 0.6, char *tipus_nev = nullptr)
    : Jegy(azonosito, hely, kocsi, vonat, indulo, cel, -kedvezmeny), kedvezmeny(kedvezmeny)
{
  tipus = new char[strlen(tipus_nev == nullptr ? "kedvezmenyes jegy" : tipus_nev) + 1];
  strcpy(tipus, tipus_nev == nullptr ? "kedvezmenyes jegy" : tipus_nev);
}

KedvezmenyesJegy::~KedvezmenyesJegy()
{
  if (tipus != nullptr)
    delete[] tipus;
  std::cout << "Kedvezmenyes jegy torolve";
}

void KedvezmenyesJegy::kiir(std::ostream &os) const
{
  if (indulo == nullptr || cel == nullptr)
  {
    os << "A jegy hibas." << std::endl;
    return;
  }
  os << "Kedvezményes jegy részletei:" << std::endl;
  os << "Jegy azonosító: " << jegy_azonosito << std::endl;
  os << "Helyszám: " << helyszam << std::endl;
  os << "Kocsi száma: " << kocsi_szam << std::endl;
  os << "Vonat száma: " << vonat_szam << std::endl;
  os << "Induló állomás: " << indulo->getNev() << std::endl;
  os << "Célállomás: " << cel->getNev() << std::endl;
  os << "Kedvezmény: " << kedvezmeny << std::endl;
  os << "Jegy típusa: " << tipus << std::endl;
}

FelarasJegy::FelarasJegy() : Jegy()
{
  tipus = new char[strlen("kedvezmenyes jegy") + 1];
  strcpy(tipus, "kedvezmenyes jegy");
}

FelarasJegy::FelarasJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel, double felar = 0.6, char *tipus_nev = nullptr)
    : Jegy(azonosito, hely, kocsi, vonat, indulo, cel, felar), felar(felar)
{
  tipus = new char[strlen(tipus_nev == nullptr ? "felaras jegy" : tipus_nev) + 1];
  strcpy(tipus, tipus_nev == nullptr ? "felaras jegy" : tipus_nev);
}

FelarasJegy::~FelarasJegy()
{
  if (tipus != nullptr)
    delete[] tipus;
}

void FelarasJegy::kiir(std::ostream &os) const
{
  if (indulo == nullptr || cel == nullptr)
  {
    os << "A jegy hibas." << std::endl;
    return;
  }
  os << "Feláras jegy részletei:" << std::endl;
  os << "Jegy azonosító: " << jegy_azonosito << std::endl;
  os << "Helyszám: " << helyszam << std::endl;
  os << "Kocsi száma: " << kocsi_szam << std::endl;
  os << "Vonat száma: " << vonat_szam << std::endl;
  os << "Induló állomás: " << indulo->getNev() << std::endl;
  os << "Célállomás: " << cel->getNev() << std::endl;
  os << "Felár: " << felar << std::endl;
  os << "Jegy típusa: " << tipus << std::endl;
}
