#pragma once

#include <iostream>
#include <vector>
#include "Mazzo/Carta.hpp"

class Giocatore
{
protected:

    // vettore contenente le carte che il giocatore ha in mano
    std::vector<Carta> m_carte_in_mano;

    // vettore contenente le carte prese durante le mani
    std::vector<Carta> m_punti_fatti;

    // punteggio finale del giocatore a fine partita
    unsigned int m_punteggio;

    // indice della carta scelta da scartare
    int m_carta_scelta;

    // booleano che se è true indica che tocca al giocatore scartare una carta
    bool m_turno_del_giocatore;

    // booleano che se è true indica che tocca al giocatore scartare una carta per primo
    bool m_giocatore_scarta_per_primo;

    // booleano che indica se il tasto del mouse è stato rilasciato almeno una volta
    bool m_is_pulsante_rilasciato;

    // vettore 2D che indica la posizione del mouse all'interno della finestra
    sf::Vector2i m_mouse_position;

    // vettore che racchiude le posizioni delle carte che il giocatore ha in mano
    std::vector<sf::FloatRect> m_bounds_carte_in_mano;

public:

    // ============================
    //  Costruttore
    // ============================

    Giocatore();

    // ============================
    //  Setter
    // ============================

    void SetCarte(int, const std::vector<Carta>&);
    void SetCarte();
    void SetToccaAlGiocatore(bool);
    void SetToccaAlGiocatoreScartarePerPrimo(bool);
    void SetMousePosition(sf::Vector2i);

    // ============================
    //  Getter
    // ============================

    int GetIndiceCartaScelta() const;
    int GetPunteggio() const;
    std::vector<Carta>& GetCarte();
    const std::vector<Carta>& GetCarte() const;
    std::vector<Carta>& GetPuntiFatti();
    const bool GetIfToccaAlGiocatore() const;
    const bool GetIfToccaAlGiocatoreScartarePerPrimo() const;
    const sf::Vector2i& GetMousePosition() const;
    std::vector<sf::FloatRect>& GetBoundsCarte();

    // ============================
    //  Altri metodi
    // ============================

    bool ScartaCarta(sf::RenderWindow&);
    void CalcolaPunteggio();
    void popolaBoundsCarte();
};
