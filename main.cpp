#include "menetrend.h"
#include "vonat.h"
#include "jegy.h"
#include "utvonal.h"
#include "ido.h"
#include "allomas.h"
#include "kocsi.h"
#include "test.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "memtrace.h"

int main()
{
    test();
    Menetrend m;
    bool kilepes = false;

    while (!kilepes)
    {
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

        if (std::cin.eof()) break;

        if (std::cin.fail())
        {
            std::cout << "Ervenytelen input. Kerem adjon meg egy szamot 1 es 7 kozott!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (valasztas)
        {
        case 1:
            std::cout << "Jegykiadas menupont kivalasztva.\n";
            try
            {
                std::string indulo, erkezo;
                int ora, perc;
                std::string tipus;
                double discountOrFee;

                std::cout << "Kerem adja meg az indulo allomas nevet: ";
                std::cin.ignore();
                std::getline(std::cin, indulo);

                std::cout << "Kerem adja meg az erkezo allomas nevet: ";
                std::getline(std::cin, erkezo);

                std::cout << "Kerem adja meg az indulasi idopontjat (ora perc): ";
                std::cin >> ora >> perc;

                if (std::cin.fail())
                    throw "Ervenytelen bemenet. Kerem adjon meg ervenyes ora es perc ertekeket.";

                char valasztas;
                std::cout << "Elso osztalyú jegy? (I/N): ";
                std::cin >> valasztas;

                if (std::toupper(valasztas) == 'I')
                {
                    std::cout << "Kerem adja meg a jegy dijanak felarat tizedes formatumban: ";
                    std::cin >> discountOrFee;

                    std::cout << "Kerem adja meg a jegy típusanak nevet (opcionalis): ";
                    std::cin.ignore();
                    std::getline(std::cin, tipus);
                }

                if (std::toupper(valasztas) != 'I')
                {
                    std::cout << "Kedvezmenyes jegy? (I/N): ";
                    std::cin >> valasztas;
                    if (std::toupper(valasztas) == 'I')
                    {
                        std::cout << "Kerem adja meg a kedvezmeny merteket tizedes formatumban: ";
                        std::cin >> discountOrFee;
                        std::cin.ignore();

                        std::cout << "Kerem adja meg a jegy típusanak nevet (opcionalis): ";
                        std::getline(std::cin, tipus);
                    }
                }

                if (std::toupper(valasztas) == 'I')
                    m.createJegy(indulo, erkezo, ora, perc, discountOrFee, tipus);
                else
                    m.createJegy(indulo, erkezo, ora, perc);
            }
            catch (const char *msg)
            {
                std::cerr << "Hiba: " << msg << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        case 2:
            std::cout << "Vonat felvetel menupont kivalasztva.\n";
            try
            {
                Vonat v;
                std::cout << "1) Kocsik szama: ";
                int kocsikSzama;
                std::cin >> kocsikSzama;

                if (std::cin.fail() || kocsikSzama <= 0)
                    throw "Ervenytelen bemenet. Legalabb 1 kocsija kell legyen a vonatnak!";

                for (int i = 1; i <= kocsikSzama; ++i)
                {
                    std::cout << "2) Kocsi " << (i) << " helyek szama: ";
                    int helyekSzama;
                    std::cin >> helyekSzama;

                    if (std::cin.fail() || helyekSzama <= 0)
                        throw "Ervenytelen bemenet. Legalabb 1 helynek kell lennie a kocsiban!";

                    v.createKocsi(helyekSzama);
                }

                Utvonal utvonal;

                std::cout << "3) Allomasok szama: ";
                int allomasokSzama;
                std::cin >> allomasokSzama;

                if (std::cin.fail() || allomasokSzama <= 1)
                    throw "Ervenytelen bemenet. Kerem adjon meg legalabb 2 allomast!";

                for (int i = 0; i < allomasokSzama; ++i)
                {
                    std::string allomasNev;
                    int indulasOra, indulasPerc, erkezesOra, erkezesPerc;

                    std::cout << "  Allomas " << (i + 1) << " neve: ";
                    std::cin.ignore();
                    std::getline(std::cin, allomasNev);

                    std::cout << "  Vonat erkezesenek ideje " << (i + 1) << " az allomasra (ora perc): ";
                    std::cin >> erkezesOra >> erkezesPerc;

                    std::cout << "  Vonat indulasanak ideje  " << (i + 1) << " az allomasrol (ora perc): ";
                    std::cin >> indulasOra >> indulasPerc;

                    if (std::cin.fail())
                        throw "Ervenytelen bemenet. Kerem adjon meg ervenyes ora es perc ertekeket.";

                    utvonal.createAllomas(allomasNev, erkezesOra, erkezesPerc, indulasOra, indulasPerc);
                }
                v.setUtvonal(utvonal);
                m.addVonat(v);
                std::cout << "Vonat sikeresen hozzaadva a menetrendhez.\n";
            }
            catch (const char *err)
            {
                std::cerr << "Hiba: " << err << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        case 3:
            try
            {
                std::cout << "Valasszon a torolni kívant vonatok kozul (1-" << m.getVonatokSzama() << "): ";

                int valasztas;
                std::cin >> valasztas;

                if (std::cin.fail() || valasztas < 1 || valasztas > m.getVonatokSzama())
                    throw "Ervenytelen valasztas. Kerem adjon meg egy ervenyes szamot.";

                m.removeVonat(valasztas - 1);

                std::cout << "A kivalasztott vonat sikeresen torolve lett a menetrendbol.\n";
            }
            catch (const char *err)
            {
                std::cerr << "Hiba: " << err << std::endl;
            }
            break;
        case 4:
            std::cout << "Adatok mentese menupont kivalasztva.\n";
            try
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::string fileNev;
                std::cout << "Kerem adja meg a fajl nevet: ";
                std::getline(std::cin, fileNev);

                std::ofstream outputFile(fileNev);
                if (outputFile.is_open())
                {
                    m.write(outputFile);
                    std::cout << "Adatok sikeresen mentve a(z) " << fileNev << " fajlba.\n";
                }
                else
                    throw "A fajl nem nyithato meg.\n";
            }
            catch (const char *err)
            {
                std::cerr << "Hiba: " << err << std::endl;
            }
            break;
        case 5:
            try
            {
                std::cout << "Adatok betoltese menupont kivalasztva.\n";
                std::string fileNev;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Kerem adja meg a fajl nevet: ";
                std::getline(std::cin, fileNev);

                m.clear();

                std::ifstream inputFile(fileNev);
                if (inputFile.is_open())
                {
                    m.read(inputFile);
                    std::cout << "Adatok sikeresen betoltve a menetrendbe a(z) " << fileNev << " fajlbol.\n";
                }
                else
                    throw "A fajl nem nyithato meg.\n";
            }
            catch (const char *err)
            {
                std::cerr << "Hiba: " << err << std::endl;
            }
            break;
        case 6:
            std::cout << "Menetrend lekerdezes menupont kivalasztva.\n";
            try
            {
                if (m.getVonatokSzama() == 0)
                    throw "Nincsenek vonatok a rendszerben.\n";
                std::string indulo, erkezo;

                std::cout << "Kerjuk adja meg az indulasi allomast (uresen hagyva az osszeset megjeleniti): ";
                std::cin.ignore();
                std::getline(std::cin, indulo);

                std::cout << "Kerjuk adja meg az erkezesi allomast (uresen hagyva az osszeset megjeleniti): ";
                std::getline(std::cin, erkezo);

                m.kiir(std::cout, indulo, erkezo);
            }
            catch (const char *err)
            {
                std::cerr << "Hiba: " << err << std::endl;
            }
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

    return 0;
}