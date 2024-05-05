#include "utvonal.hpp"

Utvonal::Utvonal() : utvonal_azonosito(0), allomasok_szama(0), allomasok(nullptr) {}

Utvonal::Utvonal(const Utvonal &other) : utvonal_azonosito(other.utvonal_azonosito), allomasok_szama(other.allomasok_szama)
{
  allomasok = new Allomas[allomasok_szama];
  for (size_t i = 0; i < allomasok_szama; ++i)
    allomasok[i] = other.allomasok[i];
}

void Utvonal::addAllomas(Allomas allomas)
{
  Allomas *temp = new Allomas[allomasok_szama + 1];
  for (int i = 0; i < allomasok_szama; ++i)
    temp[i] = allomasok[i];
  temp[allomasok_szama] = allomas;
  allomasok_szama++;
  if (allomasok != nullptr)
    delete[] allomasok;
  delete[] temp;
  allomasok = temp;
};

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

Utvonal::~Utvonal() {
  if(allomasok != nullptr) delete[] allomasok;
}
