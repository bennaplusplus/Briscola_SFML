#include <iostream>
#include "PC_player.hpp"

// ============================
//  Setter
// ============================

void PC_player::SetIndiceCartaScelta(Carta const& carta_scartata_PC)
{
    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (carta_scartata_PC == m_carte_in_mano[i])
        {
            m_carta_scelta = i;
        }
    }

#if _DEBUG
    std::cout
        << "carta scarta dal PC: "
        << m_carte_in_mano[m_carta_scelta].m_nome << " "
        << m_carte_in_mano[m_carta_scelta].m_seme << std::endl;
#endif

    m_carte_in_mano[m_carta_scelta].m_is_in_gioco = false;
}

// ============================
//  Getter
// ============================

Carta PC_player::GetBriscolaPiùBassa()
{
    Carta briscola_piu_bassa;
    briscola_piu_bassa.m_valore = -1;

    int massimo = std::numeric_limits<int>::max();

    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (m_carte_in_mano[i].m_is_briscola &&
            m_carte_in_mano[i].m_valore < massimo)
        {
            massimo = m_carte_in_mano[i].m_valore;
            briscola_piu_bassa = m_carte_in_mano[i];
        }
    }

    return briscola_piu_bassa;
}

Carta PC_player::GetBriscolaPiùAlta()
{
    Carta briscola_piu_alta;
    briscola_piu_alta.m_valore = -1;
    briscola_piu_alta.m_nome_int = -1;

    int minimo = std::numeric_limits<int>::min();

    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (m_carte_in_mano[i].m_is_briscola &&
            m_carte_in_mano[i].m_valore > minimo)
        {
            minimo = m_carte_in_mano[i].m_valore;
            briscola_piu_alta = m_carte_in_mano[i];
        }
    }

    return briscola_piu_alta;
}

Carta PC_player::GetCartaPiùBassaNonBriscola()
{
    Carta carta_più_bassa_non_briscola;
    carta_più_bassa_non_briscola.m_valore = -1;

    int massimo = std::numeric_limits<int>::max();

    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (!m_carte_in_mano[i].m_is_briscola &&
            m_carte_in_mano[i].m_valore < massimo)
        {
            massimo = m_carte_in_mano[i].m_valore;
            carta_più_bassa_non_briscola = m_carte_in_mano[i];
        }
    }

    return carta_più_bassa_non_briscola;
}

Carta PC_player::GetCartaPiùAltaNonBriscola()
{
    Carta carta_più_alta_non_briscola;
    carta_più_alta_non_briscola.m_valore = -1;

    int minimo = std::numeric_limits<int>::min();

    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (!m_carte_in_mano[i].m_is_briscola &&
            m_carte_in_mano[i].m_valore > minimo)
        {
            minimo = m_carte_in_mano[i].m_valore;
            carta_più_alta_non_briscola = m_carte_in_mano[i];
        }
    }

    return carta_più_alta_non_briscola;
}

Carta PC_player::GetCartaPiùAltaSemeSpecifico(const std::string& seme)
{
    Carta carta_piu_alta;
    carta_piu_alta.m_valore = -1;
    carta_piu_alta.m_nome_int = -1;

    int valore_massimo = std::numeric_limits<int>::min();

    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (m_carte_in_mano[i].m_seme == seme &&
            m_carte_in_mano[i].m_valore > valore_massimo)
        {
            carta_piu_alta = m_carte_in_mano[i];
            valore_massimo = m_carte_in_mano[i].m_valore;
        }
    }

    return carta_piu_alta;
}

Carta PC_player::GetCartaPiùBassaSemeSpecifico(const std::string& seme)
{
    Carta carta_piu_bassa;
    carta_piu_bassa.m_valore = -1;

    int valore_minimo = std::numeric_limits<int>::max();

    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (m_carte_in_mano[i].m_seme == seme &&
            m_carte_in_mano[i].m_valore < valore_minimo)
        {
            carta_piu_bassa = m_carte_in_mano[i];
            valore_minimo = m_carte_in_mano[i].m_valore;
        }
    }

    return carta_piu_bassa;
}

