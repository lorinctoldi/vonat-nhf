#include "menetrend.h"

#include <iostream>

Menetrend::Menetrend(Vonat v)
{
  vonatok_szama = 1;
  vonatok = new Vonat[vonatok_szama];
  vonatok[0] = v;
};

void Menetrend::addVonat(Vonat v)
{
  vonatok_szama += 1;
  Vonat *temp_vonatok = new Vonat[vonatok_szama];

  for (size_t i = 0; i < vonatok_szama - 1; ++i)
    temp_vonatok[i] = vonatok[i];

  temp_vonatok[vonatok_szama - 1] = v;

  delete[] vonatok;

  vonatok = temp_vonatok;
}

void Menetrend::changeVonat(Vonat v, size_t index)
{
  vonatok[index] = v;
}

Vonat &Menetrend::getVonat(size_t index) const
{
  return vonatok[index];
}

void Menetrend::kiir(std::ostream &os, std::string indulo = "", std::string erkezo = "") const
{
  for (size_t i = 0; i < vonatok_szama; ++i)
  {
    Utvonal u = vonatok[i].getUtvonal();
    bool induloFound = false;
    bool erkezoFound = false;
    size_t induloIndex = 0;
    size_t erkezoIndex = 0;

    // Find the indices of indulo and erkezo
    for (size_t j = 0; j < u.getAllomasokSzama(); ++j)
    {
      std::string allomasNev = u.getAllomas(j).getNev();

      if (allomasNev == indulo)
      {
        induloFound = true;
        induloIndex = j;
      }

      if (allomasNev == erkezo)
      {
        erkezoFound = true;
        erkezoIndex = j;
        break;
      }
    }

    if ((indulo.empty() || induloFound) && (erkezo.empty() || erkezoFound))
    {
      os << "Vonat " << vonatok[i].getAzonosito() << " :\n";

      if (induloFound && erkezoFound && induloIndex < erkezoIndex)
      {
        // Print "..." if there are stations before indulo
        if (induloIndex > 0)
        {
          os << "        ...\n";
          os << "        |\n";
        }

        // Print indulo station
        os << "        " << u.getAllomas(induloIndex).getNev() << " : " << u.getAllomas(induloIndex).getIndulas().getOra() << ":" << u.getAllomas(induloIndex).getIndulas().getPerc() << "\n";
        os << "        |\n";

        // Check if there are intermediate stations
        if (erkezoIndex > induloIndex + 1)
        {
          os << "        ...\n";
          os << "        |\n";
        }

        // Print erkezo station
        os << "        " << u.getAllomas(erkezoIndex).getNev() << " : " << u.getAllomas(erkezoIndex).getErkezes().getOra() << ":" << u.getAllomas(erkezoIndex).getErkezes().getPerc() << "\n";

        // Print "..." if there are stations after erkezo
        if (erkezoIndex < u.getAllomasokSzama() - 1)
        {
          os << "        |\n";
          os << "        ...\n";
        }
      }
      else if (induloFound)
      {
        // Print "..." if there are stations before indulo
        if (induloIndex > 0)
        {
          os << "        ...\n";
          os << "        |\n";
        }

        // Print all stations from indulo to the end
        for (size_t j = induloIndex; j < u.getAllomasokSzama(); ++j)
        {
          os << "        " << u.getAllomas(j).getNev() << " : " << u.getAllomas(j).getIndulas().getOra() << ":" << u.getAllomas(j).getIndulas().getPerc() << "\n";
          if (j < u.getAllomasokSzama() - 1)
          {
            os << "        |\n";
          }
        }
      }
      else if (erkezoFound)
      {
        // Print all stations from the beginning to erkezo
        for (size_t j = 0; j <= erkezoIndex; ++j)
        {
          os << "        " << u.getAllomas(j).getNev() << " : " << u.getAllomas(j).getIndulas().getOra() << ":" << u.getAllomas(j).getIndulas().getPerc() << "\n";
          if (j < erkezoIndex)
          {
            os << "        |\n";
          }
        }

        // Print "..." if there are stations after erkezo
        if (erkezoIndex < u.getAllomasokSzama() - 1)
        {
          os << "        |\n";
          os << "        ...\n";
        }
      }
      else
      {
        u.kiir(os);
      }
    }
  }
}

Menetrend::~Menetrend()
{
  delete[] vonatok;
}
