#include "jegy.h"

#include <iostream>

int Jegy::getAr(double pred = 1)
{
  return ((cel_ido.getOra() * 60 + cel_ido.getPerc()) - (indulo_ido.getOra() * 60 + indulo_ido.getPerc())) * (1.0 + pred);
}

Jegy::Jegy()
    : jegy_azonosito(0), helyszam(0), kocsi_szam(0), vonat_szam(0),
      indulo_nev(nullptr), indulo_ido(), cel_nev(nullptr), cel_ido(), ar(0) {}

Jegy::Jegy(int azonosito, int hely, int kocsi, int vonat, const char * indulo, Ido indulo_idopont,
           const char * cel, Ido cel_idopont)
    : jegy_azonosito(azonosito), helyszam(hely), kocsi_szam(kocsi), vonat_szam(vonat),
      indulo_nev(nullptr), indulo_ido(indulo_idopont), cel_nev(nullptr), cel_ido(cel_idopont), ar(getAr())
{
  indulo_nev = new char[strlen(indulo) + 1];
  std::strcpy(indulo_nev, indulo);
  cel_nev = new char[strlen(cel) + 1];
  std::strcpy(cel_nev, cel);
}

Jegy::Jegy(int azonosito, int hely, int kocsi, int vonat, const char * indulo, Ido indulo_idopont,
           const char * cel, Ido cel_idopont, double pred)
    : jegy_azonosito(azonosito), helyszam(hely), kocsi_szam(kocsi), vonat_szam(vonat),
      indulo_nev(nullptr), indulo_ido(indulo_idopont), cel_nev(nullptr), cel_ido(cel_idopont), ar(getAr(pred))
{
  indulo_nev = new char[strlen(indulo) + 1];
  std::strcpy(indulo_nev, indulo);
  cel_nev = new char[strlen(cel) + 1];
  std::strcpy(cel_nev, cel);
}

Jegy::Jegy(const Jegy &other)
    : jegy_azonosito(other.jegy_azonosito), helyszam(other.helyszam), kocsi_szam(other.kocsi_szam), vonat_szam(other.vonat_szam),
      indulo_nev(nullptr), indulo_ido(other.indulo_ido), cel_nev(nullptr), cel_ido(other.cel_ido), ar(other.ar)
{
  indulo_nev = new char[strlen(other.indulo_nev) + 1];
  std::strcpy(indulo_nev, other.indulo_nev);
  cel_nev = new char[strlen(other.cel_nev) + 1];
  std::strcpy(cel_nev, other.cel_nev);
}

Jegy &Jegy::operator=(const Jegy &other)
{
  if (this != &other)
  {
    jegy_azonosito = other.jegy_azonosito;
    helyszam = other.helyszam;
    kocsi_szam = other.kocsi_szam;
    vonat_szam = other.vonat_szam;
    indulo_ido = other.indulo_ido;
    cel_ido = other.cel_ido;
    ar = other.ar;

    delete[] indulo_nev;
    indulo_nev = new char[strlen(other.indulo_nev) + 1];
    strcpy(indulo_nev, other.indulo_nev);
    
    delete[] cel_nev;
    cel_nev = new char[strlen(other.cel_nev) + 1];
    strcpy(cel_nev, other.cel_nev); 
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
      strcmp(indulo_nev, other.indulo_nev) == 0 &&
      indulo_ido == other.indulo_ido &&
      strcmp(cel_nev, other.cel_nev) == 0 &&
      cel_ido == other.cel_ido &&
      ar == other.ar);
}

bool Jegy::operator!=(const Jegy &other) const
{
  return !(*this == other);
};

void Jegy::kiir(std::ostream &os) const
{
  os << "===== JEGY =====\n"
     << "azonosito: " << jegy_azonosito << "\n"
     << "vonat szama: " << vonat_szam + 1 << "\n"
     << "kocsi szam: " << kocsi_szam + 1 << "\n"
     << "hely szam: " << helyszam << "\n"
     << "----------------\n"
     << indulo_nev << " - " << cel_nev << "\n"
     << "indulas: ";
  indulo_ido.kiir(os);
  os << "erkezes: ";
  cel_ido.kiir(os);
  os << "----------------\n"
     << "ar: " << ar << "Ft\n";
}

void Jegy::write(std::ostream &os) const
{
  os << "JEGY\n";
  os << "===== Jegy =====\n"
     << "jegy azonosito:\n"
     << jegy_azonosito << "\n"
     << "helyszam:\n"
     << helyszam << "\n"
     << "kocsiszam:\n"
     << kocsi_szam << "\n"
     << "vonatszam:\n"
     << vonat_szam << "\n"
     << "indulasi allomas:\n"
     << indulo_nev << "\n";
  indulo_ido.write(os);
  os << "cel allomas:\n"
     << cel_nev << "\n";
  cel_ido.write(os);
  os << "ar\n"
     << ar << " Ft\n";
}

