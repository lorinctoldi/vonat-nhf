#ifndef VONAT_H
#define VONAT_H

#include <iostream>

#include "memtrace.h"

#include "serializable.h"
#include "kocsi.h"
#include "jegy.h"
#include "utvonal.h"

class Vonat : public Serializable
{
private:
    size_t vonat_azonosito; // A vonat azonositoja.
    size_t kocsik_szama;    // A vonathoz tartozo kocsik szama.
    Kocsi *kocsik;          // A vonathoz tartozo kocsik tombje.
    Jegy **jegyek;          // Array of pointers to Jegy
    size_t jegyek_szama;    // Number of jegyek in the array
    Utvonal utvonal;        // A vonathoz tartozo utvonal.
public:
    // Az osztály alapértelmezett konstruktora.
    Vonat();

    // Az osztály másoló konstruktora.
    // @param other - másolni kívánt Vonat objektum
    Vonat(const Vonat &other);

    Vonat &operator=(const Vonat &other);

    // Egyedi konstruktor.
    // @param azonosito - a vonat azonosítója
    // @param kocsik_sz - a vonathoz tartozó kocsik száma
    // @param kocsik_ptr - a kocsik tömbjére mutató pointer
    // @param utv - az útvonal, amelyhez a vonat tartozik
    // @param jegyek_sz - a vonathoz tartozó jegyek száma
    // @param jegyek_ptr - a jegyek tömbjére mutató pointer
    Vonat(size_t azonosito, size_t kocsik_sz, Kocsi *kocsik_ptr, Utvonal utv, size_t jegyek_sz, Jegy **jegyek_ptr);

    // Azonosító lekérdezése.
    // @return A vonat azonosítója.
    size_t getAzonosito() const;

    // Útvonal lekérdezése.
    // @return Az útvonal, amelyhez a vonat tartozik.
    Utvonal getUtvonal() const;

    // Útvonal beállítása.
    // @param utvonal - az útvonal, amelyhez a vonat tartozik
    void setUtvonal(const Utvonal &utvonal);

    // Kocsi hozzáadása a vonathoz.
    // @param kocsi - hozzáadni kívánt kocsi
    void addKocsi(Kocsi &kocsi);

    void createKocsi(size_t szekek);

    // Jegy hozzáadása a vonathoz.
    // @param jegy - hozzáadni kívánt jegy
    void addJegy(Jegy &jegy);

    Jegy* getJegy(size_t index) const;

    bool routeExists(std::string indulo, std::string erkezo) const;

    size_t findAllomas(std::string nev) const;

    int indulasiIdoKulonbseg(std::string nev, int ora, int perc);

    size_t createJegy(std::string indulo, std::string erkezo, int indulo_ora = 0, int indulo_perc = 0, double discountOrFee = 0, const std::string &tipus = "");

    virtual void write(std::ostream &os) const override;

    virtual void read(std::istream &is) override;

    // Az osztály destruktora.
    ~Vonat();
};

#endif // VONAT_H
