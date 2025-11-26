#include "Mazzo.hpp"

Mazzo::Mazzo() :
    m_mazzo(40),
    m_mano{ 0 },
    m_prossima_carta{ 0 }
{
}

// ============================
//  Altri metodi (in ordine da hpp)
// ============================

void Mazzo::CreaMazzo()
{
    for (int seme = 0; seme < 4; ++seme)
    {
        for (int j = 0; j < 10; ++j)
        {
            auto& carta = m_mazzo[j + seme * 10];
            carta.m_seme = m_semi[seme];
            carta.m_nome = m_nomi[j];
            carta.m_valore = m_valori[j];
            carta.m_nome_int = m_nomi_int[j];
            carta.m_is_in_gioco = false;

            std::string path = "Carte/" + carta.m_nome + "_" + carta.m_seme + ".jpg";
            carta.Init(path, 0, false);
        }
    }
}

void Mazzo::DisplayMazzo() const
{
    for (int i = 0; i < 40; i++)
    {
        std::cout << m_mazzo[i].m_nome << " "
            << m_mazzo[i].m_seme << " "
            << m_mazzo[i].m_valore << " "
            << m_mazzo[i].m_is_briscola
            << std::endl;
    }
}

void Mazzo::MischiaMazzo()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_mazzo.begin(), m_mazzo.end(), g);

    m_prossima_carta = 0; // reset
}

void Mazzo::UpdateMano()
{
    m_mano++;

#ifdef _DEBUG
    std::cout << "mano numero: " << m_mano << std::endl;
#endif
}

void Mazzo::SetBriscola()
{
    m_briscola = m_mazzo[6]; // la briscola è la settima carta

    for (auto& carta : m_mazzo)
        carta.m_is_briscola = (carta.m_seme == m_briscola.m_seme);
}

// ============================
//  Getter
// ============================

Carta Mazzo::GetBriscola() const
{
    return m_briscola;
}

unsigned int& Mazzo::GetMano()
{
    return m_mano;
}

const unsigned int& Mazzo::GetMano() const
{
    return m_mano;
}

// ============================
//  Distribuzione carte
// ============================

void Mazzo::DistribuisciCarte(Giocatore& giocatore, PC_player& PC)
{
    if (m_mano == 1)
    {
        auto& carte_giocatore = giocatore.GetCarte();
        auto& carte_PC = PC.GetCarte();

        // assegnazione carte giocatore (0,2,4)
        for (int i = 0; i < carte_giocatore.size(); ++i)
        {
            int idx = i * 2;
            carte_giocatore[i] = m_mazzo[idx];
            carte_giocatore[i].m_is_carta_giocatore = true;
            carte_giocatore[i].m_is_in_gioco = true;
            carte_giocatore[i].m_numero_carta = i;
        }

        giocatore.popolaBoundsCarte();

        // assegnazione carte PC (1,3,5)
        for (int i = 0; i < carte_PC.size(); ++i)
        {
            int idx = i * 2 + 1;
            carte_PC[i] = m_mazzo[idx];
            carte_PC[i].m_is_in_gioco = true;
            carte_PC[i].m_numero_carta = i;
        }

        // rimuovo dal mazzo le carte assegnate
        Mazzo::RimuoviCarteDalMazzo(6);
    }
    else
    {
        const unsigned int index = 1;

        if (m_mano >= 2 && m_mano < 18) // mani intermedie
        {
            if (PC.GetIfToccaAlGiocatore())
            {
                PC.SetCarte(index, m_mazzo);
                m_mazzo[index + 1].m_is_carta_giocatore = true;
                giocatore.SetCarte(index + 1, m_mazzo);
            }
            else
            {
                PC.SetCarte(index + 1, m_mazzo);
                m_mazzo[index].m_is_carta_giocatore = true;
                giocatore.SetCarte(index, m_mazzo);
            }

            giocatore.popolaBoundsCarte();
            Mazzo::RimuoviCarteDalMazzo(3);
        }
        else if (m_mano == 18) // ultima mano con mazzo
        {
            if (PC.GetIfToccaAlGiocatore())
            {
                PC.SetCarte(index, m_mazzo);
                m_mazzo[0].m_is_carta_giocatore = true;
                giocatore.SetCarte(0, m_mazzo);
            }
            else
            {
                PC.SetCarte(0, m_mazzo);
                m_mazzo[index].m_is_carta_giocatore = true;
                giocatore.SetCarte(index, m_mazzo);
            }

            giocatore.popolaBoundsCarte();
            Mazzo::RimuoviCarteDalMazzo(2);
        }
        else // mano > 18
        {
            auto& carte_giocatore = giocatore.GetCarte();
            auto& carte_PC = PC.GetCarte();

            // voglio eliminare la carta scartata dalle carte in mano al giocatore
            Mazzo::RimuoviCartaDalleCarteGiocatore(PC);
            Mazzo::RimuoviCartaDalleCarteGiocatore(giocatore);

            // aggiusto m_numero_carta se necessario
            PC.SetCarte();
            giocatore.SetCarte();

            // se siamo alla mano 19, ho 2 carte in mano; alla 20, solo 1
            int new_dimension = (m_mano == 19) ? 2 : 1;
            giocatore.GetBoundsCarte().resize(new_dimension);
            giocatore.popolaBoundsCarte();
        }
    }
}

// ============================
//  Supporto
// ============================

int Mazzo::ContaCarteRimaste() const
{
    int numero_carte_in_gioco = 0;

    for (auto const& carta : m_mazzo)
        if (carta.m_is_in_gioco)
            numero_carte_in_gioco++;

    return numero_carte_in_gioco;
}

void Mazzo::RimuoviCarteDalMazzo(int elemento)
{
    // elimino tutte le carte fino a elemento (escluso)
    if (m_mano == 1 || m_mano == 18)
    {
        m_mazzo.erase(m_mazzo.begin(), m_mazzo.begin() + elemento);
    }
    else // m_mano >= 2 && m_mano < 18
    {
        // la prima carta è la briscola sul tavolo, non posso eliminarla
        m_mazzo.erase(m_mazzo.begin() + 1, m_mazzo.begin() + elemento);
    }
}

void Mazzo::RimuoviCartaDalleCarteGiocatore(Giocatore& giocatore)
{
    auto& carte_giocatore = giocatore.GetCarte();
    unsigned int index = giocatore.GetIndiceCartaScelta();

    carte_giocatore.erase(carte_giocatore.begin() + index);
}