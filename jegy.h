#ifndef JEGY_H
#define JEGY_H

/// Szabványos bemenet és kimenet kezeléséhez.
#include <iostream>

/// Interfész az objektumok sorosításához és deszerializálásához.
#include "serializable.h"

/// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"

#include "allomas.h"

/// Idő tárolásához.
#include "ido.h"

/// A Jegy osztaly reprezentalja a vonatjegyeket.
/// Tartalmazza a jegy azonositojat, a helyszamot, a kocsi szamat, a vonat szamat,
/// az indulo es a cel allomast, valamint az arat.
class Jegy : public Serializable
{
protected:
  int jegy_azonosito;             /// A jegy azonosítója.
  int helyszam;                   /// A jegyhez tartozó helyszám.
  int kocsi_szam;                 /// A kocsi azonositója, ahol a hely található.
  int vonat_szam;                 /// A vonat azonosítója, amelyre a jegy szól.
  char* indulo_nev;         /// Az indulási állomas neve.
  Ido indulo_ido;                 /// Az indulási időpont.
  char* cel_nev;            /// A célállomás neve.
  Ido cel_ido;                    /// A célállomás időpontja.
  int ar;                         /// A jegy ára.
  virtual int getAr(double pred); /// A jegy árát számíto függvény.
public:
  /// Az osztaly alapertelmezett konstruktora.
  Jegy();

  /// Paraméteres konstruktor.
  /// @param azonosito - a jegy azonosítója
  /// @param hely - a helyszám
  /// @param kocsi - a kocsi azonosítója
  /// @param vonat - a vonat azonosítója
  /// @param indulo - az indulási állomás
  /// @param cel - a célállomás
  Jegy(int azonosito, int hely, int kocsi, int vonat, const char* indulo, Ido indulo_idopont,
       const char* cel, Ido cel_idopont);

  /// Paraméteres konstruktor (alosztályhoz).
  /// @param azonosito - a jegy azonosítója
  /// @param hely - a helyszám
  /// @param kocsi - a kocsi azonosítója
  /// @param vonat - a vonat azonosítója
  /// @param indulo - az indulási állomás
  /// @param cel - a célállomás
  /// @param pred - az árat meghatározó kedvezmény vagy felár értéke
  Jegy(int azonosito, int hely, int kocsi, int vonat, const char* indulo, Ido indulo_idopont,
       const char* cel, Ido cel_idopont, double pred);

  /// Az osztály másoló konstruktora.
  /// @param other - Másolni kívánt Jegy objektum.
  Jegy(const Jegy &other);

  /// Értékadó operátor.
  /// @param other - Másolni kívánt Jegy objektum.
  /// @return A másolt Jegy objektum referenciája.
  Jegy &operator=(const Jegy &other);

  /// Egyenlőség operátor.
  /// @param other - A másik jegy, amivel az egyenlőség vizsgálat történik.
  /// @return igaz, ha a jegyek megegyeznek, különben hamis.
  bool operator==(const Jegy &other) const;

  /// Nem egyenlőség operátor.
  /// @param other - A másik jegy, amivel a nem egyenlőség vizsgálat történik.
  /// @return igaz, ha a jegyek nem egyeznek meg, különben hamis.
  bool operator!=(const Jegy &other) const;

  /// Objektum kiírása adatfolyamba esztétikus formában.
  /// @param os - Az írásra használt kimeneti adatfolyam.
  virtual void kiir(std::ostream &os) const;

  /// Serializable interfész implementációja: objektum írása adatfolyamba.
  /// @param os - Az írásra használt kimeneti adatfolyam.
  virtual void write(std::ostream &os) const;

  /// Serializable interfész implementációja: objektum olvasása adatfolyamból.
  /// @param is - A beolvasásra használt bemeneti adatfolyam.
  virtual void read(std::istream &is);

  /// Létrehoz egy új Jegy objektum másolatot az aktuális objektumról.
  /// @return Jegy objektumra mutató pointer, amely az új másolatot tartalmazza.
  virtual Jegy *clone() const;

  /// Az osztály virtuális destruktora.
  virtual ~Jegy();
};

/// A KedvezményesJegy osztály a Jegy osztály leszármazottja, és reprezentálja a kedvezményes jegyeket.
/// Tartalmazza a típust (pl. diák, nyugdíjas) és a kedvezmény mértékét.
class KedvezmenyesJegy : public Jegy
{
  char* tipus; /// A kedvezményes típus neve.
  double kedvezmeny; /// A kedvezmény mértékét százalékban kifejező érték.
public:
  /// Az osztály alapértelmezett konstruktora.
  KedvezmenyesJegy();

