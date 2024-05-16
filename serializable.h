#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>

#include "memtrace.h"

class Serializable
{
public:
  virtual void write(std::ostream &os) const = 0;
  virtual void read(std::istream &is) = 0;
};

#endif