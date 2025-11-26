#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Mazzo/Carta.hpp"
#include "Giocatore/Giocatore.hpp"
#include "PC_player/PC_player.hpp"

class Mazzo
{
private:

    // vettore contenente tutte e 40 le carte
    std::vector<Carta> m_mazzo;

    // vettore contenente i 4 semi
    const std::vector<std::string> m_semi{
        "bastoni", "coppe", "denari", "spade"
    };

    // vettore contenente le 10 carte per ogni seme
    const std::vector<std::string> m_nomi{
        "due", "quattro", "cinque", "sei", "sette",
        "fante", "cavallo", "re", "tre", "asso"
    };

    // nomi in formato decimale delle carte
    const std::vector<unsigned int> m_nomi_int{
        2, 4, 5, 6, 7, 8, 9, 10, 3, 11
    };

    // valori delle carte
    const std::vector<unsigned int> m_valori{
        0, 0, 0, 0, 0, 2, 3, 4, 10, 11
    };

    // numero della mano corrente
    unsigned int m_mano;

    // indice della prossima carta nel mazzo
    unsigned m_prossima_carta;

    // la briscola che compare sul campo di gioco
    Carta m_briscola;

public:

    // costruttore
    Mazzo();

    // setter
    void SetBriscola();

    // getter
    Carta GetBriscola() const;
    unsigned int& GetMano();
    const unsigned int& GetMano() const;

    // altri metodi
    void CreaMazzo();
    void DisplayMazzo() const;
    void MischiaMazzo();
    void UpdateMano();
    void DistribuisciCarte(Giocatore&, PC_player&);
    int ContaCarteRimaste() const;
    void RimuoviCarteDalMazzo(int);
    void RimuoviCartaDalleCarteGiocatore(Giocatore&);
};
