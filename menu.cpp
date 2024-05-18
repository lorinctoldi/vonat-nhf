#include "menetrend.h"
#include "vonat.h"
#include "jegy.h"
#include "utvonal.h"
#include "ido.h"
#include "allomas.h"
#include "kocsi.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "memtrace.h"

void createJegy(Menetrend &m)
{
    if(m.getVonatokSzama() < 1) throw "Nincsen vonat";
    std::string indulo, erkezo;
    int ora, perc;
    double discountOrFee;
    std::string tipus;

    std::cout << "Kerem adja meg az indulo allomas nevet: ";
    std::cin >> indulo;

    std::cout << "Kerem adja meg az erkező allomas nevet: ";
    std::cin >> erkezo;

    std::cout << "Kerem adja meg az indulasi orat: ";
    std::cin >> ora;
    std::cin.ignore();

    std::cout << "Kerem adja meg az indulasi percet: ";
    std::cin >> perc;
    std::cin.ignore();

    char choice;
    std::cout << "Első osztalyú jegy? (I/N): ";
    std::cin >> choice;

    if (std::toupper(choice) == 'I')
    {
        std::cout << "Kerem adja meg a jegy dijanak felarat tizedes formatumban: ";
        std::cin >> discountOrFee;

        std::cout << "Kerem adja meg a jegy típusanak nevet (opcionalis): ";
        std::cin.ignore();
        std::getline(std::cin, tipus);
    }

    if (std::toupper(choice) != 'I')
    {
        std::cout << "Kedvezmenyes jegy? (I/N): ";
        std::cin >> choice;
        if (std::toupper(choice) == 'I')
        {
            std::cout << "Kerem adja meg a kedvezmeny merteket tizedes formatumban: ";
            std::cin >> discountOrFee;
            std::cin.ignore();

            std::cout << "Kerem adja meg a jegy típusanak nevet (opcionalis): ";
            std::getline(std::cin, tipus);
        }
    }

    try
    {
        if (std::toupper(choice) == 'I')
            m.createJegy(indulo, erkezo, ora, perc, discountOrFee, tipus);
        else
            m.createJegy(indulo, erkezo, ora, perc);
    }
    catch (const char *msg)
    {
        std::cerr << "Hiba: " << msg << std::endl;
    }
}

