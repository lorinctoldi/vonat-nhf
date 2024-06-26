#ifndef MENETREND_H
#define MENETREND_H

#include "vonat.h"

// Szabványos bemenet és kimenet kezeléséhez.
#include <iostream>

// Interfész az objektumok sorosításához és deszerializálásához.
#include "serializable.h"

// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"

// A Menetrend osztály reprezentálja a vonatok menetrendjét.
// Tartalmazza a vonatok számát és a vonatokat.
class Menetrend : public Serializable
{
  size_t vonatok_szama; // A menetrendben szereplő vonatok száma.
  Vonat *vonatok;       // A menetrendben szereplő vonatok tömbje.
public:
  // Az osztály alapértelmezett konstruktora.
  Menetrend() : vonatok_szama(0), vonatok(NULL) {}

  // Paraméteres konstruktor.
  // @param v - hozzáadni kívánt vonat
  Menetrend(Vonat v);

  // Paraméteres konstruktor.
  // @param v - a vonatok tömbje
  // @param meret - a vonatok tömbjének mérete
  Menetrend(Vonat *v, size_t meret) : vonatok_szama(meret), vonatok(v) {}

  // Masoló konstruktor.
  // @param m - másolni kívánt Menetrend objektum
  Menetrend(const Menetrend &m);

  // Vonat hozzáadása a menetrendhez.
  // @param v - hozzáadni kívánt vonat
  void addVonat(Vonat v);

  // Vonat módosítása a menetrendben.
  // @param v - a módosítandó vonat
  // @param index - a vonat indexe a menetrendben
  void changeVonat(Vonat v, size_t index);

  // Vonat lekérdezése a megadott indexen.
  // @param index - a kívánt vonat indexe
  // @return Az adott indexen található vonat
  Vonat &getVonat(size_t index) const;

  // Vonatok számának lekérdezése.
  // @return A vonatok száma a menetrendben
  size_t getVonatokSzama() const;

  // Vonat törlése a megadott indexen.
  // @param index - a törlendő vonat indexe
  void removeVonat(size_t index);

  // Jegy létrehozása a megadott állomások között.
  // @param indulo - Az induló állomás neve.
  // @param erkezo - Az érkező állomás neve.
  // @param indulo_ora - Az indulási idő órája.
  // @param indulo_perc - Az indulási idő perce.
  // @param discountOrFee - Kedvezmény vagy felár értéke.
  // @param tipus - A jegy típusa.
  void createJegy(std::string indulo, std::string erkezo, int indulo_ora, int indulo_perc, double discountOrFee = 0, const std::string &tipus = "");

  // Menetrendben tárolt adatok törlése.
  void clear();

  // Kiírja a menetrendben található vonatok útvonalát a megadott állomások között.
  // Ha indulo és erkezo üres, akkor mindet.
  // Ha csak indulo üres, akkor kiír minden útvonalat, amely az adott állomásba tart.
  // Ha csak erkezo üres, akkor kiír minden útvonalat, amely az adott állomásból indul.
  // Ha erkezo és indulo üres, akkor kiír minden útvonalat, amely a két állomás között van.
  // @param os - Az írásra használt kimeneti adatfolyam.
  // @param indulo - Az induló állomás neve.
  // @param erkezo - Az érkező állomás neve.
  void kiir(std::ostream &os, std::string indulo, std::string erkezo) const;

  // Serializable interfész implementációja: objektum írása adatfolyamba.
  // @param os - Az írásra használt kimeneti adatfolyam.
  void write(std::ostream &os) const;

  // Serializable interfész implementációja: objektum olvasása adatfolyamból.
  // @param is - A beolvasásra használt bemeneti adatfolyam.
  void read(std::istream &is);

  // Az osztály destruktora.
  ~Menetrend();
};

#endif // MENETREND_H
