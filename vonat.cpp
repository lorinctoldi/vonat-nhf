#include "vonat.h"

Vonat::Vonat() : vonat_azonosito(0), kocsik_szama(0), kocsik(nullptr), jegyek(nullptr), jegyek_szama(0) {}

Vonat::Vonat(const Vonat &other)
    : vonat_azonosito(other.vonat_azonosito), kocsik_szama(other.kocsik_szama), jegyek_szama(other.jegyek_szama),
      utvonal(other.utvonal)
{

  // Deep copy kocsik array
  kocsik = new Kocsi[kocsik_szama];
  for (size_t i = 0; i < kocsik_szama; ++i)
  {
    kocsik[i] = other.kocsik[i];
  }

  // Deep copy jegyek array
  jegyek = new Jegy *[jegyek_szama];
  for (size_t i = 0; i < jegyek_szama; ++i)
  {
    if (dynamic_cast<KedvezmenyesJegy *>(other.jegyek[i]))
    {
      jegyek[i] = new KedvezmenyesJegy(*dynamic_cast<KedvezmenyesJegy *>(other.jegyek[i]));
    }
    else if (dynamic_cast<FelarasJegy *>(other.jegyek[i]))
    {
      jegyek[i] = new FelarasJegy(*dynamic_cast<FelarasJegy *>(other.jegyek[i]));
    }
    else
    {
      jegyek[i] = new Jegy(*other.jegyek[i]);
    }
  }
}

Vonat &Vonat::operator=(const Vonat &other)
{
  if (this == &other) // self-assignment check
    return *this;

  // Copy basic members
  vonat_azonosito = other.vonat_azonosito;
  kocsik_szama = other.kocsik_szama;
  jegyek_szama = other.jegyek_szama;
  utvonal = other.utvonal;

  // Deep copy kocsik array
  delete[] kocsik;
  kocsik = new Kocsi[kocsik_szama];
  for (size_t i = 0; i < kocsik_szama; ++i)
  {
    kocsik[i] = other.kocsik[i];
  }

  jegyek = new Jegy *[jegyek_szama];
  for (size_t i = 0; i < jegyek_szama; ++i)
  {
    if (dynamic_cast<KedvezmenyesJegy *>(other.jegyek[i]))
    {
      jegyek[i] = new KedvezmenyesJegy(*dynamic_cast<KedvezmenyesJegy *>(other.jegyek[i]));
    }
    else if (dynamic_cast<FelarasJegy *>(other.jegyek[i]))
    {
      jegyek[i] = new FelarasJegy(*dynamic_cast<FelarasJegy *>(other.jegyek[i]));
    }
    else
    {
      jegyek[i] = new Jegy(*other.jegyek[i]);
    }
  }

  return *this;
}

Vonat::Vonat(size_t azonosito, size_t kocsik_sz, Kocsi *kocsik_ptr, Utvonal utv, size_t jegyek_sz, Jegy **jegyek_ptr)
    : vonat_azonosito(azonosito), kocsik_szama(kocsik_sz), kocsik(new Kocsi[kocsik_sz]), jegyek(new Jegy *[jegyek_sz]), jegyek_szama(jegyek_sz), utvonal(utv)
{
  for (size_t i = 0; i < kocsik_sz; ++i)
  {
    kocsik[i] = kocsik_ptr[i];
  }

  for (size_t i = 0; i < jegyek_sz; ++i)
  {
    if (dynamic_cast<KedvezmenyesJegy *>(jegyek_ptr[i]))
    {
      jegyek[i] = new KedvezmenyesJegy(*dynamic_cast<KedvezmenyesJegy *>(jegyek_ptr[i]));
    }
    else if (dynamic_cast<FelarasJegy *>(jegyek_ptr[i]))
    {
      jegyek[i] = new FelarasJegy(*dynamic_cast<FelarasJegy *>(jegyek_ptr[i]));
    }
    else
    {
      jegyek[i] = new Jegy(*jegyek_ptr[i]);
    }
  }
}