// ============================
//  Altri metodi
// ============================

void PC_player::MinimizzaPresaGiocatore()
{
    int minimo_valore = std::numeric_limits<int>::max();

    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (m_carte_in_mano[i].m_valore < minimo_valore)
        {
            minimo_valore = m_carte_in_mano[i].m_valore;
            m_carta_scelta = i;
        }
    }

#if _DEBUG
    std::cout
        << "carta scarta dal PC: "
        << m_carte_in_mano[m_carta_scelta].m_nome << " "
        << m_carte_in_mano[m_carta_scelta].m_seme << std::endl;
#endif

    m_carte_in_mano[m_carta_scelta].m_is_in_gioco = false;
}

void PC_player::MossaPC(std::vector<Carta> const& carte_giocatore)
{
    if (GetIfToccaAlGiocatoreScartarePerPrimo())
    {
        MinimizzaPresaGiocatore();
    }
    else // il pc deve rispondere alla mia carta scartata
    {
        // devo prima capire quale carta ho tirato
        Carta carta_scartata_giocatore;
        Carta carta_scartata_PC;

        // cerco la carta che il giocatore ha scartato
        for (int i = 0; i < m_carte_in_mano.size(); i++)
        {
            if (carte_giocatore[i].m_is_in_gioco == false)
            {
                carta_scartata_giocatore = carte_giocatore[i];
                break;
            }
        }

        // TODO: se la briscola è coppe, e io scarto un re di denari e il PC ha una briscola "non vestita"
        // tanto vale che il PC prenda

        // carta più alta che il PC ha dello stesso m_seme
        Carta carta_piu_alta_seme_PC = GetCartaPiùAltaSemeSpecifico(carta_scartata_giocatore.m_seme);

        Carta briscola_piu_alta = GetBriscolaPiùAlta();

        ///////////////////////////////////////////////////////////////////
        // in questa situazione il PC ha una carta più alta dello stesso m_seme, quindi prende il PC
        if (carta_piu_alta_seme_PC.m_valore >= carta_scartata_giocatore.m_valore &&
            carta_piu_alta_seme_PC.m_valore != -1)
        {
            SetIndiceCartaScelta(carta_piu_alta_seme_PC);
        }
        ///////////////////////////////////////////////////////////////////
        // carta dello stesso m_seme ma m_valore più basso o uguale, prende il giocatore
        else if (carta_piu_alta_seme_PC.m_valore < carta_scartata_giocatore.m_valore &&
            carta_piu_alta_seme_PC.m_valore != -1)
        {
            // se la carta che il PC ha dello stesso m_seme ha m_valore 0 allora il PC tira quella
            if (carta_piu_alta_seme_PC.m_valore == 0)
            {
                SetIndiceCartaScelta(carta_piu_alta_seme_PC);
            }
            else // altrimenti tira quella con il punteggio più basso
            {
                MinimizzaPresaGiocatore();
            }
        }
        ///////////////////////////////////////////////////////////////////
        // il pc non ha una carta dello stesso m_seme che ho tirato
        else if (carta_piu_alta_seme_PC.m_valore == -1)
        {
            // ho scartato una carta che vale punti ma non di briscola,
            // e se il PC ha briscola, tira quella più alta
            if (briscola_piu_alta.m_valore >= 0 &&
                carta_scartata_giocatore.m_valore > 0 &&
                !carta_scartata_giocatore.m_is_briscola)
            {
                SetIndiceCartaScelta(briscola_piu_alta);
            }
            else if (carta_scartata_giocatore.m_valore == 0)
            {
                MinimizzaPresaGiocatore();
            }
            else
            {
                MinimizzaPresaGiocatore();
            }
        }
    }
}
