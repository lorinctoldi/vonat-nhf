#include "menetrend.hpp"

Menetrend::Menetrend(Vonat v) {
  vonatok_szama = 1;
  vonatok = new Vonat[vonatok_szama];
  vonatok[0] = v;
};

void Menetrend::addVonat(Vonat v)
{
  vonatok_szama += 1;

  Vonat *temp_vonatok = new Vonat[vonatok_szama];

  for (size_t i = 0; i < vonatok_szama - 1; ++i)
    temp_vonatok[i] = vonatok[i];

  temp_vonatok[vonatok_szama - 1] = v;

  delete[] vonatok;
  vonatok = temp_vonatok;
}

void Menetrend::changeVonat(Vonat v, size_t index)
{
  vonatok[index] = v;
}

Vonat Menetrend::getVonat(size_t index = 0)
{
  if (index >= vonatok_szama)
    throw std::out_of_range("Index out of bounds");
  return vonatok[index];
}

void Menetrend::kiir() {
  // menetrend kiirasa a vonatok kiiro fuggvenyet / parametereit felhasznalva
};

Menetrend::~Menetrend()
{
  delete[] vonatok;
}
