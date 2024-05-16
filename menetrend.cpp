#include "menetrend.h"

Menetrend::Menetrend(Vonat v)
{
  vonatok_szama = 1;
  vonatok = new Vonat[vonatok_szama];
  vonatok[0] = v;
};

void Menetrend::addVonat(Vonat v)
{
vonatok_szama += 1;

    // Create a new array with the increased size
    Vonat *temp_vonatok = new Vonat[vonatok_szama];

    // Copy the contents of the old array to the new array
    for (size_t i = 0; i < vonatok_szama - 1; ++i)
        temp_vonatok[i] = vonatok[i];

    // Add the new Vonat object to the end of the new array
    temp_vonatok[vonatok_szama - 1] = v;

    // Deallocate the memory of the old array
    delete[] vonatok;

    // Assign the new array to vonatok
    vonatok = temp_vonatok;
}

void Menetrend::changeVonat(Vonat v, size_t index)
{
  vonatok[index] = v;
}

void Menetrend::kiir() {
  
}

Menetrend::~Menetrend()
{
  delete[] vonatok;
}
