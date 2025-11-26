#include "Campo.hpp"

//
// ============================================================================
//  COSTRUTTORE
// ============================================================================
//

Campo::Campo(unsigned int width, unsigned int height, const char* title, const Carta& briscola) :
    m_carta_briscola(briscola),
    m_carte_sul_tavolo(2, Carta())
{
    LoadBackground();
    LoadBriscola();
    LoadMazzo();
    m_font.openFromFile("C:/Windows/Fonts/Arial.ttf");
}

//
// ============================================================================
//  SETTER
// ============================================================================
//

void Campo::SetBriscolaOrigin()
{
    sf::Sprite sprite_briscola(m_immagine_briscola);
    sprite_briscola.setScale({ 0.1f, 0.1f });
    auto bounds = sprite_briscola.getLocalBounds();

    m_briscolaOrigin = {
        bounds.position.x + bounds.size.x / 2,
        bounds.position.y + bounds.size.y / 2
    };
}

void Campo::SetBriscolaPosition()
{
    m_briscolaPosition = { 650.0f, 300.0f };
}

void Campo::SetMazzoOrigin()
{
    sf::Sprite sprite_mazzo(m_immagine_mazzo);
    sprite_mazzo.setScale({ 0.1f, 0.1f });
    auto bounds = sprite_mazzo.getLocalBounds();

    m_mazzoOrigin = {
        bounds.position.x + bounds.size.x / 2,
        bounds.position.y + bounds.size.y / 2
    };
}

void Campo::SetMazzoPosition()
{
    m_mazzoPosition = { 800.0f, 300.0f };
}

//
// ============================================================================
//  CARICAMENTO RISORSE
// ============================================================================
//

void Campo::LoadBriscola()
{
    m_immagine_briscola.loadFromFile(m_carta_briscola.m_path_immagine);
    SetBriscolaOrigin();
    SetBriscolaPosition();
}

void Campo::LoadBackground()
{
    m_immagine_background.loadFromFile("Carte/background.png");
}

void Campo::LoadMazzo()
{
    m_immagine_mazzo.loadFromFile("Carte/retro_carta.jpg");
    SetMazzoOrigin();
    SetMazzoPosition();
}

//
// ============================================================================
//  DISPLAY GENERALI
// ============================================================================
//

void Campo::DisplayBriscola(bool is_ultima_mano, sf::RenderWindow& window) const
{
    if (!is_ultima_mano)
    {
        sf::Sprite sprite_briscola(m_immagine_briscola);
        sprite_briscola.setScale({ 0.1f, 0.1f });

        sprite_briscola.setOrigin(m_briscolaOrigin);
        sprite_briscola.setPosition(m_briscolaPosition);

        window.draw(sprite_briscola);
    }
}

void Campo::DisplayBackground(sf::RenderWindow& window)
{
    sf::Sprite background_image(m_immagine_background);
    background_image.setScale({ 0.586f, 0.586f });

    window.draw(background_image);
}

void Campo::DisplayMazzo(bool is_ultima_mano, sf::RenderWindow& window)
{
    if (!is_ultima_mano)
    {
        sf::Sprite sprite_mazzo(m_immagine_mazzo);
        sprite_mazzo.setScale({ 0.135f, 0.135f });

        sprite_mazzo.setOrigin(m_mazzoOrigin);
        sprite_mazzo.setPosition(m_mazzoPosition);

        window.draw(sprite_mazzo);
    }
}

void Campo::DisplayVincitoreManoPrecedente(sf::RenderWindow& window)
{
    sf::Vector2f position = { 1050.0f, 300.0f };
    sf::Text testo(m_font, m_esito_mano, 20);

    sf::FloatRect bounds = testo.getLocalBounds();
    testo.setOrigin({
        bounds.position.x + bounds.size.x / 2,
        bounds.position.y + bounds.size.y / 2
        });

    testo.setPosition(position);
    testo.setStyle(sf::Text::Bold);
    testo.setFillColor(sf::Color::White);

    window.draw(testo);
}

void Campo::DisplayTesto(const std::string& messaggio, sf::Vector2f position, sf::Color color, int fontSize, sf::RenderWindow& window)
{
    sf::Text testo(m_font, messaggio, fontSize);

    sf::FloatRect bounds = testo.getLocalBounds();
    testo.setOrigin({
        bounds.position.x + bounds.size.x / 2,
        bounds.position.y + bounds.size.y / 2
        });

    testo.setPosition(position);
    testo.setStyle(sf::Text::Bold);
    testo.setFillColor(color);

    window.draw(testo);
}

//
// ============================================================================
//  DISPLAY CARTE E CONTORNI
// ============================================================================
//

void Campo::DisplayContornoCarta(Giocatore& giocatore, sf::RenderWindow& window)
{
    const auto& mouse_position = giocatore.GetMousePosition();
    const auto& bounds_vector = giocatore.GetBoundsCarte();

    unsigned int numero_carta_scelta = 0;

    sf::RectangleShape contorno({ 132.0f, 219.0f });
    contorno.setFillColor(sf::Color::Transparent);
    contorno.setOutlineThickness(5.0f);
    contorno.setOutlineColor(sf::Color::Red);
    contorno.setOrigin({ 0.0f, 219.0f });

    for (const auto& bound : bounds_vector)
    {
        if (bound.contains({ (float)mouse_position.x, (float)mouse_position.y }))
        {
            float x = 50.f * (numero_carta_scelta + 1) + 132.f * numero_carta_scelta;
            contorno.setPosition({ x, 600.0f });

            window.draw(contorno);
            break;
        }
        numero_carta_scelta++;
    }
}

