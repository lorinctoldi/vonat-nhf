#ifndef UTVONAL_HPP
#define UTVONAL_HPP

#include "allomas.hpp"

class Utvonal {
  size_t utvonal_azonosito;
  size_t allomasok_szama;
  Allomas *allomasok;
public:
  Utvonal();
  Utvonal(const Utvonal& other);
  void addAllomas(Allomas allomas);
  void changeAllomas(size_t index, Allomas allomas);
  void removeAllomas(size_t index);
  ~Utvonal();
};

#endif // UTVONAL_HPP

// done
