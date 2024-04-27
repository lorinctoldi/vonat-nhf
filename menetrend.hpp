#ifndef MENETREND_HPP
#define MENETREND_HPP

#include "vonat.hpp"

class Menetrend {
  size_t vonatok_szama;
  Vonat* vonatok;
public:
  Menetrend(): vonatok_szama(0), vonatok(NULL) { }
  Menetrend(Vonat v);
  Menetrend(Vonat *v, size_t meret): vonatok_szama(meret), vonatok(v) { }
  Menetrend(const Menetrend& m);
  void addVonat(Vonat v);
  void changeVonat(Vonat v, size_t index);
  Vonat getVonat(size_t index);
  void kiir();
  ~Menetrend();
};

#endif // MENETREND_HPP
