#pragma once

#include <string>
#include "SFML/Graphics.hpp"

// ============================================================================
//  Struttura Carta
// ============================================================================
struct Carta
{
    // =========================================================================
    //  Membri
    // =========================================================================

    // valore della carta
    int m_valore;

    // nome della carta in formato decimale (es "cavallo" = 9; "asso" = 11; "due" = 2)
    int m_nome_int;

    // indice della carta che ha in mano il giocatore (da 0 a 2)
    int m_numero_carta;

    // seme; può essere bastoni, coppe, denari o spade
    std::string m_seme;

    // nome della carta; es. tre di denari
    std::string m_nome;

    // path della carta, data dalla combinazione di m_nome e m_seme
    std::string m_path_immagine;

    // booleano che indica se la carta ha il seme di briscola
    bool m_is_briscola;

    // booleano che indica se la carta è in gioco o è appena stata scartata nella mano corrente
    bool m_is_in_gioco;

    // booleano che indica se la carta appartiene al giocatore
    bool m_is_carta_giocatore;

    // fattore di scala per adattare la dimensione dell'immagine alla finestra
    float m_scale_factor;

    // immagine del fronte della carta (ognuna ha la sua immagine)
    sf::Texture m_texture_fronte;

    // immagine del retro della carta (uguale per tutte)
    sf::Texture m_texture_retro;

    // origine della carta; di default è (0.0), cioè angolo alto a sinistra
    sf::Vector2f m_imageOrigin;

    // posizione dell'origine dell'immagine
    sf::Vector2f m_imagePosition;

    // dimensione originale in pixel dell'immagine caricata
    sf::Vector2u m_imageSize;

    // coppia di vettori che identificano la posizione della carta sullo schermo
    sf::FloatRect m_bounds;

    // =========================================================================
    //  Costruttore
    // =========================================================================

    Carta();

    // =========================================================================
    //  Setter
    // =========================================================================

    // calcola l'origine dell'immagine della carta
    void SetImageOrigin();

    // calcola la posizione dell'immagine della carta
    void SetImagePosition();

    // salva la dimensione originale della texture
    void SetImageSize();

    // calcola il bounding box globale della carta
    void SetBounds();

    // =========================================================================
    //  Getter
    // =========================================================================

    const sf::Vector2f& GetOriginPosition() const;
    const sf::Vector2f& GetImagePosition() const;
    const sf::Vector2u& GetImageSize() const;
    const unsigned int  GetNumeroCarta() const;
    sf::Sprite          GetImage();
    const sf::FloatRect& GetBounds() const;
    sf::FloatRect& GetBounds();

    // =========================================================================
    //  Altri metodi
    // =========================================================================

    // carica le texture fronte/retro
    void LoadTextures();

    // inizializza la carta
    void Init(const std::string&, unsigned, bool);

    // =========================================================================
    //  Operator overloads (friend)
    // =========================================================================

    friend bool operator==(const Carta& carta1, const Carta& carta2);
    friend bool operator>(const Carta& carta1, const Carta& carta2);
};