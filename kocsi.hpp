#ifndef KOCSI_HPP
#define KOCSI_HPP

#include <cstddef>
#include <iostream>

class Kocsi {
  size_t kocsi_azonosito;
  size_t szekek_szama;
  size_t foglalt_szekek_szama;
public:
  Kocsi();
  Kocsi(const Kocsi& other);
  Kocsi(size_t azonosito, size_t szekek);
  void szek_foglal();
  size_t getSzekek_szama() const;
  ~Kocsi();
};

#endif // KOCSI_HPP

// done
// red-flag : error
