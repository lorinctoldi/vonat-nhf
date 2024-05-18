#ifndef JEGY_H
#define JEGY_H

#include <cstring>
#include <cstddef>
#include <iostream>

#include "allomas.h"
#include "ido.h"
#include "serializable.h"

#include "memtrace.h"

// A Jegy osztaly reprezentalja a vonatjegyeket.
// Tartalmazza a jegy azonositojat, a helyszamot, a kocsi szamat, a vonat szamat,
// az indulo es a cel allomast, valamint az arat.
class Jegy
{
protected:
  size_t jegy_azonosito;          // A jegy azonositoja.
  size_t helyszam;                // A jegyhez tartozo helyszam.
  size_t kocsi_szam;              // A kocsi azonositoja, ahol a hely talalhato.
  size_t vonat_szam;              // A vonat azonositoja, amelyre a jegy szol.
  std::string indulo_nev;         // Az indulasi allomas neve.
  Ido indulo_ido;                 // Az indulasi idopont.
  std::string cel_nev;            // A celallomas neve.
  Ido cel_ido;                    // A celallomas idopontja.
  int ar;                         // A jegy ara.
  virtual int getAr(double pred); // A jegy arat szamito fuggveny.
public:
  // Az osztaly alapertelmezett konstruktora.
  Jegy();

  // Egyedi konstruktor.
  // @param azonosito - a jegy azonositoja
  // @param hely - a helyszam
  // @param kocsi - a kocsi azonositoja
  // @param vonat - a vonat azonositoja
  // @param indulo - az indulasi allomas
  // @param cel - a celallomas
  Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, const std::string &indulo, Ido indulo_idopont,
       const std::string &cel, Ido cel_idopont);

  Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, const std::string &indulo, Ido indulo_idopont,
             const std::string &cel, Ido cel_idopont, double pred);

  // Masolo konstruktor.
  // @param other - masolni kivant Jegy objektum
  Jegy(const Jegy &other);

  // Masolo ertekadas operator.
  // @param other - masolni kivant Jegy objektum
  // @return A masolt Jegy objektum referenciaja
  Jegy &operator=(const Jegy &other);

  // Egyenloseg operator.
  // @param other - a masik Jegy objektum, amivel osszehasonlitjuk
  // @return true, ha a ket Jegy azonos, false egyebkent
  bool operator==(const Jegy &other) const;

  // Nem egyenloseg operator.
  // @param other - a masik Jegy objektum, amivel osszehasonlitjuk
  // @return true, ha a ket Jegy nem azonos, false egyebkent
  bool operator!=(const Jegy &other) const;

  // Kiiratas operator.
  // @param os - a kimeneti stream, amire kiirjuk a Jegy adatait
  virtual void kiir(std::ostream &os) const;

  virtual void write(std::ostream &os) const;

  virtual void read(std::istream &is);

  // Az osztaly virtualis destruktora.
  virtual ~Jegy() {}
};

// A KedvezmenyesJegy osztaly a Jegy osztaly leszarmazottja, es reprezentalja a kedvezmenyes jegyeket.
// Tartalmazza a tipust (pl. diak, nyugdijas) es a kedvezmeny merteket.
class KedvezmenyesJegy : public Jegy
{
  std::string tipus; // A kedvezmenyes tipus neve.
  double kedvezmeny; // A kedvezmeny merteket szazalekban kifejezo ertek.
public:
  // Az osztaly alapertelmezett konstruktora.
  KedvezmenyesJegy();

  // Masolo konstruktor.
  // @param other - masolni kivant KedvezmenyesJegy objektum
  KedvezmenyesJegy(const KedvezmenyesJegy &other);

  // Egyedi konstruktor.
  // @param azonosito - a jegy azonositoja
  // @param hely - a helyszam
  // @param kocsi - a kocsi azonositoja
  // @param vonat - a vonat azonositoja
  // @param indulo - az indulasi allomas
  // @param cel - a celallomas
  // @param kedvezmeny - a kedvezmeny merteket szazalekban kifejezo ertek
  // @param tipus_nev - a kedvezmenyes tipus neve
  KedvezmenyesJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, const std::string &indulo, Ido indulo_idopont,
                   const std::string &cel, Ido cel_idopont, double kedvezmeny, std::string tipus);

  KedvezmenyesJegy &operator=(const KedvezmenyesJegy &other);

  // Kiiratas operator.
  // @param os - a kimeneti stream, amire kiirjuk a KedvezmenyesJegy adatait
  void kiir(std::ostream &os) const;

  void write(std::ostream &os) const;

  void read(std::istream &is);

  // Az osztaly destruktora.
  ~KedvezmenyesJegy();
};

// A FelarasJegy osztaly a Jegy osztaly leszarmazottja, es reprezentalja a felaras jegyeket.
// Tartalmazza a tipust es a felart.
class FelarasJegy : public Jegy
{
  std::string tipus; // A felaras tipus neve.
  double felar;      // A felar erteket.
public:
  // Az osztaly alapertelmezett konstruktora.
  FelarasJegy();

  // Masolo konstruktor.
  // @param other - masolni kivant FelarasJegy objektum
  FelarasJegy(const FelarasJegy &other);

  // Egyedi konstruktor.
  // @param azonosito - a jegy azonositoja
  // @param hely - a helyszam
  // @param kocsi - a kocsi azonositoja
  // @param vonat - a vonat azonositoja
  // @param indulo - az indulasi allomas
  // @param cel - a celallomas
  // @param felar - a felar erteket
  // @param tipus_nev - a felaras tipus neve
  FelarasJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, const std::string &indulo, Ido indulo_idopont,
              const std::string &cel, Ido cel_idopont, double felar, std::string tipus);

  FelarasJegy &operator=(const FelarasJegy &other);

  // Kiiratas operator.
  // @param os - a kimeneti stream, amire kiirjuk a FelarasJegy adatait
  void kiir(std::ostream &os) const override;

  void write(std::ostream &os) const override;

  void read(std::istream &is) override;

  ~FelarasJegy();
};

#endif // JEGY_H