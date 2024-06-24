#include "HexPlansza.h"
#include <string>
#include <iostream>
#include <vector>

HexPlansza::HexPlansza()
    : rozmiarPlanszy(0), punktX(0), punktY(0), pionkiCzerwone(0), pionkiNiebieskie(0)
{
}


void HexPlansza::wyczysc()
{
    punktX = 0;
    punktY = 0;
    rozmiarPlanszy = 0;
    pionkiCzerwone = 0;
    pionkiNiebieskie = 0;
}

void HexPlansza::zapiszPlansze(const std::string& linia)
{
    char pionek = ' ';
    int x = punktX, y = punktY;
    int maksymalnyIndex = rozmiarPlanszy - 1;

    for (int i = 0; i < linia.length(); i++) {
        if (linia[i] == '<') {
            pionek = linia[i + 2];
            plansza[x][y] = pionek;

            if (pionek == 'r') {
                pionkiCzerwone++;
            }
            else if (pionek == 'b') {
                pionkiNiebieskie++;
            }

            y--;
            x++;
        }
    }

    if (punktY < maksymalnyIndex) {
        punktY++;
    }
    else if (punktX < maksymalnyIndex) {
        punktX++;
    }
}

void HexPlansza::wypiszRozmiarPlanszy()
{
    printf("%d\n", rozmiarPlanszy);
}


void HexPlansza::wypiszPlansze()
{

    std::cout << "rozmiarPlanszy = " << rozmiarPlanszy << std::endl;

    for (int i = 0; i < rozmiarPlanszy; i++) {

        for (int j = 0; j < rozmiarPlanszy; j++) {

            std::cout << plansza[i][j] << " ";
        }

        printf("\n");

    }

}

void HexPlansza::wypiszIloscPionow()
{
    printf("%d\n", (pionkiCzerwone + pionkiNiebieskie) );

}

void HexPlansza::wypiszCzyPoprawna()
{
    if (pionkiCzerwone == pionkiNiebieskie + 1 || pionkiCzerwone == pionkiNiebieskie) {

        printf("YES\n");
    }
    else {

        printf("NO\n");
    }

}

int HexPlansza::obliczRozmiar(const std::string& linia)
{
    for (int i = 0; i < linia.length(); i++) {

        if (linia[i] == ' ') {

            rozmiarPlanszy++;
        }
        else {

            break;
        }
    }

    rozmiarPlanszy = (rozmiarPlanszy + 2) / 3;

    return (rozmiarPlanszy*2);
}

int HexPlansza::czyGameOver()
{
    if (pionkiCzerwone == pionkiNiebieskie + 1 || pionkiCzerwone == pionkiNiebieskie) {
        bool stanGry = false;

        // Sprawdzenie wygranej dla czerwonych
        for (int i = 0; i < rozmiarPlanszy; i++) {
            if (plansza[0][i] == 'r') {
                stanGry = visitRooms(0, i, 'r');
                if (stanGry) return 3;
            }
        }

        // Sprawdzenie wygranej dla niebieskich
        for (int i = 0; i < rozmiarPlanszy; i++) {
            if (plansza[i][0] == 'b') {
                stanGry = visitRooms(i, 0, 'b');
                if (stanGry) return 2;
            }
        }

        return 1; //Poprawna iloœæ pionków, ale nikt nie wygra³
    }
    else {
        return 0; //Niepoprawna iloœæ pionków
    }
}

void HexPlansza::wypiszCzyGameOver()
{

    int czyKoniecGry = czyGameOver();

    if (czyKoniecGry == 3) {
        printf("YES RED\n");
    }
    else if (czyKoniecGry == 2) {
        printf("YES BLUE\n");
    }
    else {
        printf("NO\n");
    }

}

int HexPlansza::isBoardPossible() {

    int czyKoniec = czyGameOver();

    if (czyKoniec == 3 && pionkiCzerwone == pionkiNiebieskie + 1) {
        if (czyZawszeWygrywa('r')) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (czyKoniec == 2 && pionkiCzerwone == pionkiNiebieskie) {
        if (czyZawszeWygrywa('b')) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        if (czyKoniec == 1) {
            return 2;
        }
        else {
            return 0;
        }    
    }
}

void HexPlansza::wypiszCzyIsBoardPossible()
{
    int czyPlanszJestMozliwa = isBoardPossible();

    if (czyPlanszJestMozliwa) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }

}

