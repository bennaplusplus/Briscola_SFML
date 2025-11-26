#pragma once

#include "Giocatore/Giocatore.hpp"

class PC_player : public Giocatore
{

public:

    // ============================
    //  Setter
    // ============================

    void SetIndiceCartaScelta(Carta const&);

    // ============================
    //  Getter
    // ============================

    Carta GetBriscolaPiùBassa();
    Carta GetBriscolaPiùAlta();
    Carta GetCartaPiùBassaNonBriscola();
    Carta GetCartaPiùAltaNonBriscola();
    Carta GetCartaPiùAltaSemeSpecifico(const std::string&);
    Carta GetCartaPiùBassaSemeSpecifico(const std::string&);

    // ============================
    //  Altri metodi
    // ============================

    void MossaPC(std::vector<Carta> const& carte_giocatore);
    void MinimizzaPresaGiocatore();
};
