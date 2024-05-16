#include "jegy.h"

int Jegy::getAr(double pred = 1)
{
  return ((cel_ido.getOra() * 60 + cel_ido.getPerc()) - (indulo_ido.getOra() * 60 + indulo_ido.getPerc())) * (1 + pred);
}

Jegy::Jegy()
    : jegy_azonosito(0), helyszam(0), kocsi_szam(0), vonat_szam(0),
      indulo_nev(""), indulo_ido(), cel_nev(""), cel_ido(), ar(0) {}

Jegy::Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, const std::string &indulo, Ido indulo_idopont,
           const std::string &cel, Ido cel_idopont)
    : jegy_azonosito(azonosito), helyszam(hely), kocsi_szam(kocsi), vonat_szam(vonat),
      indulo_nev(indulo), indulo_ido(indulo_idopont), cel_nev(cel), cel_ido(cel_idopont), ar(getAr()) {}

Jegy::Jegy(const Jegy &other)
    : jegy_azonosito(other.jegy_azonosito), helyszam(other.helyszam), kocsi_szam(other.kocsi_szam), vonat_szam(other.vonat_szam),
      indulo_nev(other.indulo_nev), indulo_ido(other.indulo_ido), cel_nev(other.cel_nev), cel_ido(other.cel_ido), ar(other.ar) {}

Jegy &Jegy::operator=(const Jegy &other)
{
  if (this != &other)
  {
    jegy_azonosito = other.jegy_azonosito;
    helyszam = other.helyszam;
    kocsi_szam = other.kocsi_szam;
    vonat_szam = other.vonat_szam;
    indulo_nev = other.indulo_nev;
    indulo_ido = other.indulo_ido;
    cel_nev = other.cel_nev;
    cel_ido = other.cel_ido;
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
      indulo_nev == other.indulo_nev &&
      indulo_ido == other.indulo_ido &&
      cel_nev == other.cel_nev &&
      cel_ido == other.cel_ido &&
      ar == other.ar);
}

bool Jegy::operator!=(const Jegy &other) const
{
  return !(*this == other);
};

void Jegy::kiir(std::ostream &os) const
{
}

// kedvezmenyes jegy

KedvezmenyesJegy::KedvezmenyesJegy() : Jegy()
{
  tipus = "kedvezmenyes jegy";
}

KedvezmenyesJegy::KedvezmenyesJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, const std::string &indulo, Ido indulo_idopont,
                                   const std::string &cel, Ido cel_idopont, double kedvezmeny = 0.6, std::string tipus = "kedvezmenyes jegy")
    : Jegy(azonosito, hely, kocsi, vonat, indulo, indulo_idopont, cel, cel_idopont), tipus(tipus), kedvezmeny(-kedvezmeny)
{
}

KedvezmenyesJegy::~KedvezmenyesJegy()
{
  std::cout << tipus << "torolve";
}

void KedvezmenyesJegy::kiir(std::ostream &os) const
{
}

// felaras jegy

FelarasJegy::FelarasJegy() : Jegy()
{
  tipus = "felaras jegy";
}

FelarasJegy::FelarasJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, const std::string &indulo, Ido indulo_idopont,
                         const std::string &cel, Ido cel_idopont, double felar = 0.6, std::string tipus = "felaras jegy")
    : Jegy(azonosito, hely, kocsi, vonat, indulo, indulo_idopont, cel, cel_idopont), tipus(tipus), felar(felar)
{
}

FelarasJegy::~FelarasJegy()
{
  std::cout << tipus << "torolve";
}

void FelarasJegy::kiir(std::ostream &os) const
{
}

// write
void Jegy::write(std::ostream &os) const {
    os << "JEGY\n"; // Type identifier
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

void Jegy::read(std::istream &is) {
    std::string header;
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
    std::getline(is, indulo_nev);
    indulo_ido.read(is);
    std::getline(is, header);
    std::getline(is, cel_nev);
    cel_ido.read(is);
    std::getline(is, header);
    is >> ar;
    is.ignore(3, '\n'); // Ignore " Ft" and newline
    is.ignore(); // Ignore newline character
}

// KedvezmenyesJegy class
void KedvezmenyesJegy::write(std::ostream &os) const {
    os << "KEDVEZMENYES\n"; // Type identifier
    Jegy::write(os);
    os << tipus << "\n" << kedvezmeny << "\n";
}

void KedvezmenyesJegy::read(std::istream &is) {
    std::string header;
    Jegy::read(is);
    is.ignore(); // Ignore newline after Jegy read
    std::getline(is, tipus);
    is >> kedvezmeny;
    is.ignore(); // Ignore newline after kedvezmeny
}

// FelarasJegy class
void FelarasJegy::write(std::ostream &os) const {
    os << "FELARAS\n"; // Type identifier
    Jegy::write(os);
    os << tipus << "\n" << felar << "\n";
}

void FelarasJegy::read(std::istream &is) {
    std::string header;
    Jegy::read(is);
    is.ignore(); // Ignore newline after Jegy read
    std::getline(is, tipus);
    is >> felar;
    is.ignore(); // Ignore newline after felar
}