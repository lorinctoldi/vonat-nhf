#include "vonat.h"

Vonat::Vonat() : vonat_azonosito(0), kocsik_szama(0), kocsik(nullptr), jegyek_szama(0), jegyek(nullptr) {}

Vonat::Vonat(const Vonat &other)
    : vonat_azonosito(other.vonat_azonosito), kocsik_szama(other.kocsik_szama), jegyek_szama(other.jegyek_szama),
      utvonal(other.utvonal)
{

    kocsik = new Kocsi[kocsik_szama];
    for (size_t i = 0; i < kocsik_szama; ++i)
    {
        kocsik[i] = other.kocsik[i];
    }

    // Deep copy for jegyek array
    jegyek = new Jegy[jegyek_szama];
    for (size_t i = 0; i < jegyek_szama; ++i)
    {
        jegyek[i] = other.jegyek[i];
    }
}

Vonat& Vonat::operator=(const Vonat &other)
{
    if (this == &other)
        return *this;

    delete[] kocsik;
    delete[] jegyek;

    vonat_azonosito = other.vonat_azonosito;
    kocsik_szama = other.kocsik_szama;
    kocsik = new Kocsi[kocsik_szama];
    for (size_t i = 0; i < kocsik_szama; ++i)
        kocsik[i] = other.kocsik[i];

    jegyek_szama = other.jegyek_szama;
    jegyek = new Jegy[jegyek_szama];
    for (size_t i = 0; i < jegyek_szama; ++i)
        jegyek[i] = other.jegyek[i];

    utvonal = other.utvonal;

    return *this;
}

Vonat::Vonat(size_t azonosito, size_t kocsik_sz, Kocsi *kocsik_ptr, Utvonal utv, size_t jegyek_sz, Jegy *jegyek_ptr)
    : vonat_azonosito(azonosito), kocsik_szama(kocsik_sz), kocsik(new Kocsi[kocsik_sz]), jegyek_szama(jegyek_sz), jegyek(new Jegy[jegyek_sz]), utvonal(utv)
{
  for (size_t i = 0; i < kocsik_sz; ++i)
    {
        kocsik[i] = kocsik_ptr[i];
    }

    for (size_t i = 0; i < jegyek_sz; ++i)
    {
        jegyek[i] = jegyek_ptr[i];
    }
}

void Vonat::addJegy(Jegy &jegy)
{
  Jegy *temp = new Jegy[jegyek_szama + 1];
  for (size_t i = 0; i < jegyek_szama; i++)
    temp[i] = jegyek[i];

  temp[jegyek_szama] = jegy;
  delete[] jegyek;
  jegyek = temp;
  jegyek_szama++;
}

void Vonat::addKocsi(Kocsi &kocsi)
{
  Kocsi *temp = new Kocsi[kocsik_szama + 1];
  for (size_t i = 0; i < kocsik_szama; i++)
    temp[i] = kocsik[i];
  temp[kocsik_szama] = kocsi;
  delete[] kocsik;
  kocsik = temp;
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