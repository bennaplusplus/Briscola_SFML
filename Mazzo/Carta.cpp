#include "Carta.hpp"

#define OFFSET 50.0f

//
// ============================================================================
//  COSTRUTTORE
// ============================================================================
//

Carta::Carta() :
    m_valore(0),
    m_nome_int(0),
    m_numero_carta(0),
    m_seme(""),
    m_nome(""),
    m_path_immagine(""),
    m_is_briscola(false),
    m_is_in_gioco(false),
    m_is_carta_giocatore(false),
    m_scale_factor(0.1f)
{
}

//
// ============================================================================
//  SETTER
// ============================================================================
//

// vettore 2D che rappresenta l'origine della carta
void Carta::SetImageOrigin()
{
    SetImageSize();

    if (m_is_carta_giocatore) // vertice in basso a SX
        m_imageOrigin = { 0.0f, (float)m_imageSize.y };
}

// vettore 2D che rappresenta la posizione di m_imageOrigin
void Carta::SetImagePosition()
{
    float x = OFFSET * (m_numero_carta + 1) + m_imageSize.x * m_numero_carta * m_scale_factor;
    float y = m_is_carta_giocatore ? 600.0f : 0.0f;

    if (!m_is_in_gioco)
        m_is_carta_giocatore ? y -= OFFSET : y += OFFSET;

    m_imagePosition = { x, y };
}

// dimensione originale della carta
void Carta::SetImageSize()
{
    m_imageSize = m_texture_fronte.getSize();
}

// coppia di vettori che indentificano la posizione in alto a SX e in basso a DX dell'immagine
void Carta::SetBounds()
{
    SetImageOrigin();
    SetImagePosition();

    sf::Sprite image_card(m_texture_fronte);
    image_card.setScale({ m_scale_factor, m_scale_factor });

    image_card.setOrigin(m_imageOrigin);
    image_card.setPosition(m_imagePosition);

    m_bounds = image_card.getGlobalBounds();
}

//
// ============================================================================
//  GETTER
// ============================================================================
//

const sf::Vector2f& Carta::GetOriginPosition() const
{
    return m_imageOrigin;
}

const sf::Vector2f& Carta::GetImagePosition() const
{
    return m_imagePosition;
}

const sf::Vector2u& Carta::GetImageSize() const
{
    return m_imageSize;
}

const unsigned int Carta::GetNumeroCarta() const
{
    return m_numero_carta;
}

sf::Sprite Carta::GetImage()
{
    SetImageOrigin();
    SetImagePosition();

    const auto& origin = GetOriginPosition();
    const auto& position = GetImagePosition();

    if (!m_is_carta_giocatore && m_is_in_gioco)
    {
#if _DEBUG
        sf::Sprite sprite(m_texture_fronte);
        sprite.setScale({ m_scale_factor, m_scale_factor });
        sprite.setOrigin(origin);
        sprite.setPosition(position);
#else
        sf::Sprite sprite(m_texture_retro);
        sprite.setScale({ 0.135f, 0.135f });
        sprite.setOrigin(origin);
        sprite.setPosition(position);
#endif
        return sprite;
    }
    else
    {
        sf::Sprite sprite(m_texture_fronte);
        sprite.setScale({ m_scale_factor, m_scale_factor });
        sprite.setOrigin(origin);
        sprite.setPosition(position);

        return sprite;
    }
}

const sf::FloatRect& Carta::GetBounds() const
{
    return m_bounds;
}

sf::FloatRect& Carta::GetBounds()
{
    return m_bounds;
}

//
// ============================================================================
//  ALTRI METODI
// ============================================================================
//

// inizializzazione
void Carta::Init(const std::string& path, unsigned numero, bool is_giocatore)
{
    m_path_immagine = path;
    m_numero_carta = numero;
    m_is_carta_giocatore = is_giocatore;

    LoadTextures();
    SetBounds();
}

// carica le texture del fronte e del retro
void Carta::LoadTextures()
{
    m_texture_fronte.loadFromFile(m_path_immagine);
    m_texture_retro.loadFromFile("Carte\\retro_carta.jpg");
}

//
// ============================================================================
//  FRIEND OPERATORS
// ============================================================================
//

// uguaglianza
bool operator==(const Carta& carta1, const Carta& carta2)
{
    return (carta1.m_nome == carta2.m_nome &&
        carta1.m_seme == carta2.m_seme);
}

// confronto ">"
bool operator>(const Carta& carta1, const Carta& carta2)
{
    // carta1 è briscola e carta2 no
    if (carta1.m_is_briscola && !carta2.m_is_briscola)
        return true;

    // carta1 non è briscola e carta2 sì
    if (!carta1.m_is_briscola && carta2.m_is_briscola)
        return false;

    // entrambe briscole
    if (carta1.m_is_briscola && carta2.m_is_briscola)
    {
        if (carta1.m_valore > carta2.m_valore)
            return true;

        if (carta1.m_valore == carta2.m_valore)
            return carta1.m_nome_int > carta2.m_nome_int;

        return false;
    }

    // nessuna delle due è briscola
    if (carta1.m_seme != carta2.m_seme)
        return true;

    // stesso seme
    if (carta1.m_valore > carta2.m_valore)
        return true;

    if (carta1.m_valore == carta2.m_valore)
        return carta1.m_nome_int > carta2.m_nome_int;

    return false;
}