void vonatFelvete(Menetrend &m)
{
    m.createVonat();
    std::cout << "1) Kocsik szama: ";
    int kocsikSzama;
    std::cin >> kocsikSzama;

    if (std::cin.fail() || kocsikSzama <= 0)
    {
        std::cout << "ervenytelen bemenet. Kerem adjon meg egy pozitív egesz szamot.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    for (int i = 0; i < kocsikSzama; ++i)
    {
        std::cout << "2) Kocsi " << (i + 1) << " helyek szama: ";
        int helyekSzama;
        std::cin >> helyekSzama;

        if (std::cin.fail() || helyekSzama <= 0)
        {
            std::cout << "ervenytelen bemenet. Kerem adjon meg egy pozitív egesz szamot.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        m.getVonat(m.getVonatokSzama() - 1).createKocsi(helyekSzama);
    }

    Utvonal utvonal;

    std::cout << "3) Allomasok szama: ";
    int allomasokSzama;
    std::cin >> allomasokSzama;

    if (std::cin.fail() || allomasokSzama <= 1)
    {
        std::cout << "ervenytelen bemenet. Kerem adjon meg egy pozitív egesz szamot.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    for (int i = 0; i < allomasokSzama; ++i)
    {
        std::string allomasNev;
        int indulasOra, indulasPerc, erkezesOra, erkezesPerc;

        std::cout << "  Allomas " << (i + 1) << " neve: ";
        std::cin >> allomasNev;

        std::cout << "  Allomas " << (i + 1) << " erkezese (ora perc): ";
        std::cin >> erkezesOra >> erkezesPerc;

        std::cout << "  Allomas " << (i + 1) << " indulasa (ora perc): ";
        std::cin >> indulasOra >> indulasPerc;

        if (std::cin.fail())
        {
            std::cout << "ervenytelen bemenet. Kerem adjon meg ervenyes ora es perc ertekeket.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        utvonal.createAllomas(allomasNev, indulasOra, indulasPerc, erkezesOra, erkezesPerc);
    }
    m.getVonat(m.getVonatokSzama() - 1).setUtvonal(utvonal);

    std::cout << "Vonat sikeresen hozzaadva a menetrendhez.\n";
}

void vonatTorlese(Menetrend &m)
{
    std::cout << "Valasszon a torolni kívant vonatok kozul (1-" << m.getVonatokSzama() << "): ";

    int choice;
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > m.getVonatokSzama())
    {
        std::cout << "ervenytelen valasztas. Kerem adjon meg egy ervenyes szamot.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    m.removeVonat(choice - 1);

    std::cout << "A kivalasztott vonat sikeresen torolve lett a menetrendből.\n";
}

void menetrendLekerdezes(Menetrend &m)
{
    std::string indulo, erkezo;

    std::cout << "Kerjuk adja meg az indulasi allomast (uresen hagyva az osszeset megjeleníti): ";
    std::cin.ignore();
    std::getline(std::cin, indulo);
    if (indulo.empty())
    {
        indulo = "";
    }

    std::cout << "Kerjuk adja meg az erkezesi allomast (uresen hagyva az osszeset megjeleníti): ";
    std::getline(std::cin, erkezo);
    if (erkezo.empty())
    {
        erkezo = "";
    }

    std::cout << "\nMenetrend:\n";
    m.kiir(std::cout, indulo, erkezo);
}

void adatMenteseFileba(Menetrend &m)
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string fileName;
    std::cout << "Kerem adja meg a fajl nevet: ";
    std::getline(std::cin, fileName);

    std::ofstream outputFile(fileName);
    if (outputFile.is_open())
    {
        m.write(outputFile);
        std::cout << "Adatok sikeresen mentve a(z) " << fileName << " fajlba.\n";
    }
    else
    {
        std::cerr << "Hiba: A fajl nem nyithato meg.\n";
    }
}

void adatBetolteseFilebol(Menetrend &m)
{
    std::string fileName;

    // Clear the input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Kerem adja meg a fajl nevet: ";
    std::getline(std::cin, fileName);

    m.clear();

    std::ifstream inputFile(fileName);
    if (inputFile.is_open())
    {
        m.read(inputFile);
        std::cout << "Adatok sikeresen betoltve a menetrendbe a(z) " << fileName << " fajlbol.\n";
    }
    else
    {
        std::cerr << "Hiba: A fajl nem nyithato meg.\n";
    }
}

int main()
{
    try {
        Menetrend m;
        bool kilepes = false;

        while (!kilepes) {
            std::cout << "Menupontok:\n"
                      << "(1) Jegykiadas\n"
                      << "(2) Vonat felvetel\n"
                      << "(3) Vonat torles\n"
                      << "(4) Adatok mentese\n"
                      << "(5) Adatok betoltese\n"
                      << "(6) Menetrend lekerdezes\n"
                      << "(7) Kilepes\n"
                      << "Valasszon egy menupontot (1-7): ";

            int valasztas;
            std::cin >> valasztas;

            if (std::cin.fail()) {
                std::cout << "Ervenytelen input. Kerem adjon meg egy szamot 1 es 7 kozott!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            switch (valasztas) {
            case 1:
                std::cout << "Jegykiadas menupont kivalasztva.\n";
                createJegy(m);
                break;
            case 2:
                std::cout << "Vonat felvetel menupont kivalasztva.\n";
                vonatFelvete(m);
                break;
            case 3:
                std::cout << "Vonat torles menupont kivalasztva.\n";
                vonatTorlese(m);
                break;
            case 4:
                std::cout << "Adatok mentese menupont kivalasztva.\n";
                adatMenteseFileba(m);
                break;
            case 5:
                std::cout << "Adatok betoltese menupont kivalasztva.\n";
                adatBetolteseFilebol(m);
                break;
            case 6:
                std::cout << "Menetrend lekerdezes menupont kivalasztva.\n";
                menetrendLekerdezes(m);
                break;
            case 7:
                std::cout << "Kilepes.\n";
                kilepes = true;
                break;
            default:
                std::cout << "Ervenytelen menupont.\n";
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Kivetel tortent: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "Ismeretlen kivetel tortent.\n";
    }

    return 0;
}