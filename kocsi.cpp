#include "kocsi.h"

Kocsi::Kocsi() : kocsi_azonosito(0), szekek_szama(0), foglalt_szekek_szama(0) {}

Kocsi::Kocsi(const Kocsi& other)
    : kocsi_azonosito(other.kocsi_azonosito), szekek_szama(other.szekek_szama), foglalt_szekek_szama(other.foglalt_szekek_szama) {}

Kocsi::Kocsi(size_t azonosito, size_t szekek) 
    : kocsi_azonosito(azonosito), szekek_szama(szekek), foglalt_szekek_szama(0) {}

bool Kocsi::tele() const {
    return szekek_szama == foglalt_szekek_szama;
}

size_t Kocsi::reserveHely() {
    if(tele())
        throw "A kocsi tele van";
    else
        return foglalt_szekek_szama++;
    return -1;
}

size_t Kocsi::getSzekek_szama() const {
    return szekek_szama;
}

size_t Kocsi::getAzonosito() const {
    return kocsi_azonosito;
}

Kocsi::~Kocsi() {
}
