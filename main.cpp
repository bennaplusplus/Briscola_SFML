#ifndef _DEBUG
#include <Windows.h>
#endif

#include "Mazzo/Mazzo.hpp"
#include "Campo/Campo.hpp"

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow
) // DEBUG
#endif
{
    Mazzo       mazzo;
    Giocatore   giocatore;
    PC_player   PC;

    mazzo.CreaMazzo();
    mazzo.MischiaMazzo();
    mazzo.SetBriscola();

    const Carta& briscola = mazzo.GetBriscola();
    Campo campo(1200, 600, "Briscola", briscola);
    sf::RenderWindow window(sf::VideoMode({ 1200, 600 }), "Briscola");
    window.setFramerateLimit(60);

    // di default parte il PC, ma non è necessario;
    giocatore.SetToccaAlGiocatore(false);
    giocatore.SetToccaAlGiocatoreScartarePerPrimo(false);
    PC.SetToccaAlGiocatore(true);
    PC.SetToccaAlGiocatoreScartarePerPrimo(true);

    mazzo.UpdateMano();
    mazzo.DistribuisciCarte(giocatore, PC);
    int count = 0;

    while (window.isOpen())
    {
        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // giocatore
        if (giocatore.GetIfToccaAlGiocatore())
        {
            if (giocatore.ScartaCarta(window))
            {
                giocatore.SetToccaAlGiocatore(false);

                if (giocatore.GetIfToccaAlGiocatoreScartarePerPrimo())
                    PC.SetToccaAlGiocatore(true);
            }
        }

        // PC
        if (PC.GetIfToccaAlGiocatore())
        {
            PC.MossaPC(giocatore.GetCarte());
            PC.SetToccaAlGiocatore(false);

            if (PC.GetIfToccaAlGiocatoreScartarePerPrimo())
                giocatore.SetToccaAlGiocatore(true);
        }

        // solo se entrambi hanno scartato si può procedere a controllare
        // chi ha vinto la mano e ricominciare
        if (!giocatore.GetIfToccaAlGiocatore() &&
            !PC.GetIfToccaAlGiocatore())
        {
            campo.ChiHaVintoLaMano(giocatore, PC);
            mazzo.UpdateMano();
            mazzo.DistribuisciCarte(giocatore, PC);
        }

        /*****************************************************************************************************************************************************/
        window.clear(sf::Color(64, 64, 64));

        campo.DisplayBackground(window);
        campo.DisplayTesto(
            std::string("mano numero: ") + std::to_string(mazzo.GetMano()),
            { 1050.0f, 50.0f },
            sf::Color::White,
            20,
            window
        );

        campo.DisplayBriscola(mazzo.GetMano() > 17, window);
        campo.DisplayCarteGiocatore(giocatore.GetCarte(), window);
        campo.DisplayCarteGiocatore(PC.GetCarte(), window);

        // mostro a schermo il seme di briscola nelle ultime mani
        if (mazzo.GetMano() > 18)
        {
            std::string message = "briscola : " + briscola.m_seme;
            campo.DisplayTesto(message, { 1040.0f, 500.0f },
                sf::Color::White, 20, window);
        }

        if (mazzo.GetMano() > 1)
        {
            campo.DisplayVincitoreManoPrecedente(window);
        }

        campo.DisplayContornoCarta(giocatore, window);
        campo.DisplayMazzo(mazzo.GetMano() > 17, window);
        campo.DisplayBottinoGiocatore(giocatore.GetPuntiFatti().size() > 0, window);
        campo.DisplayBottinoPC(PC.GetPuntiFatti().size() > 0, window);

        campo.DecretaVincitore(mazzo.GetMano() == 21, giocatore, PC, window);

        window.display();
        /*****************************************************************************************************************************************************/

        // partita finita
        if (mazzo.GetMano() == 21)
        {
            // pausa di 2 secondi per visualizzare l'esito della partita
            sf::sleep(sf::seconds(2));   
            window.close();
        }
    }

    return 0;
}
