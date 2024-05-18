#ifndef IDO_H
#define IDO_H

#include <iostream>
#include "serializable.h"

#include "memtrace.h"

class Ido : public Serializable
{
private:
    int ora;
    int perc;
public:
    Ido();
    Ido(int o, int p);

    Ido(const Ido &other);

    ~Ido();

    int getOra() const;
    int getPerc() const;

    void setOra(int o);
    void setPerc(int p);

    void setIdo(int o, int p);
    void addPerc(int p);
    void addOra(int o);

    bool operator==(const Ido& other) const;
    bool operator!=(const Ido& other) const;

    void write(std::ostream &os) const;

    void kiir(std::ostream &os) const;

    void read(std::istream &is);
};

#endif // IDO_H
