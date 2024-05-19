#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

// Ostream és istream használatához.
#include <iostream>

// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"

// Absztrakt osztály a perzisztencia megvalósításához.
// Tartalmazza a write() és read() virtuális függvényeket, amelyeket a leszármazott osztályoknak meg kell valósítaniuk.
class Serializable
{
public:
  // Adatfolyamra írásért felelős függvény.
  // @param os - Az objektum írása során használt kimeneti adatfolyam, például egy fájl vagy a konzol kimenete.
  virtual void write(std::ostream &os) const = 0;

  // Adatfolyamról olvasásért felelős függvény.
  // @param is - Az objektum olvasása során használt bemeneti adatfolyam, például egy fájl vagy a konzol bemenete.
  virtual void read(std::istream &is) = 0;
};

#endif