#pragma once
#include <string>
#include <list>
#include "HexPlansza.h"

void wczytanie() {
    HexPlansza plansza;
    std::string linia;
    std::string zapytanie;
    std::list<std::string> linieLista;
    bool czyPierwszaLinia = true;

    while (true) {

        if (std::cin.eof()) {
            break;
        }

        while (std::getline(std::cin, linia)) {

            if (linia.empty()) continue;

            if (czyPierwszaLinia) {
                plansza.obliczRozmiar(linia);
                czyPierwszaLinia = false;
                continue;
            }

            if (linia == "BOARD_SIZE" || linia == "PAWNS_NUMBER" || linia == "IS_BOARD_CORRECT" || linia == "IS_GAME_OVER" ||
                linia == "IS_BOARD_POSSIBLE" || linia == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {

                zapytanie = linia;
                czyPierwszaLinia = true;
                break;

            }
            else if (linia == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT" || linia == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT" ||
                linia == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
                continue;
            }
            else {

                linieLista.push_back(linia);
            }

        }

        if (zapytanie == "BOARD_SIZE") {

            plansza.wypiszRozmiarPlanszy();
            linieLista.clear();
            plansza.wyczysc();
            zapytanie = "";

        }
        else {

            while (!linieLista.empty()) {
                auto linia = linieLista.front();
                linieLista.pop_front();
                plansza.zapiszPlansze(linia);
            }

            //plansza.wypiszPlansze();

            if (zapytanie == "PAWNS_NUMBER") {
                plansza.wypiszIloscPionow();
                plansza.wyczysc();
            }
            else if (zapytanie == "IS_BOARD_CORRECT") {
                plansza.wypiszCzyPoprawna();
                plansza.wyczysc();
            }
            else if (zapytanie == "IS_GAME_OVER") {

                plansza.wypiszCzyGameOver();
                plansza.wyczysc();

            }
            else if (zapytanie == "IS_BOARD_POSSIBLE") {

                plansza.wypiszCzyIsBoardPossible();
                plansza.wyczysc();

            }
            else if (zapytanie == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
                plansza.winWithNaiveOpponent();
                plansza.wyczysc();
            }

            zapytanie = "";

        }

    }
}