void Jegy::read(std::istream &is)
{
  char buffer[256];
  std::string header;
  std::getline(is, header);
  if (header == "JEGY")
    std::getline(is, header);
  std::getline(is, header);
  is >> jegy_azonosito;
  is.ignore();
  std::getline(is, header);
  is >> helyszam;
  is.ignore();
  std::getline(is, header);
  is >> kocsi_szam;
  is.ignore();
  std::getline(is, header);
  is >> vonat_szam;
  is.ignore();
  std::getline(is, header);

  is.getline(buffer, 256);
  indulo_nev = new char[strlen(buffer) + 1];
  std::strcpy(indulo_nev, buffer);

  indulo_ido.read(is);
  std::getline(is, header);

  is.getline(buffer, 256);
  cel_nev = new char[strlen(buffer) + 1];
  std::strcpy(cel_nev, buffer);

  cel_ido.read(is);
  std::getline(is, header);
  is >> ar;
  std::getline(is, header);
}

Jegy *Jegy::clone() const
{
  return new Jegy(*this);
}

Jegy::~Jegy()
{
  delete[] indulo_nev;
  delete[] cel_nev;
};

// KEDVEZMENYES JEGY

KedvezmenyesJegy::KedvezmenyesJegy() : Jegy()
{
}

KedvezmenyesJegy::KedvezmenyesJegy(int azonosito, int hely, int kocsi, int vonat, const char * indulo, Ido indulo_idopont,
                                   const char * cel, Ido cel_idopont, double kedvezmeny = -0.6, const char *tipus = "kedvezmenyes jegy")
    : Jegy(azonosito, hely, kocsi, vonat, indulo, indulo_idopont, cel, cel_idopont, kedvezmeny), kedvezmeny(kedvezmeny)
{
  this->tipus = new char[strlen(tipus) + 1];
  std::strcpy(this->tipus, tipus);
}

KedvezmenyesJegy::KedvezmenyesJegy(const KedvezmenyesJegy &other) : Jegy(other), kedvezmeny(other.kedvezmeny)
{
  tipus = new char[strlen(other.tipus) + 1];
  std::strcpy(tipus, other.tipus);
}

KedvezmenyesJegy &KedvezmenyesJegy::operator=(const KedvezmenyesJegy &other)
{
  if (this != &other)
  {
    Jegy::operator=(other);

    delete[] tipus;
    tipus = new char[strlen(other.tipus) + 1];
    std::strcpy(tipus, other.tipus);

    kedvezmeny = other.kedvezmeny;
  }
  return *this;
}

void KedvezmenyesJegy::kiir(std::ostream &os) const
{
  Jegy::kiir(os);
  os << "tipus: " << tipus << "\n"
     << "kedvezmeny merteke: " << (kedvezmeny * 100) << "%\n";
}

void KedvezmenyesJegy::write(std::ostream &os) const
{
  os << "KEDVEZMENYES\n";
  Jegy::write(os);
  os << tipus << "\n"
     << kedvezmeny << "\n";
}

void KedvezmenyesJegy::read(std::istream &is)
{
  char buffer[256];
  std::string header;
  std::getline(is, header);
  if (header == "KEDVEZMENYES")
    std::getline(is, header);
  Jegy::read(is);

  is.getline(buffer, 256);
  tipus = new char[strlen(buffer) + 1];
  std::strcpy(tipus, buffer);

  is >> kedvezmeny;
  is.ignore();
}

Jegy *KedvezmenyesJegy::clone() const
{
  return new KedvezmenyesJegy(*this);
}

KedvezmenyesJegy::~KedvezmenyesJegy()
{
  delete[] tipus;
}

// FELARAS JEGY

FelarasJegy::FelarasJegy() : Jegy()
{
}

FelarasJegy::FelarasJegy(int azonosito, int hely, int kocsi, int vonat, const char * indulo, Ido indulo_idopont,
                         const char * cel, Ido cel_idopont, double felar = 0.6, const char *tipus = "felaras jegy")
    : Jegy(azonosito, hely, kocsi, vonat, indulo, indulo_idopont, cel, cel_idopont, felar), felar(felar)
{
  this->tipus = new char[strlen(tipus) + 1];
  std::strcpy(this->tipus, tipus);
}

FelarasJegy::FelarasJegy(const FelarasJegy &other) : Jegy(other), felar(other.felar)
{
  tipus = new char[strlen(other.tipus) + 1];
  std::strcpy(tipus, other.tipus);
}

FelarasJegy &FelarasJegy::operator=(const FelarasJegy &other)
{
  if (this != &other)
  {
    Jegy::operator=(other);

    delete[] tipus;
    tipus = new char[strlen(other.tipus) + 1];
    std::strcpy(tipus, other.tipus);

    felar = other.felar;
  }
  return *this;
}

void FelarasJegy::kiir(std::ostream &os) const
{
  Jegy::kiir(os);
  os << "tipus: " << tipus << "\n"
     << "felar merteke: " << (felar * 100) << "%\n";
}

void FelarasJegy::write(std::ostream &os) const
{
  os << "FELARAS\n";
  Jegy::write(os);
  os << tipus << "\n"
     << felar << "\n";
}

void FelarasJegy::read(std::istream &is)
{
  char buffer[256];
  std::string header;
  std::getline(is, header);
  if (header == "FELARAS")
    std::getline(is, header);
  Jegy::read(is);

  is.getline(buffer, 256);
  tipus = new char[strlen(buffer) + 1];
  std::strcpy(tipus, buffer);

  is >> felar;
  is.ignore();
}

Jegy *FelarasJegy::clone() const
{
  return new FelarasJegy(*this);
}

FelarasJegy::~FelarasJegy()
{
  delete[] tipus;
}
