#include "vonat.h"

Vonat::Vonat() : vonat_azonosito(0), kocsik_szama(0), jegyek_szama(0), kocsik(nullptr), jegyek(nullptr) {}

Vonat::Vonat(const Vonat &other)
    : vonat_azonosito(other.vonat_azonosito), kocsik_szama(other.kocsik_szama), jegyek_szama(other.jegyek_szama),
      utvonal(other.utvonal)
{
  kocsik = new Kocsi[kocsik_szama];
  for (int i = 0; i < kocsik_szama; ++i)
    kocsik[i] = other.kocsik[i];

  jegyek = new Jegy *[jegyek_szama];
  for (int i = 0; i < jegyek_szama; ++i)
    if (dynamic_cast<KedvezmenyesJegy *>(other.jegyek[i]))
      jegyek[i] = new KedvezmenyesJegy(*dynamic_cast<KedvezmenyesJegy *>(other.jegyek[i]));
    else if (dynamic_cast<FelarasJegy *>(other.jegyek[i]))
      jegyek[i] = new FelarasJegy(*dynamic_cast<FelarasJegy *>(other.jegyek[i]));
    else
      jegyek[i] = new Jegy(*other.jegyek[i]);
}

Vonat &Vonat::operator=(const Vonat &other)
{
  if (this == &other)
    return *this;

  vonat_azonosito = other.vonat_azonosito;
  kocsik_szama = other.kocsik_szama;
  jegyek_szama = other.jegyek_szama;
  utvonal = other.utvonal;

  delete[] kocsik;
  kocsik = new Kocsi[kocsik_szama];
  for (int i = 0; i < kocsik_szama; ++i)
    kocsik[i] = other.kocsik[i];

  if (jegyek_szama > 0)
  {
    jegyek = new Jegy *[jegyek_szama];
    for (int i = 0; i < jegyek_szama; ++i)
      jegyek[i] = other.jegyek[i]->clone();
  }

  return *this;
}

Vonat::Vonat(int azonosito, int kocsik_sz, Kocsi kocsik_tomb[], Utvonal utv, int jegyek_sz, Jegy **jegyek_ptr)
    : vonat_azonosito(azonosito), kocsik_szama(kocsik_sz), jegyek_szama(jegyek_sz), kocsik(new Kocsi[kocsik_sz]), jegyek(new Jegy *[jegyek_sz]), utvonal(utv)
{
  for (int i = 0; i < kocsik_sz; ++i)
    kocsik[i] = kocsik_tomb[i];

  for (int i = 0; i < jegyek_sz; ++i)
    if (dynamic_cast<KedvezmenyesJegy *>(jegyek_ptr[i]))
      jegyek[i] = new KedvezmenyesJegy(*dynamic_cast<KedvezmenyesJegy *>(jegyek_ptr[i]));
    else if (dynamic_cast<FelarasJegy *>(jegyek_ptr[i]))
      jegyek[i] = new FelarasJegy(*dynamic_cast<FelarasJegy *>(jegyek_ptr[i]));
    else
      jegyek[i] = new Jegy(*jegyek_ptr[i]);
}

void Vonat::addJegy(Jegy &jegy)
{
  Jegy **temp = new Jegy *[jegyek_szama + 1];
  for (int i = 0; i < jegyek_szama; ++i)
  {
    temp[i] = jegyek[i]->clone();
    delete jegyek[i];
  }
  temp[jegyek_szama] = jegy.clone();

  delete[] jegyek;
  jegyek = temp;
  jegyek_szama++;
}

Jegy *Vonat::getJegy(int index) const
{
  if (index <= jegyek_szama)
    return jegyek[index - 1];
  else
    throw std::out_of_range("Nincs ilyen jegy a rendszerben.");
}

int Vonat::findAllomas(std::string nev) const
{
  for (int i = 0; i < utvonal.getAllomasokSzama(); ++i)
    if (utvonal.getAllomas(i).getNev() == nev)
      return i;

  return -1;
}

int Vonat::indulasiIdoKulonbseg(std::string nev, int ora, int perc)
{
  int allomas_index = findAllomas(nev);
  if (allomas_index == -1)
    return -1;
  Allomas m = utvonal.getAllomas(allomas_index);
  int i = m.getIndulasOra() * 60 + m.getIndulasPerc();
  int p = ora * 60 + perc;
  if (p > i)
    return -1;
  return i - p;
}

bool Vonat::routeExists(std::string indulo, std::string erkezo) const
{
  int induloIndex = findAllomas(indulo);
  int erkezoIndex = findAllomas(erkezo);

  if (induloIndex == -1 || erkezoIndex == -1 || induloIndex >= erkezoIndex)
    return false;
  return true;
}