  /// Másoló konstruktor.
  /// @param other - másolni kívánt KedvezmenyesJegy objektum
  KedvezmenyesJegy(const KedvezmenyesJegy &other);

  /// Paraméteres konstruktor.
  /// @param azonosito - a jegy azonosítója
  /// @param hely - a helyszám
  /// @param kocsi - a kocsi azonosítója
  /// @param vonat - a vonat azonosítója
  /// @param indulo - az indulási állomás
  /// @param cel - a célállomás
  /// @param kedvezmeny - a kedvezmény mértékét kifejező érték
  /// @param tipus_nev - a kedvezményes típus neve
  KedvezmenyesJegy(int azonosito, int hely, int kocsi, int vonat, const char* indulo, Ido indulo_idopont,
                   const char* cel, Ido cel_idopont, double kedvezmeny, const char* tipus);

  /// Értékadó operátor.
  /// @param other - másolni kívánt KedvezmenyesJegy objektum
  /// @return A másolt KedvezmenyesJegy objektum referenciája.
  KedvezmenyesJegy &operator=(const KedvezmenyesJegy &other);

  /// Objektum kiírása adatfolyamba esztétikus formában.
  /// @param os - Az írásra használt kimeneti adatfolyam.
  void kiir(std::ostream &os) const override;

  /// Serializable interfész implementációja: objektum írása adatfolyamba.
  /// @param os - Az írásra használt kimeneti adatfolyam.
  void write(std::ostream &os) const override;

  /// Serializable interfész implementációja: objektum olvasása adatfolyamból.
  /// @param is - A beolvasásra használt bemeneti adatfolyam.
  void read(std::istream &is) override;

  /// Létrehoz egy új Jegy objektum másolatot az aktuális objektumról.
  /// @return Jegy objektumra mutató pointer, amely az új másolatot tartalmazza.
  Jegy *clone() const override;

  /// Az osztály destruktora.
  ~KedvezmenyesJegy() override;
};

/// A FélárasJegy osztály a Jegy osztály leszármazottja, és reprezentálja a féláras jegyeket.
/// Tartalmazza a típust és a felárat.
class FelarasJegy : public Jegy
{
  char* tipus;       /// A féláras típus neve.
  double felar;      /// A felár értéket.
public:
  /// Az osztály alapértelmezett konstruktora.
  FelarasJegy();

  /// Másoló konstruktor.
  /// @param other - másolni kívánt FélárasJegy objektum
  FelarasJegy(const FelarasJegy &other);

  /// Paraméteres konstruktor.
  /// @param azonosito - a jegy azonosítója
  /// @param hely - a helyszám
  /// @param kocsi - a kocsi azonosítója
  /// @param vonat - a vonat azonosítója
  /// @param indulo - az indulási állomás
  /// @param cel - a célállomás
  /// @param felar - a felár értéket
  /// @param tipus_nev - a féláras típus neve
  FelarasJegy(int azonosito, int hely, int kocsi, int vonat, const char* indulo, Ido indulo_idopont,
              const char* cel, Ido cel_idopont, double felar, const char* tipus);

  /// Értékadó operátor.
  /// @param other - másolni kívánt FélárasJegy objektum
  /// @return A másolt FélárasJegy objektum referenciája.
  FelarasJegy &operator=(const FelarasJegy &other);

  /// Objektum kiírása adatfolyamba esztétikus formában.
  /// @param os - Az írásra használt kimeneti adatfolyam.
  void kiir(std::ostream &os) const override;

  /// Serializable interfész implementációja: objektum írása adatfolyamba.
  /// @param os - Az írásra használt kimeneti adatfolyam.
  void write(std::ostream &os) const override;

  /// Serializable interfész implementációja: objektum olvasása adatfolyamból.
  /// @param is - A beolvasásra használt bemeneti adatfolyam.
  void read(std::istream &is) override;

  /// Létrehoz egy új Jegy objektum másolatot az aktuális objektumról.
  /// @return Jegy objektumra mutató pointer, amely az új másolatot tartalmazza.
  Jegy *clone() const override;

  /// Az osztály destruktora.
  ~FelarasJegy() override;
};

#endif /// JEGY_H