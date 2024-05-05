#include "vonat.hpp"

Vonat::Vonat() : vonat_azonosito(0), kocsik_szama(0), kocsik(nullptr), jegyek_szama(0), jegyek(nullptr) {}

Vonat::Vonat(const Vonat &other)
  : vonat_azonosito(other.vonat_azonosito),
    kocsik_szama(other.kocsik_szama),
    kocsik(new Kocsi[other.kocsik_szama]),
    jegyek_szama(other.jegyek_szama),
    jegyek(new Jegy[other.jegyek_szama]),
    utvonal(other.utvonal)
{
  for (size_t i = 0; i < kocsik_szama; ++i)
    kocsik[i] = other.kocsik[i];
  for (size_t i = 0; i < jegyek_szama; ++i)
    jegyek[i] = other.jegyek[i];
}

Vonat::Vonat(size_t azonosito, size_t kocsik_sz, Kocsi *kocsik_ptr, Utvonal utv, size_t jegyek_sz, Jegy *jegyek_ptr)
    : vonat_azonosito(azonosito), kocsik_szama(kocsik_sz), kocsik(kocsik_ptr), jegyek_szama(jegyek_sz), jegyek(jegyek_ptr),  utvonal(utv) {}

void Vonat::addJegy(Jegy &jegy)
{
  Jegy *temp = new Jegy[jegyek_szama + 1];
  for (int i = 0; i < jegyek_szama; i++)
    temp[i] = jegyek[i];

  temp[jegyek_szama] = jegy;
  jegyek = temp;
  delete[] temp;
  jegyek_szama++;
}

void Vonat::addKocsi(Kocsi &kocsi)
{
  Kocsi *temp = new Kocsi[kocsik_szama + 1];
  for (int i = 0; i < kocsik_szama; i++)
    temp[i] = kocsik[i];

  temp[kocsik_szama] = kocsi;
  kocsik = temp;
  delete[] temp;
  kocsik_szama++;
}

size_t Vonat::getAzonosito() const
{
  return vonat_azonosito;
}

Utvonal Vonat::getUtvonal() const
{
  return utvonal;
}

void Vonat::setUtvonal(const Utvonal &utv)
{
  utvonal = utv;
}

Vonat::~Vonat()
{
  if (kocsik_szama > 0)
    delete[] kocsik;
  if (jegyek_szama > 0)
    delete[] jegyek;
}