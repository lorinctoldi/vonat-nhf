#ifndef JEGY_HPP
#define JEGY_HPP

class Jegy {
protected:
    size_t jegy_azonosito;
    size_t helyszam;
    size_t kocsi_szam;
    size_t vonat_szam;
    int ar;
public:
    Jegy();
    Jegy(const Jegy& other);
    Jegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, int price): jegy_azonosito(azonosito), helyszam(hely), kocsi_szam(kocsi), vonat_szam(vonat) { };
    virtual void setAr(int price);
    virtual ~Jegy();
public:
    Jegy& operator=(const Jegy& other);
    bool operator==(const Jegy& other) const;
    bool operator!=(const Jegy& other) const;
};

class ElsoOsztalyJegy : public Jegy {
private:
    std::string tipus;
public:
    ElsoOsztalyJegy();
    ElsoOsztalyJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, int price);
    void setAr(int price);
    ~ElsoOsztalyJegy();
};

class MasodOsztalyJegy : public Jegy {
private:
    std::string tipus;
public:
    MasodOsztalyJegy();
    MasodOsztalyJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, int price);
    void setAr(int price);
    ~MasodOsztalyJegy();
};

class DiakJegy : public Jegy {
private:
    std::string tipus;
public:
    DiakJegy();
    DiakJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, int price);
    void setAr(int price);
    ~DiakJegy();
};

class NyugdijasJegy : public Jegy {
private:
    std::string tipus;
public:
    NyugdijasJegy();
    NyugdijasJegy(size_t azonosito, size_t hely, size_t kocsi, size_t vonat, int price);
    void setAr(int price);
    ~NyugdijasJegy();
};

#endif // JEGY_HPP
