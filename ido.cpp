#include "ido.h"

Ido::Ido() : ora(0), perc(0) {}

Ido::Ido(int o, int p) : ora(o), perc(p) {}
Ido::Ido(const Ido &other) : ora(other.getOra()), perc(other.getPerc()){};

Ido::~Ido()
{
}

int Ido::getOra() const
{
    return ora;
}

int Ido::getPerc() const
{
    return perc;
}

void Ido::setOra(int o)
{
    ora = o;
}

void Ido::setPerc(int p)
{
    perc = p;
}

void Ido::setIdo(int o, int p)
{
    ora = o;
    perc = p;
}

void Ido::addPerc(int p)
{
    p += perc;
    ora += (p / 60);
    perc = (p % 60);
}

void Ido::addOra(int o)
{
    ora = (ora + o) % 24;
}

bool Ido::operator==(const Ido &other) const
{
    return (other.getOra() == ora && other.getPerc() == perc);
}

bool Ido::operator!=(const Ido &other) const
{
    return !(*this == other);
}

void Ido::write(std::ostream &os) const
{
    os << ora << ' ' << perc << '\n';
}

void Ido::kiir(std::ostream &os) const
{
    os << (ora > 9 ? "" : "0") << ora << ':' << (perc > 9 ? "" : "0") << perc << '\n';
}

void Ido::read(std::istream &is)
{
    is >> ora >> perc;
    is.ignore();
}
