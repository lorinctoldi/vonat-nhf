#include "allomas.hpp"

int main() {
  // Vonat v;
  // Menetrend m(v, 1);

  const char* name = "alma"; 
  size_t id = 12;

  Allomas a(id, name, 12, 10, 16, 30);

  a.changeErkezes(17, 30);
  a.changeNev("alma");
  return 0;
}

