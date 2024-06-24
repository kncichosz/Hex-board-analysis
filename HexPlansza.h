#pragma once
#include <string>
#include <vector>

class HexPlansza
{
private:
    char plansza[11][11];
    int rozmiarPlanszy;
    int punktX, punktY;
    int pionkiCzerwone;
    int pionkiNiebieskie;
    struct Punkt
    {
        int x;
        int y;

        Punkt(int x, int y) : x(x), y(y) {}
    };
public:
    HexPlansza();
    void zapiszPlansze(const std::string& linia);
    void wypiszRozmiarPlanszy();
    void wypiszPlansze();
    void wypiszIloscPionow();
    void wypiszCzyPoprawna();
    void wyczysc();
    int obliczRozmiar(const std::string& linia);
    int czyGameOver();
    void wypiszCzyGameOver();
    int isBoardPossible();
    void wypiszCzyIsBoardPossible();
    void winWithNaiveOpponent();
    bool czyMozeWygrac(int ruch, char gracz);
    bool visitRooms(int x, int y, char gracz);
    std::vector<HexPlansza::Punkt> get_neighbours(int x, int y);
    bool czyZawszeWygrywa(char gracz);
    ~HexPlansza();
};