void Vonat::addJegy(Jegy &jegy)
{
  Jegy **newJegyek = new Jegy *[jegyek_szama + 1];
  for (size_t i = 0; i < jegyek_szama; ++i)
  {
    if (dynamic_cast<KedvezmenyesJegy *>(jegyek[i]))
    {
      newJegyek[i] = new KedvezmenyesJegy(*dynamic_cast<KedvezmenyesJegy *>(jegyek[i]));
    }
    else if (dynamic_cast<FelarasJegy *>(jegyek[i]))
    {
      newJegyek[i] = new FelarasJegy(*dynamic_cast<FelarasJegy *>(jegyek[i]));
    }
    else
    {
      newJegyek[i] = new Jegy(*jegyek[i]);
    }
  }
  if (dynamic_cast<KedvezmenyesJegy *>(&jegy))
  {
    newJegyek[jegyek_szama] = new KedvezmenyesJegy(*dynamic_cast<KedvezmenyesJegy *>(&jegy));
  }
  else if (dynamic_cast<FelarasJegy *>(&jegy))
  {
    newJegyek[jegyek_szama] = new FelarasJegy(*dynamic_cast<FelarasJegy *>(&jegy));
  }
  else
  {
    newJegyek[jegyek_szama] = new Jegy(jegy);
  }
  for (size_t i = 0; i < jegyek_szama; ++i)
  {
    delete jegyek[i];
  }
  delete[] jegyek;
  jegyek = newJegyek;
  jegyek_szama++;
}

size_t Vonat::createJegy(std::string indulo, std::string erkezo, int indulo_ora , int indulo_perc , double discountOrFee , const std::string &tipus)
{
  size_t kocsi_azonosito = -1;
  size_t hely_szam = -1;
  for (size_t i = 0; i < kocsik_szama; ++i)
  {
    if (!kocsik[i].tele())
    {
      kocsi_azonosito = kocsik[i].getAzonosito();
      hely_szam = kocsik[i].reserveHely();
      break;
    }
  }

  if (kocsi_azonosito == -1 || hely_szam == -1)
  {
    std::cout << "tele";
    throw "Nincs hely a vonaton";
    return -1;
  }

  bool induloFound = false;
  bool erkezoFound = false;
  size_t induloIndex = 0;
  size_t erkezoIndex = 0;

  for (size_t j = 0; j < utvonal.getAllomasokSzama(); ++j)
  {
    std::string allomasNev = utvonal.getAllomas(j).getNev();

    if (allomasNev == indulo)
    {
      induloFound = true;
      induloIndex = j;
    }

    if (allomasNev == erkezo)
    {
      erkezoFound = true;
      erkezoIndex = j;
      break;
    }
  }

  if (!induloFound || !erkezoFound || induloIndex >= erkezoIndex)
  {
    throw "Invalid route: departure and arrival stations not found or in the wrong order";
    return -1;
  }

  Ido indulas = utvonal.getAllomas(induloIndex).getIndulas();
  Ido erkezes = utvonal.getAllomas(erkezoIndex).getErkezes();

  Jegy *newJegy;
  if (discountOrFee > 0)
  {
    newJegy = new FelarasJegy(jegyek_szama, hely_szam, kocsi_azonosito, vonat_azonosito, indulo, indulas, erkezo, erkezes, discountOrFee, tipus);
  }
  else if (discountOrFee < 0)
  {
    newJegy = new KedvezmenyesJegy(jegyek_szama, hely_szam, kocsi_azonosito, vonat_azonosito, indulo, indulas, erkezo, erkezes, discountOrFee, tipus);
  }
  else
  {
    newJegy = new Jegy(jegyek_szama, hely_szam, kocsi_azonosito, vonat_azonosito, indulo, indulas, erkezo, erkezes);
  }
  addJegy(*newJegy);
  delete newJegy; // Since addJegy makes a copy, we can safely delete the local object.
  return jegyek_szama;
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
  delete[] kocsik;
  for (size_t i = 0; i < jegyek_szama; ++i)
  {
    delete jegyek[i];
  }
  delete[] jegyek;
}