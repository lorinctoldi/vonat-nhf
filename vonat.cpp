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
    : vonat_azonosito(azonosito), kocsik_szama(kocsik_sz), kocsik(kocsik_ptr), utvonal(utv), jegyek_szama(jegyek_sz), jegyek(jegyek_ptr) {}

void Vonat::addJegy(size_t helyszam, int ar)
{
  
}

size_t Vonat::getAzonosito() const
{
  return vonat_azonosito;
}

Utvonal Vonat::getUtvonal() const
{
  return utvonal;
}

// Setter for utvonal
void Vonat::setUtvonal(const Utvonal &utv)
{
  utvonal = utv;
}

// Function to add a car
void Vonat::addKocsi(size_t helyek_szama, size_t kocsi_szam)
{
  // Implement car addition logic
}

// Function to add a ticket to a specific car
void Vonat::addTicket(size_t kocsi_index, size_t helyszam)
{
  // Implement ticket addition to a specific car logic
}

// Destructor
Vonat::~Vonat()
{
  delete[] kocsik;
  delete[] jegyek;
}