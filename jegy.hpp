#ifndef JEGY_HPP
#define JEGY_HPP

// red-flag -- start
#include <cstring>
#include <cstddef>
// red-flag -- end

#include "allomas.hpp"

class Jegy
{
protected:
  size_t jegy_azonosito;
  size_t helyszam;
  size_t kocsi_szam;
  size_t vonat_szam;
  Allomas *indulo;
  Allomas *cel;
  double kedvezmeny;
  int ar;
  int getAr();
  
public:
  Jegy();
  Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel);
  Jegy(const Jegy &other);
  Jegy &operator=(const Jegy &other);

  virtual void kiir() const = 0;
  virtual bool operator==(const Jegy &other) const;
  virtual bool operator!=(const Jegy &other) const;
  virtual ~Jegy() {}
};

class ElsoOsztalyJegy : public Jegy
{
  char *tipus;
public:
  ElsoOsztalyJegy();
  ElsoOsztalyJegy(const ElsoOsztalyJegy &other);
  ElsoOsztalyJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel, double kedvezmeny);

  ~ElsoOsztalyJegy();

  void kiir() const override;
};

class MasodOsztalyJegy : public Jegy
{
  char *tipus;
public:
  MasodOsztalyJegy();
  MasodOsztalyJegy(const MasodOsztalyJegy &other);
  MasodOsztalyJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, Allomas *indulo, Allomas *cel, double kedvezmeny);

  ~MasodOsztalyJegy();

  void kiir() const override;
};

class DiakJegy : public Jegy
{
  char *tipus;

public:
  DiakJegy();
  DiakJegy(const Jegy &other);
  ~DiakJegy();
};

class NyugdijasJegy : public Jegy
{
  char *tipus;

public:
  NyugdijasJegy();
  NyugdijasJegy(const Jegy &other);
  ~NyugdijasJegy();
};

#endif // JEGY_HPP