void HexPlansza::winWithNaiveOpponent()
{
    int czyPlanszJestMozliwa = czyGameOver();
    int minBlue1 = 0, minRed1 = 0, minBlue2 = 0, minRed2 = 0;
    int wolneMiejsca = ((rozmiarPlanszy * rozmiarPlanszy) - pionkiCzerwone - pionkiNiebieskie);

    if (czyPlanszJestMozliwa == 1) {

        if (pionkiNiebieskie == pionkiCzerwone) {
        
            minBlue1 = 2;
            minRed1 = 1;
            minBlue2 = 4;
            minRed2 = 3;
        
        }
        else {
        
            minBlue1 = 1;
            minRed1 = 2;
            minBlue2 = 3;
            minRed2 = 4;
            
        }

        if (minRed1 <= wolneMiejsca && czyMozeWygrac(0, 'r')) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }

        if (minBlue1 <= wolneMiejsca && czyMozeWygrac(0, 'b')) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }

        if (minRed2 <= wolneMiejsca && czyMozeWygrac(1, 'r')) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }

        if (minBlue2 <= wolneMiejsca && czyMozeWygrac(1, 'b')) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }

    }
    else {
        printf("NO\n");
        printf("NO\n");
        printf("NO\n");
        printf("NO\n");
    }
    

}

bool HexPlansza::czyMozeWygrac(int ruch, char gracz)
{

    bool moliwoscWygrania = true;

    for (int i = 0; i < rozmiarPlanszy; i++) {
        for (int j = 0; j < rozmiarPlanszy; j++) {

            moliwoscWygrania = true;

            if (plansza[i][j] == ' ') {
                plansza[i][j] = gracz;

                if (visitRooms(i, j, gracz)) {
                    plansza[i][j] = ' ';
                    if (ruch) {
                        moliwoscWygrania = false;
                    }
                    else {
                        return true;
                    } 
                }

                if (ruch && moliwoscWygrania) {
                    for (int k = 0; k < rozmiarPlanszy; k++) {
                        for (int m = 0; m < rozmiarPlanszy; m++) {
                            if (plansza[k][m] == ' ') {
                                plansza[k][m] = gracz; 

                                if (visitRooms(k, m, gracz)) {
                                    plansza[k][m] = ' '; 
                                    plansza[i][j] = ' '; 
                                    return true; 
                                }

                                plansza[k][m] = ' '; 
                            }
                        }
                    }
                }

                plansza[i][j] = ' '; 
            }
        }
    }
    return false; 
}


bool HexPlansza::czyZawszeWygrywa(char gracz) {
    for (int i = 0; i < rozmiarPlanszy; i++) {
        for (int j = 0; j < rozmiarPlanszy; j++) {
            if (plansza[i][j] == gracz) {

                plansza[i][j] = ' ';

                bool wygrana = false;

                if (gracz == 'r') {
                    for (int k = 0; k < rozmiarPlanszy; k++) {
                        if (plansza[0][k] == 'r') {
                            if (visitRooms(0, k, 'r')) {
                                wygrana = true;
                                break;
                            }
                        }
                    }
                }
                else if (gracz == 'b') {
                    for (int k = 0; k < rozmiarPlanszy; k++) {
                        if (plansza[k][0] == 'b') {
                            if (visitRooms(k, 0, 'b')) {
                                wygrana = true;
                                break;
                            }
                        }
                    }
                }

                plansza[i][j] = gracz;

                if (!wygrana) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool HexPlansza::visitRooms(int x, int y, char gracz)
{
    std::vector<Punkt> stos;
    bool czyOdwiedzone[11][11] = { false };
    int index = 0;
    bool krawedz1 = false, krawedz2 = false;


    stos.push_back(Punkt(x, y));

    while (index < stos.size()) {
        Punkt obecny = stos[index];
        index ++;

        if (!czyOdwiedzone[obecny.x][obecny.y]) {
            czyOdwiedzone[obecny.x][obecny.y] = true;

            if ((plansza[obecny.x][obecny.y] == 'r' && obecny.x == (rozmiarPlanszy - 1)) ||
                (plansza[obecny.x][obecny.y] == 'b' && obecny.y == (rozmiarPlanszy - 1))) {
                krawedz2 = true;
            }


            if ((plansza[obecny.x][obecny.y] == 'r' && obecny.x == 0) ||
                (plansza[obecny.x][obecny.y] == 'b' && obecny.y == 0)) {
                krawedz1 = true;
            }

            if (krawedz1 && krawedz2) {
                return true;
            
            }

            std::vector<Punkt> sasiedzi = get_neighbours(obecny.x, obecny.y);

            for (const Punkt& sasiad : sasiedzi) {
                if (plansza[sasiad.x][sasiad.y] == gracz) {
                    stos.push_back(sasiad);
                }
            }
        }
    }

    return false;
}

std::vector<HexPlansza::Punkt> HexPlansza::get_neighbours(int x, int y)
{
    static const int przesuniecia[6][2] = { {0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}, {-1, -1} };
    std::vector<Punkt> neighbours;
    //neighbours.reserve(6);

    for (int i = 0; i < 6; ++i) {
        int x2 = x + przesuniecia[i][0];
        int y2 = y + przesuniecia[i][1];
        if (x2 >= 0 && x2 < rozmiarPlanszy && y2 >= 0 && y2 < rozmiarPlanszy) {
            neighbours.push_back(Punkt(x2, y2));
        }
    }

    return neighbours;
}


HexPlansza::~HexPlansza()
{
}