void Campo::DisplayCarteGiocatore(std::vector<Carta>& carte_giocatore, sf::RenderWindow& window)
{
    for (auto& carta : carte_giocatore)
        window.draw(carta.GetImage());
}

void Campo::DisplayBottinoGiocatore(bool size_vettore_punti, sf::RenderWindow& window)
{
    if (size_vettore_punti > 0)
    {
        sf::Sprite sprite(m_immagine_mazzo);
        sprite.setScale({ 0.135f, 0.135f });

        sprite.setOrigin(m_mazzoOrigin);
        sprite.rotate(sf::degrees(90));
        sprite.setPosition({ 725.0f, 500.0f });

        window.draw(sprite);
    }
}

void Campo::DisplayBottinoPC(bool punteggio_PC, sf::RenderWindow& window)
{
    if (punteggio_PC > 0)
    {
        sf::Sprite sprite(m_immagine_mazzo);
        sprite.setScale({ 0.135f, 0.135f });

        sprite.setOrigin(m_mazzoOrigin);
        sprite.rotate(sf::degrees(90));
        sprite.setPosition({ 725.0f, 100.0f });

        window.draw(sprite);
    }
}

//
// ============================================================================
//  LOGICA DI GIOCO
// ============================================================================
//

void Campo::DecretaVincitore(bool is_ultima_mano, Giocatore& giocatore, PC_player& PC, sf::RenderWindow& window)
{
    if (!is_ultima_mano)
        return;

    giocatore.CalcolaPunteggio();
    PC.CalcolaPunteggio();

    if (giocatore.GetPunteggio() > PC.GetPunteggio())
        m_esito_partita = "complimenti, hai vinto!";
    else if (giocatore.GetPunteggio() < PC.GetPunteggio())
        m_esito_partita = "mi spiace, hai perso!";
    else
        m_esito_partita = "partita finita in parità!";

    PC.SetToccaAlGiocatore(false);
    giocatore.SetToccaAlGiocatore(false);

    DisplayTesto(m_esito_partita, { 450, 300.0f }, sf::Color::Red, 40, window);
}

void Campo::ChiHaVintoLaMano(Giocatore& giocatore, PC_player& PC)
{
#if _DEBUG
    std::cout << "------------------------------------------------------------\n";
#endif

    auto& carte_giocatore = giocatore.GetCarte();
    auto& carte_PC = PC.GetCarte();
    auto& punti_giocatore = giocatore.GetPuntiFatti();
    auto& punti_PC = PC.GetPuntiFatti();

    int indice_PC = PC.GetIndiceCartaScelta();
    int indice_gio = giocatore.GetIndiceCartaScelta();

    // Caso 1: gioca prima il PC
    if (PC.GetIfToccaAlGiocatoreScartarePerPrimo())
    {
        m_carte_sul_tavolo[0] = carte_PC[indice_PC];
        m_carte_sul_tavolo[1] = carte_giocatore[indice_gio];

        if (m_carte_sul_tavolo[0] > m_carte_sul_tavolo[1])
        {
            m_esito_mano = "esito mano precedente:\nmano del PC";
            punti_PC.push_back(m_carte_sul_tavolo[0]);
            punti_PC.push_back(m_carte_sul_tavolo[1]);

            PC.SetToccaAlGiocatore(true);
            PC.SetToccaAlGiocatoreScartarePerPrimo(true);
            giocatore.SetToccaAlGiocatore(false);
            giocatore.SetToccaAlGiocatoreScartarePerPrimo(false);
        }
        else
        {
            m_esito_mano = "esito mano precedente:\nmano del giocatore";
            punti_giocatore.push_back(m_carte_sul_tavolo[0]);
            punti_giocatore.push_back(m_carte_sul_tavolo[1]);

            giocatore.SetToccaAlGiocatore(true);
            giocatore.SetToccaAlGiocatoreScartarePerPrimo(true);
            PC.SetToccaAlGiocatore(false);
            PC.SetToccaAlGiocatoreScartarePerPrimo(false);
        }
    }
    else
    {
        // Caso 2: gioca per primo il giocatore
        m_carte_sul_tavolo[0] = carte_giocatore[indice_gio];
        m_carte_sul_tavolo[1] = carte_PC[indice_PC];

        if (m_carte_sul_tavolo[0] > m_carte_sul_tavolo[1])
        {
            m_esito_mano = "esito mano precedente:\nmano del giocatore";
            punti_giocatore.push_back(m_carte_sul_tavolo[0]);
            punti_giocatore.push_back(m_carte_sul_tavolo[1]);

            giocatore.SetToccaAlGiocatore(true);
            giocatore.SetToccaAlGiocatoreScartarePerPrimo(true);
            PC.SetToccaAlGiocatore(false);
            PC.SetToccaAlGiocatoreScartarePerPrimo(false);
        }
        else
        {
            m_esito_mano = "esito mano precedente:\nmano del PC";
            punti_PC.push_back(m_carte_sul_tavolo[0]);
            punti_PC.push_back(m_carte_sul_tavolo[1]);

            PC.SetToccaAlGiocatore(true);
            PC.SetToccaAlGiocatoreScartarePerPrimo(true);
            giocatore.SetToccaAlGiocatore(false);
            giocatore.SetToccaAlGiocatoreScartarePerPrimo(false);
        }
    }
}