int Vonat::createJegy(std::string indulo, std::string erkezo, int indulo_ora, int indulo_perc, double discountOrFee, const std::string &tipus)
{
  if (!routeExists(indulo, erkezo))
  {
    throw "Nincs ilyen ut";
  }

  int kocsi_azonosito = -1;
  int hely_szam = -1;
  for (int i = 0; i < kocsik_szama; ++i)
    if (!kocsik[i].tele())
    {
      kocsi_azonosito = kocsik[i].getAzonosito();
      hely_szam = kocsik[i].reserveHely();
      break;
    }

  if (hely_szam == -1)
    throw "Egy kocsiban sincsen szabad ulohely.";

  int induloIndex = findAllomas(indulo);
  int erkezoIndex = findAllomas(erkezo);

  Ido indulas = utvonal.getAllomas(induloIndex).getIndulas();
  Ido erkezes = utvonal.getAllomas(erkezoIndex).getErkezes();

  if (discountOrFee > 0) {
    Jegy* temp = new FelarasJegy(jegyek_szama + 1, hely_szam + 1, kocsi_azonosito, vonat_azonosito, indulo, indulas, erkezo, erkezes, discountOrFee, tipus);
    addJegy(*temp);
    delete temp;
  }
  else if (discountOrFee < 0) {
    Jegy* temp = new KedvezmenyesJegy(jegyek_szama + 1, hely_szam + 1, kocsi_azonosito, vonat_azonosito, indulo, indulas, erkezo, erkezes, discountOrFee, tipus);
    addJegy(*temp);
    delete temp;
  }
  else {
    Jegy* temp = new Jegy(jegyek_szama + 1, hely_szam + 1, kocsi_azonosito, vonat_azonosito, indulo, indulas, erkezo, erkezes);
    addJegy(*temp);
    delete temp;
  }

  return jegyek_szama;
}

void Vonat::addKocsi(Kocsi &kocsi)
{
  Kocsi *temp = new Kocsi[kocsik_szama + 1];
  for (int i = 0; i < kocsik_szama; i++)
    temp[i] = kocsik[i];
  temp[kocsik_szama] = kocsi;
  delete[] kocsik;
  kocsik = temp;
  kocsik_szama++;
}

void Vonat::createKocsi(int szekek)
{
  Kocsi *temp = new Kocsi[kocsik_szama + 1];
  for (int i = 0; i < kocsik_szama; i++)
    temp[i] = kocsik[i];
  temp[kocsik_szama] = Kocsi(kocsik_szama, szekek);
  if (kocsik_szama > 0)
    delete[] kocsik;
  kocsik = temp;
  kocsik_szama++;
}

int Vonat::getAzonosito() const
{
  return vonat_azonosito;
}

Utvonal Vonat::getUtvonal() const
{
  return utvonal;
}

void Vonat::setAzonosito(int azonosito)
{
  vonat_azonosito = azonosito;
}

void Vonat::setUtvonal(const Utvonal &utv)
{
  utvonal = utv;
}

void Vonat::write(std::ostream &os) const
{
  os << "===== Vonat =====\n";
  os << "vonat azonosito:\n";
  os << vonat_azonosito << '\n';
  os << "kocsik szama:\n";
  os << kocsik_szama << '\n';
  for (int i = 0; i < kocsik_szama; ++i)
  {
    kocsik[i].write(os);
  }
  os << "jegyek szama:\n";
  os << jegyek_szama << '\n';
  for (int i = 0; i < jegyek_szama; ++i)
    jegyek[i]->write(os);
  utvonal.write(os);
}

void Vonat::read(std::istream &is)
{
  std::string header;
  std::getline(is, header);
  std::getline(is, header);
  is >> vonat_azonosito;
  is.ignore();
  std::getline(is, header);
  is >> kocsik_szama;
  is.ignore();

  delete[] kocsik;
  kocsik = new Kocsi[kocsik_szama];

  for (int i = 0; i < kocsik_szama; ++i)
    kocsik[i].read(is);

  std::getline(is, header);
  is >> jegyek_szama;
  is.ignore();

  delete[] jegyek;
  jegyek = new Jegy *[jegyek_szama];

  for (int i = 0; i < jegyek_szama; ++i)
  {
    std::string type;
    std::getline(is, type);
    if (type == "JEGY")
    {
      jegyek[i] = new Jegy();
      jegyek[i]->read(is);
    }
    else if (type == "KEDVEZMENYES")
    {
      jegyek[i] = new KedvezmenyesJegy();
      jegyek[i]->read(is);
    }
    else if (type == "FELARAS")
    {
      jegyek[i] = new FelarasJegy();
      jegyek[i]->read(is);
    }
  }
  utvonal.read(is);
}

Vonat::~Vonat()
{
  delete[] kocsik;
  for (int i = 0; i < jegyek_szama; ++i)
    delete jegyek[i];
  delete[] jegyek;
}