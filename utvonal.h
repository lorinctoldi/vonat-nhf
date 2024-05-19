#ifndef UTVONAL_H
#define UTVONAL_H

#include "allomas.h"

// Interfész az objektumok sorosításához és deszerializálásához.
#include "serializable.h"

// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"

// Az Útvonal osztály az egyes vonatútvonalakat reprezentálja.
// Tartalmazza az útvonal azonosítóját, az állomások számát, valamint az állomásokat.
class Utvonal : public Serializable
{
  size_t utvonal_azonosito; // Az útvonal azonosítója
  size_t allomasok_szama;   // Az állomások száma az útvonalon
  Allomas *allomasok;       // Az állomások tömbje az útvonalon
public:
  // Az osztály alapértelmezett konstruktora.
  Utvonal();

  // Az osztály másoló konstruktora.
  // @param other - másolni kívánt Utvonal objektum
  Utvonal(const Utvonal &other);

  // Állomás hozzáadása az útvonalhoz.
  // @param allomas - hozzáadni kívánt állomás
  void addAllomas(Allomas allomas);

  // Új állomás létrehozása az útvonalon.
  // @param nev - az állomás neve
  // @param erkezes_ora - az állomásra érkező vonat óra
  // @param erkezes_perc - az állomásra érkező vonat perc
  // @param indulas_óra - az állomásról induló vonat óra
  // @param indulas_perc - az állomásról induló vonat perc
  void createAllomas(std::string nev, int erkezes_ora, int erkezes_perc, int indulas_ora, int indulas_perc);

  // Az útvonal értékadás operátora.
  // @param other - másolni kívánt Utvonal objektum
  Utvonal &operator=(const Utvonal &other);

  // Állomás cseréje az útvonalon.
  // @param index - az állomás indexe, amelyet cserélni kívánunk
  // @param allomas - beszúrni kívánt állomás
  void changeAllomas(size_t index, Allomas allomas);

  // Állomás eltávolítása az útvonalról.
  // @param index - az eltávolítani kívánt állomás indexe
  void removeAllomas(size_t index);

  // Az útvonalon található állomások számának lekérdezése.
  size_t getAllomasokSzama() const;

  // Visszaad egy kívánt számú állomást a listából az index alapján.
  // @param i - az állomás indexe
  // @return Az állomás referenciája az adott indexen
  Allomas &getAllomas(size_t i) const;

  // Objektum kiírása adatfolyamba esztétikus formában.
  // @param os - Az írásra használt kimeneti adatfolyam.
  void kiir(std::ostream &os) const;

  // Serializable interfész implementációja: objektum írása adatfolyamba.
  // @param os - Az írásra használt kimeneti adatfolyam.
  void write(std::ostream &os) const;

  // Serializable interfész implementációja: objektum olvasása adatfolyamból.
  // @param is - A beolvasásra használt bemeneti adatfolyam.
  void read(std::istream &is);

  // Az osztály destruktora.
  ~Utvonal();
};

#endif // UTVONAL_H
