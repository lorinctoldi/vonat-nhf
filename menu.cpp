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

void printMenu()
{
    std::cout << "Menupontok:\n"
                 "(1) Jegykiadas\n"
                 "(2) Vonat felvetel\n"
                 "(3) Vonat torles\n"
                 "(4) Adatok mentese\n"
                 "(5) Adatok betoltese\n"
                 "(6) Menetrend lekerdezes\n"
                 "(7) Kilepes\n";
}

void createJegy(Menetrend &m) {
    std::string indulo, erkezo;
    int ora, perc;
    double discountOrFee;
    std::string tipus;

    // Read in the information from the user
    std::cout << "Kérem adja meg az induló állomás nevét: ";
    std::cin >> indulo;

    std::cout << "Kérem adja meg az érkező állomás nevét: ";
    std::cin >> erkezo;

    std::cout << "Kérem adja meg az indulási orat: ";
    std::cin >> ora;
    std::cin.ignore();

    std::cout << "Kérem adja meg az indulási percet: ";
    std::cin >> perc;
    std::cin.ignore();

    char choice;
    std::cout << "Első osztályú jegy? (I/N): ";
    std::cin >> choice;

    if (std::toupper(choice) == 'I') {
        std::cout << "Kérem adja meg a jegy dijanak felarat tizedes formatumban: ";
        std::cin >> discountOrFee;

        std::cout << "Kérem adja meg a jegy típusának nevet (opcionális): ";
        std::cin.ignore();
        std::getline(std::cin, tipus);
    }

    if (std::toupper(choice) != 'I') {
        std::cout << "Kedvezmenyes jegy? (I/N): ";
        std::cin >> choice;
        if(std::toupper(choice) == 'I') {
            std::cout << "Kérem adja meg a kedvezmeny merteket tizedes formatumban: ";
            std::cin >> discountOrFee;
                    std::cin.ignore();

            std::cout << "Kérem adja meg a jegy típusának nevet (opcionális): ";
            std::getline(std::cin, tipus);
        }
    }


    // Call the Menetrend::createJegy method with the provided information
    try {
        if(std::toupper(choice) == 'I')
            m.createJegy(indulo, erkezo, ora, perc, discountOrFee, tipus);
        else
            m.createJegy(indulo, erkezo, ora, perc);
    } catch (const char* msg) {
        std::cerr << "Hiba: " << msg << std::endl;
    }
}

void addVonat(Menetrend &m)
{
    Vonat v;
    std::cout << "1) Kocsik száma: ";
    int kocsikSzama;
    std::cin >> kocsikSzama;

    if (std::cin.fail() || kocsikSzama <= 0)
    {
        std::cout << "Érvénytelen bemenet. Kérem adjon meg egy pozitív egész számot.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    for (int i = 0; i < kocsikSzama; ++i)
    {
        std::cout << "2) Kocsi " << (i + 1) << " helyek száma: ";
        int helyekSzama;
        std::cin >> helyekSzama;

        if (std::cin.fail() || helyekSzama <= 0)
        {
            std::cout << "Érvénytelen bemenet. Kérem adjon meg egy pozitív egész számot.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        v.createKocsi(helyekSzama);
    }

    Utvonal utvonal;

    std::cout << "3) Allomasok szama: ";
    int allomasokSzama;
    std::cin >> allomasokSzama;

    if (std::cin.fail() || allomasokSzama <= 1)
    {
        std::cout << "Érvénytelen bemenet. Kérem adjon meg egy pozitív egész számot.\n";
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

        std::cout << "  Allomas " << (i + 1) << " érkezése (óra perc): ";
        std::cin >> erkezesOra >> erkezesPerc;

        std::cout << "  Allomas " << (i + 1) << " indulása (óra perc): ";
        std::cin >> indulasOra >> indulasPerc;

        if (std::cin.fail())
        {
            std::cout << "Érvénytelen bemenet. Kérem adjon meg érvényes óra és perc értékeket.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        utvonal.createAllomas(allomasNev, indulasOra, indulasPerc, erkezesOra, erkezesPerc);
    }
    v.setUtvonal(utvonal);

    m.addVonat(v);

    std::cout << "Vonat sikeresen hozzáadva a menetrendhez.\n";
}

void deleteVonat(Menetrend &m)
{
    std::cout << "Válasszon a törölni kívánt vonatok közül (1-" << m.getVonatokSzama() << "): ";

    int choice;
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > m.getVonatokSzama())
    {
        std::cout << "Érvénytelen választás. Kérem adjon meg egy érvényes számot.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    m.removeVonat(choice - 1);

    std::cout << "A kiválasztott vonat sikeresen törölve lett a menetrendből.\n";
}

void querySchedule(Menetrend &m) {
    std::string indulo, erkezo;

    std::cout << "Kérjük adja meg az indulási állomást (üresen hagyva az összeset megjeleníti): ";
    std::cin.ignore();
    std::getline(std::cin, indulo);
    if (indulo.empty()) {
        indulo = ""; 
    }

    std::cout << "Kérjük adja meg az érkezési állomást (üresen hagyva az összeset megjeleníti): ";
    std::getline(std::cin, erkezo);
    if (erkezo.empty()) {
        erkezo = "";  
    }

    std::cout << "\nMenetrend:\n";
    m.kiir(std::cout, indulo, erkezo);
}

void saveToFile(Menetrend &m) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string fileName;
    std::cout << "Kérem adja meg a fájl nevét: ";
    std::getline(std::cin, fileName);

    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        m.write(outputFile);
        std::cout << "Adatok sikeresen mentve a(z) " << fileName << " fájlba.\n";
    } else {
        std::cerr << "Hiba: A fájl nem nyitható meg.\n";
    }
}

void loadDataFromFile(Menetrend &m) {
    std::string fileName;

    // Clear the input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Kérem adja meg a fájl nevét: ";
    std::getline(std::cin, fileName);

    m.clear();

    std::ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        m.read(inputFile);
        std::cout << "Adatok sikeresen betöltve a menetrendbe a(z) " << fileName << " fájlból.\n";
    } else {
        std::cerr << "Hiba: A fájl nem nyitható meg.\n";
    }
}

int main()
{
    Menetrend m;
    bool exitMenu = false;

    while (!exitMenu)
    {
        printMenu();
        std::cout << "Valasszon egy menupontot (1-7): ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "Érvénytelen input. Kérem adjon meg egy számot!\n";
            std::cin.clear();
            std::cin.ignore();
            continue;
        }

        switch (choice)
        {
        case 1:
            std::cout << "Jegykiadás menüpont kiválasztva.\n";
            createJegy(m);
            break;
        case 2:
            std::cout << "Vonat felvétel menüpont kiválasztva.\n";
            addVonat(m);
            break;
        case 3:
            std::cout << "Vonat törlés menüpont kiválasztva.\n";
            deleteVonat(m);
            break;
        case 4:
            std::cout << "Adatok mentése menüpont kiválasztva.\n";
            saveToFile(m);
            break;
        case 5:
            std::cout << "Adatok betöltése menüpont kiválasztva.\n";
            loadDataFromFile(m);
            break;
        case 6:
            std::cout << "Menetrend lekérdezés menüpont kiválasztva.\n";
            querySchedule(m);
            break;
        case 7:
            std::cout << "Kilépés.\n";
            exitMenu = true;
            break;
        default:
            std::cout << "Érvénytelen menüpont.\n";
            break;
        }
    }

    return 0;
}