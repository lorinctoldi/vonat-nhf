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
  v.setAzonosito(vonatok_szama);
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

size_t Menetrend::getVonatokSzama() const {
  return vonatok_szama;
}

void Menetrend::removeVonat(size_t index) {
  if (index >= vonatok_szama) {
        std::cerr << "Index out of range." << std::endl;
        return;
    }

    for (size_t i = index; i < vonatok_szama - 1; ++i) {
        vonatok[i] = vonatok[i + 1];
    }

    vonatok_szama--;

    Vonat* temp_vonatok = new Vonat[vonatok_szama];
    
    for (size_t i = 0; i < vonatok_szama; ++i) {
        temp_vonatok[i] = vonatok[i];
    }
    
    delete[] vonatok;

    vonatok = temp_vonatok;
}

void Menetrend::createJegy(std::string indulo, std::string erkezo, int indulo_ora, int indulo_perc, double discountOrFee, const std::string &tipus) {
  if(vonatok_szama == 0) throw "Nincsenek vonatok a rendszerben.";
  size_t leghamarabb_indulo_vonat = -1;
  int min_ido = -1;
  for(size_t i = 0; i < vonatok_szama; ++i) {
    if(!vonatok[i].routeExists(indulo, erkezo)) continue;
    int t = vonatok[i].indulasiIdoKulonbseg(indulo, indulo_ora, indulo_perc);

    if((min_ido == -1 && t != -1) || (min_ido != -1 && t < min_ido)) {
      min_ido = t;
      leghamarabb_indulo_vonat = i;
    }
  }

  if(leghamarabb_indulo_vonat == -1) {
    throw "nem talalt vonatot";
    return;
  }

  size_t jegy_index = vonatok[leghamarabb_indulo_vonat].createJegy(indulo, erkezo, indulo_ora, indulo_perc, discountOrFee, tipus);
  vonatok[leghamarabb_indulo_vonat].getJegy(jegy_index)->kiir(std::cout);
}

void Menetrend::clear()
  {
    if (vonatok_szama > 0)
    {
      delete[] vonatok;
      vonatok = nullptr;
      vonatok_szama = 0;
    }
  }


void Menetrend::kiir(std::ostream &os, std::string indulo = "", std::string erkezo = "") const
{
  os << "\nMenetrend:\n";
  bool talalt = false;
  for (size_t i = 0; i < vonatok_szama; ++i)
  {
    size_t induloIndex = vonatok[i].findAllomas(indulo);
    size_t erkezoIndex = vonatok[i].findAllomas(erkezo);
    if(!vonatok[i].routeExists(indulo, erkezo) && induloIndex == -1 && erkezoIndex == -1 && (!indulo.empty() && !erkezo.empty())) continue;

    talalt = true;
    Utvonal u = vonatok[i].getUtvonal();

    if ((indulo.empty() || (induloIndex != -1)) && (erkezo.empty() || (erkezoIndex != -1)))
    {
      os << "Vonat " << vonatok[i].getAzonosito()+1 << " :\n";

      if ((induloIndex != -1) && (erkezoIndex != -1) && induloIndex < erkezoIndex)
      {
        if (induloIndex > 0)
        {
          os << "        ...\n";
          os << "        |\n";
        }

        os << "        " << u.getAllomas(induloIndex).getNev() << " : " << u.getAllomas(induloIndex).getIndulas().getOra() << ":" << u.getAllomas(induloIndex).getIndulas().getPerc() << "\n";
        os << "        |\n";

        if (erkezoIndex > induloIndex + 1)
        {
          os << "        ...\n";
          os << "        |\n";
        }

        os << "        " << u.getAllomas(erkezoIndex).getNev() << " : " << u.getAllomas(erkezoIndex).getErkezes().getOra() << ":" << u.getAllomas(erkezoIndex).getErkezes().getPerc() << "\n";

        if (erkezoIndex < u.getAllomasokSzama() - 1)
        {
          os << "        |\n";
          os << "        ...\n";
        }
      }
      else if ((induloIndex != -1))
      {
        if (induloIndex > 0)
        {
          os << "        ...\n";
          os << "        |\n";
        }

        for (size_t j = induloIndex; j < u.getAllomasokSzama(); ++j)
        {
          os << "        " << u.getAllomas(j).getNev() << " : " << u.getAllomas(j).getIndulas().getOra() << ":" << u.getAllomas(j).getIndulas().getPerc() << "\n";
          if (j < u.getAllomasokSzama() - 1)
          {
            os << "        |\n";
          }
        }
      }
      else if ((erkezoIndex != -1))
      {
        for (size_t j = 0; j <= erkezoIndex; ++j)
        {
          os << "        " << u.getAllomas(j).getNev() << " : " << u.getAllomas(j).getIndulas().getOra() << ":" << u.getAllomas(j).getIndulas().getPerc() << "\n";
          if (j < erkezoIndex)
          {
            os << "        |\n";
          }
        }

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
  if(!talalt) os << "A megadott allomasok kozott vonat nem kozlekedik.\n";
}

void Menetrend::write(std::ostream &os) const
  {
    os << "===== Menetrend =====\n";
    os << "Vonatok szama:\n";
    os << vonatok_szama << '\n';
    for (size_t i = 0; i < vonatok_szama; ++i)
    {
      vonatok[i].write(os);
    }
  }

  void Menetrend::read(std::istream &is)
  {
    std::string header;
    std::getline(is, header);
    std::getline(is, header);
    is >> vonatok_szama;
    is.ignore();
    vonatok = new Vonat[vonatok_szama];
    for (size_t i = 0; i < vonatok_szama; ++i)
    {
      vonatok[i].read(is);
    }
  }

Menetrend::~Menetrend()
{
  delete[] vonatok;
}
