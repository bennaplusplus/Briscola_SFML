#pragma once

#include <utility>

#include "Mazzo/Mazzo.hpp"
#include "Giocatore/Giocatore.hpp"
#include "PC_Player/PC_player.hpp"


class Campo
{
private:

    // vettore delle carte che sono sul tavolo
    std::vector<Carta> m_carte_sul_tavolo;

    // texture del campo da gioco
    sf::Texture m_immagine_background;

    // texture della carta di briscola che è sul campo
    sf::Texture m_immagine_briscola;

    // texture del mazzo
    sf::Texture m_immagine_mazzo;

    // carta di briscola sul campo di gioco
    const Carta& m_carta_briscola;

    // vettore 2D che contiene le coordinate dell'origine della carta di briscola. di default è (0, 0)
    sf::Vector2f m_briscolaOrigin;

    // vettore 2D che contiene la posizione da assegnare al punto m_briscolaOrigin
    sf::Vector2f m_briscolaPosition;

    // vettore 2D che contiene le coordinate dell'origine dell mazzo delle prese. di default è (0, 0)
    sf::Vector2f m_bottinoOrigin;

    // vettore 2D che contiene la posizione da assegnare al punto m_bottinoOrigin
    sf::Vector2f m_bottinoPosition;

    // vettore 2D che contiene le coordinate dell'origine del mazzo delle carte da pescare. di default è (0, 0)
    sf::Vector2f m_mazzoOrigin;

    // vettore 2D che contiene la posizione da assegnare al punto m_mazzoOrigin
    sf::Vector2f m_mazzoPosition;

    // font delle scritte che vengono mostrate a fianco della finestra a DX
    sf::Font m_font;

    // stringa che mi dice chi ha preso l'ultima mano
    std::string m_esito_mano;

    // stringa che mi dice chi ha vinto la partita
    std::string m_esito_partita;

public:

    //
    // ===========================
    //   Costruttore
    // ===========================
    //
    Campo(unsigned int, unsigned int, const char*, const Carta&);

    //
    // ===========================
    //   Setter
    // ===========================
    //
    void SetBriscolaOrigin();
    void SetBriscolaPosition();
    void SetMazzoOrigin();
    void SetMazzoPosition();

    //
    // ===========================
    //   Caricamento immagini
    // ===========================
    //
    void LoadBriscola();
    void LoadBackground();
    void LoadMazzo();

    //
    // ===========================
    //   Display
    // ===========================
    //
    void DisplayBriscola(bool, sf::RenderWindow&) const;
    void DisplayBackground(sf::RenderWindow&);
    void DisplayMazzo(bool, sf::RenderWindow&);
    void DisplayVincitoreManoPrecedente(sf::RenderWindow&);
    void DisplayTesto(const std::string&, sf::Vector2f, sf::Color, int, sf::RenderWindow&);
    void DisplayContornoCarta(Giocatore&, sf::RenderWindow&);
    void DisplayCarteGiocatore(std::vector<Carta>& carte_giocatore, sf::RenderWindow&);
    void DisplayBottinoGiocatore(bool, sf::RenderWindow&);
    void DisplayBottinoPC(bool, sf::RenderWindow&);

    //
    // ===========================
    //   Logica di gioco
    // ===========================
    //
    void DecretaVincitore(bool, Giocatore&, PC_player&, sf::RenderWindow&);
    void ChiHaVintoLaMano(Giocatore&, PC_player&);
};
