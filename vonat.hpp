#ifndef VONAT_HPP
#define VONAT_HPP

#include <iostream>

#include "memtrace.h"

#include "kocsi.hpp"
#include "jegy.hpp"
#include "utvonal.hpp"

class Vonat {
private:
    size_t vonat_azonosito; // A vonat azonositoja.
    size_t kocsik_szama;    // A vonathoz tartozo kocsik szama.
    Kocsi* kocsik;          // A vonathoz tartozo kocsik tombje.
    size_t jegyek_szama;    // A vonathoz tartozo jegyek szama.
    Jegy* jegyek;           // A vonathoz tartozo jegyek tombje.
    Utvonal utvonal;        // A vonathoz tartozo utvonal.
public:
    // Az osztály alapértelmezett konstruktora.
    Vonat();

    // Az osztály másoló konstruktora.
    // @param other - másolni kívánt Vonat objektum
    Vonat(const Vonat& other);

    // Egyedi konstruktor.
    // @param azonosito - a vonat azonosítója
    // @param kocsik_sz - a vonathoz tartozó kocsik száma
    // @param kocsik_ptr - a kocsik tömbjére mutató pointer
    // @param utv - az útvonal, amelyhez a vonat tartozik
    // @param jegyek_sz - a vonathoz tartozó jegyek száma
    // @param jegyek_ptr - a jegyek tömbjére mutató pointer
    Vonat(size_t azonosito, size_t kocsik_sz, Kocsi* kocsik_ptr, Utvonal utv, size_t jegyek_sz, Jegy* jegyek_ptr);
    
    // Azonosító lekérdezése.
    // @return A vonat azonosítója.
    size_t getAzonosito() const;

    // Útvonal lekérdezése.
    // @return Az útvonal, amelyhez a vonat tartozik.
    Utvonal getUtvonal() const;

    // Útvonal beállítása.
    // @param utvonal - az útvonal, amelyhez a vonat tartozik
    void setUtvonal(const Utvonal& utvonal);

    // Kocsi hozzáadása a vonathoz.
    // @param kocsi - hozzáadni kívánt kocsi
    void addKocsi(Kocsi& kocsi);

    // Jegy hozzáadása a vonathoz.
    // @param jegy - hozzáadni kívánt jegy
    void addJegy(Jegy& jegy);

  // Operátor túlterhelés: Streambe írás a Vonat osztályhoz.
  // @param os - referencia a kimeneti streamre
  // @param vonat - referencia a kiírandó Vonat objektumra
  // @return A kimeneti stream referenciaja
  friend std::ostream &operator<<(std::ostream &os, const Vonat &vonat);

  // Operátor túlterhelés: Streamből olvasás a Vonat osztályhoz.
  // @param is - referencia a bemeneti streamre
  // @param vonat - referencia a beolvasandó Vonat objektumra
  // @return A bemeneti stream referenciaja
  friend std::istream &operator>>(std::istream &is, Vonat &vonat);

    // Az osztály destruktora.
    ~Vonat();
};

#endif // VONAT_HPP
