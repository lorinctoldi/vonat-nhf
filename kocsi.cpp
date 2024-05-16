#include "kocsi.h"

Kocsi::Kocsi() : kocsi_azonosito(0), szekek_szama(0), foglalt_szekek_szama(0) {}

Kocsi::Kocsi(const Kocsi& other)
    : kocsi_azonosito(other.kocsi_azonosito), szekek_szama(other.szekek_szama), foglalt_szekek_szama(other.foglalt_szekek_szama) {}

Kocsi::Kocsi(size_t azonosito, size_t szekek) 
    : kocsi_azonosito(azonosito), szekek_szama(szekek), foglalt_szekek_szama(0) {}

void Kocsi::szek_foglal() {
    if (foglalt_szekek_szama < szekek_szama) {
        foglalt_szekek_szama++;
    } else {
      std::cout << "Nincs tobb szabad hely";
    }
}

size_t Kocsi::getSzekek_szama() const {
    return szekek_szama;
}

Kocsi::~Kocsi() {
}
