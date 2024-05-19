#ifndef ALLOMAS_H
#define ALLOMAS_H

// Idő tárolásához.
#include "ido.h"

// Szabványos bemenet és kimenet kezeléséhez.
#include <iostream>

// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"

// Interfész az objektumok sorosításához és deszerializálásához.
#include "serializable.h"

// Az Allomas osztály definíciója.
class Allomas : public Serializable
{
  size_t allomas_azonosito; // Az állomás azonosítója.
  std::string nev;          // Az állomás neve.
  Ido indulas;              // Az indulási időpont tárolója.
  Ido erkezes;              // Az érkezési időpont tárolója.
public:
  // Az osztály alapértelmezett konstruktora.
  Allomas();

  // Másoló konstruktor.
  // @param other - Másolni kívánt Allomas objektum.
  Allomas(const Allomas &other);

  // Értékadó operátor.
  Allomas &operator=(const Allomas &other);

  // Egyedi konstruktor.
  // @param azonosito - Az állomás azonosítója.
  // @param nev - Az állomás neve.
  // @param erkezes_ora - Az érkezés órája.
  // @param erkezes_perc - Az érkezés perce.
  // @param indulas_ora - Az indulás órája.
  // @param indulas_perc - Az indulás perce.
  Allomas(size_t azonosito, const std::string &nev, int erkezes_ora, int erkezes_perc, int indulas_ora, int indulas_perc);

  // Az érkezés idejének módosítása.
  // @param ora - Az új érkezés órája.
  // @param perc - Az új érkezés perce.
  void changeErkezes(int ora, int perc);

  // Az indulás idejének módosítása.
  // @param ora - Az új indulás órája.
  // @param perc - Az új indulás perce.
  void changeIndulas(int ora, int perc);

  // Az állomás nevének módosítása.
  // @param other - Az új név.
  void changeNev(const std::string &other);

  // Az indulás órájának lekérdezése.
  // @return Az indulás órája.
  int getIndulasOra();

  // Az indulás percének lekérdezése.
  // @return Az indulás perce.
  int getIndulasPerc();

  // Az érkezés órájának lekérdezése.
  // @return Az érkezés órája.
  int getErkezesOra();

  // Az érkezés percének lekérdezése.
  // @return Az érkezés perce.
  int getErkezesPerc();

  // Az indulási idő referenciájának lekérdezése.
  // @return Az indulás idejének referenciája.
  Ido &getIndulas();

  // Az érkezési idő referenciájának lekérdezése.
  // @return Az érkezés idejének referenciája.
  Ido &getErkezes();

  // Az állomás névének lekérdezése.
  // @return Az állomás neve.
  std::string &getNev();

  // Serializable interfész implementációja: objektum írása adatfolyamba.
  // @param os - Az írásra használt kimeneti adatfolyam.
  void write(std::ostream &os) const;

  // Serializable interfész implementációja: objektum olvasása adatfolyamból.
  // @param is - A beolvasásra használt bemeneti adatfolyam.
  void read(std::istream &is);

  // Az osztály destruktora.
  ~Allomas();
};

#endif // ALLOMAS_H