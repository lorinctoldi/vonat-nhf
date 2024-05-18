#include "utvonal.h"

Utvonal::Utvonal() : utvonal_azonosito(0), allomasok_szama(0), allomasok(nullptr) {}

Utvonal::Utvonal(const Utvonal &other) : utvonal_azonosito(other.utvonal_azonosito), allomasok_szama(other.allomasok_szama)
{
  allomasok = new Allomas[allomasok_szama];
  for (size_t i = 0; i < allomasok_szama; ++i)
    allomasok[i] = other.allomasok[i];
}

Utvonal& Utvonal::operator=(const Utvonal &other)
{
    if (this == &other)
        return *this;


    delete[] allomasok;


    utvonal_azonosito = other.utvonal_azonosito;
    allomasok_szama = other.allomasok_szama;
    allomasok = new Allomas[allomasok_szama];
    for (size_t i = 0; i < allomasok_szama; ++i)
        allomasok[i] = other.allomasok[i];

    return *this;
}

void Utvonal::addAllomas(Allomas allomas)
{
  Allomas *temp = new Allomas[allomasok_szama + 1];
  for (size_t i = 0; i < allomasok_szama; ++i) {
    temp[i] = allomasok[i];
  }

  temp[allomasok_szama] = allomas;
  allomasok_szama++;

  if (allomasok != nullptr) {
    delete[] allomasok;
  }
  allomasok = temp;
};

void Utvonal::createAllomas(std::string nev,  int indulas_ora, int indulas_perc, int erkezes_ora, int erkezes_perc) {
  Allomas *temp = new Allomas[allomasok_szama + 1];
  for (size_t i = 0; i < allomasok_szama; ++i) {
    temp[i] = allomasok[i];
  }

  temp[allomasok_szama] = Allomas(allomasok_szama, nev, indulas_ora, indulas_perc, erkezes_ora, erkezes_perc);
  allomasok_szama++;

  if (allomasok != nullptr) {
    delete[] allomasok;
  }
  allomasok = temp;
}

void Utvonal::changeAllomas(size_t index, Allomas allomas)
{
  if (index < allomasok_szama)
    allomasok[index] = allomas;
};

void Utvonal::removeAllomas(size_t index)
{
  if (index < allomasok_szama)
  {
    Allomas *temp = new Allomas[allomasok_szama - 1];
    for (size_t i = 0, j = 0; i < allomasok_szama; ++i)
      if (i != index)
        temp[j++] = allomasok[i];

    delete[] allomasok;
    allomasok = temp;
    delete[] temp;
    allomasok_szama--;
  }
}

size_t Utvonal::getAllomasokSzama() const {
  return allomasok_szama;
}

Allomas& Utvonal::getAllomas(size_t i) const {
  return allomasok[i];
}

void Utvonal::kiir(std::ostream &os) const {
  for(size_t i = 0; i < allomasok_szama; ++i) {
    os << "\t" << allomasok[i].getNev() << " : ";
    allomasok[i].getIndulas().kiir(os);
    if(i != allomasok_szama-1) os << "\t|\n";
  }
}

void Utvonal::write(std::ostream &os) const
  {
    os << "===== Utvonal =====\n";
    os << "utvonal azonosito:\n";
    os << utvonal_azonosito << '\n';
    os << "allomasok szama:\n";
    os << allomasok_szama << '\n';
    for (size_t i = 0; i < allomasok_szama; ++i)
    {
      allomasok[i].write(os);
    }
  }

  void Utvonal::read(std::istream &is)
  {
    std::string header;
    std::getline(is, header);
    std::getline(is, header);
    is >> utvonal_azonosito;
    is.ignore();
    std::getline(is, header);
    is >> allomasok_szama;
    is.ignore();
    allomasok = new Allomas[allomasok_szama];
    for (size_t i = 0; i < allomasok_szama; ++i)
    {
      allomasok[i].read(is);
    }
  }

Utvonal::~Utvonal() {
  if(allomasok != nullptr) delete[] allomasok;
}
