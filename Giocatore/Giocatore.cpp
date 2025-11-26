#include "Giocatore.hpp"

Giocatore::Giocatore() :
    m_carte_in_mano(3),
    m_turno_del_giocatore{ false },
    m_punteggio{ 0 },
    m_carta_scelta{ -1 },
    m_bounds_carte_in_mano(3, sf::FloatRect()),
    m_giocatore_scarta_per_primo{ false },
    m_is_pulsante_rilasciato{ true }
{
};

// ============================
//  Setter
// ============================

void Giocatore::SetCarte(int index, const std::vector<Carta>& mazzo)
{
    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (m_carte_in_mano[i].m_is_in_gioco == false)
        {
            m_carte_in_mano[i] = mazzo[index];
            m_carte_in_mano[i].m_numero_carta = i;
            m_carte_in_mano[i].m_is_in_gioco = true;
            break;
        }
    }
}

void Giocatore::SetCarte()
{
    for (int i = 0; i < m_carte_in_mano.size(); i++)
    {
        if (m_carte_in_mano[i].m_numero_carta != i)
        {
            m_carte_in_mano[i].m_numero_carta = i;
        }
    }
}

void Giocatore::SetToccaAlGiocatore(bool value)
{
    m_turno_del_giocatore = value;
}

void Giocatore::SetToccaAlGiocatoreScartarePerPrimo(bool value)
{
    m_giocatore_scarta_per_primo = value;
}

void Giocatore::SetMousePosition(sf::Vector2i xy_position)
{
    m_mouse_position = xy_position;
}

// ============================
//  Getter
// ============================

int Giocatore::GetIndiceCartaScelta() const
{
    return m_carta_scelta;
}

int Giocatore::GetPunteggio() const
{
    return m_punteggio;
}

std::vector<Carta>& Giocatore::GetCarte()
{
    return m_carte_in_mano;
}

const std::vector<Carta>& Giocatore::GetCarte() const
{
    return m_carte_in_mano;
}

std::vector<Carta>& Giocatore::GetPuntiFatti()
{
    return m_punti_fatti;
}

const bool Giocatore::GetIfToccaAlGiocatore() const
{
    return m_turno_del_giocatore;
}

const bool Giocatore::GetIfToccaAlGiocatoreScartarePerPrimo() const
{
    return m_giocatore_scarta_per_primo;
}

const sf::Vector2i& Giocatore::GetMousePosition() const
{
    return m_mouse_position;
}

std::vector<sf::FloatRect>& Giocatore::GetBoundsCarte()
{
    return m_bounds_carte_in_mano;
}

// ============================
//  Altri metodi
// ============================

bool Giocatore::ScartaCarta(sf::RenderWindow& window)
{
    m_mouse_position = sf::Mouse::getPosition(window);

    // se clicco il pulsante SX allora is_pulsante_premuto diventa true, altrimenti è false
    bool is_pulsante_premuto = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    // questa è la condizione che sto prevenendo; nel senso che se:
    // nel frame precedente ho scelto la carta, quindi ho:
    //    - cliccato il tasto (is_pulsante_premuto = true) e di conseguenza
    //    - m_is_pulsante_rilasciato è diventato false;
    // nel frame successivo (cioè quello attuale) il PC è talmente veloce
    // che mi ritrovo ancora con il tasto premuto, quindi per il programma
    // questo frame è "uguale" al precedente; 
    // in questo caso il codice entra qui, ritorna false ed esce,
    // perché NON devo considerare questo come un nuovo click,
    // ma semplicemente come la prosecuzione del click precedente
    // tenuto premuto per qualche millisecondo.
    if (is_pulsante_premuto && !m_is_pulsante_rilasciato)
        return false;

    // se non ho cliccato il pulsante non ho fatto nulla, quindi esco
    if (!is_pulsante_premuto)
    {
        // se non ho cliccato il pulsante, allora di sicuro è stato rilasciato
        m_is_pulsante_rilasciato = true;
        return false;
    }

    // se sono qui, is_pulsante_premuto = true e quindi lo sto tenendo premuto;
    m_is_pulsante_rilasciato = false;

    int index = 0;
    for (const auto& bound : m_bounds_carte_in_mano)
    {
        if (bound.contains(sf::Vector2f(m_mouse_position)))
        {
            m_carta_scelta = index;
            m_carte_in_mano[index].m_is_in_gioco = false;

#ifdef _DEBUG
            std::cout << "carta scartata dal giocatore: "
                << m_carte_in_mano[index].m_nome << " "
                << m_carte_in_mano[index].m_seme << std::endl;
#endif

            return true;
        }
        index++;
    }

    // sto cliccando il pulsante in una zona fuori dal bounds delle mie carte
    return false;
}

void Giocatore::CalcolaPunteggio()
{
    m_punteggio = 0;

    for (const auto& carta : m_punti_fatti)
    {

        m_punteggio += carta.m_valore;
    }
}

void Giocatore::popolaBoundsCarte()
{
    unsigned int i = 0;
    for (auto& carta : m_carte_in_mano)
    {
        carta.SetBounds();
        m_bounds_carte_in_mano[i] = carta.GetBounds();
        i++;
    }
}
