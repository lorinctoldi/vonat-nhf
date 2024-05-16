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
    size_t jegyek_szama;    // A vonathoz tartozo jegyek szama.
    Jegy *jegyek;           // A vonathoz tartozo jegyek tombje.
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
    Vonat(size_t azonosito, size_t kocsik_sz, Kocsi *kocsik_ptr, Utvonal utv, size_t jegyek_sz, Jegy *jegyek_ptr);

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

    // Jegy hozzáadása a vonathoz.
    // @param jegy - hozzáadni kívánt jegy
    void addJegy(Jegy &jegy);

    virtual void write(std::ostream &os) const override
    {
        os << "===== Vonat =====\n";
        os << "vonat azonosito:\n";
        os << vonat_azonosito << '\n';
        os << "kocsik szama:\n";
        os << kocsik_szama << '\n';
        for (size_t i = 0; i < kocsik_szama; ++i)
        {
            kocsik[i].write(os);
        }
        os << "jegyek szama:\n";
        os << jegyek_szama << '\n';
        for (size_t i = 0; i < jegyek_szama; ++i)
        {
            jegyek[i].write(os);
        }
        utvonal.write(os);
    }

    virtual void read(std::istream &is) override
    {
        std::string header;
        std::getline(is, header); // "===== Vonat ====="
        std::getline(is, header); // "vonat azonosito:"
        is >> vonat_azonosito;
        is.ignore();              // Ignore newline character
        std::getline(is, header); // "kocsik szama:"
        is >> kocsik_szama;
        is.ignore(); // Ignore newline character
        kocsik = new Kocsi[kocsik_szama];
        for (size_t i = 0; i < kocsik_szama; ++i)
        {
            kocsik[i].read(is);
        }
        std::getline(is, header); // "jegyek szama:"
        is >> jegyek_szama;
        is.ignore();                     // Ignore newline character
        jegyek = new Jegy[jegyek_szama]; // Allocate array of pointers
        for (size_t i = 0; i < jegyek_szama; ++i)
        {
            std::string type;
            std::getline(is, type); // Read type identifier
            if (type == "JEGY")
            {
                Jegy j;
                j.read(is); // Call read() on the base class object
                jegyek[i] = j;
            }
            else if (type == "KEDVEZMENYES")
            {
                KedvezmenyesJegy j;
                j.read(is); // Call read() on the derived class object
                jegyek[i] = j;
            }
            else if (type == "FELARAS")
            {
                FelarasJegy j;
                j.read(is); // Call read() on the derived class object
                jegyek[i] = j;
            }
        }
        utvonal.read(is);
    }
    // Az osztály destruktora.
    ~Vonat();
};

#endif // VONAT_H
