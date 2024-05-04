#ifndef VONAT_HPP
#define VONAT_HPP

#include <iostream>

#include "kocsi.hpp"
#include "jegy.hpp"
#include "utvonal.hpp"

class Vonat {
private:
    size_t vonat_azonosito;
    size_t kocsik_szama;
    Kocsi* kocsik;
    size_t jegyek_szama;
    Jegy* jegyek;
    Utvonal utvonal;
public:
    Vonat();
    Vonat(const Vonat& other);
    Vonat(Kocsi* kocsik, Utvonal utvonal, Jegy* jegyek);
    Vonat::Vonat(size_t azonosito, size_t kocsik_sz, Kocsi* kocsik_ptr, Utvonal utv, size_t jegyek_sz, Jegy* jegyek_ptr);
    size_t getAzonosito() const;
    Utvonal getUtvonal() const;
    void setUtvonal(const Utvonal& utvonal);
    void addKocsi(size_t helyek_szama, size_t kocsi_szam);
    void addJegy(size_t kocsi_szam, size_t hely_szam);
    ~Vonat();
};

#endif // JEGY_HPP
