#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <map>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <Singleton/Singleton.h>
#include <Util/SharedDefine.h>
#include <SFML/Graphics.hpp>

/******************Convention de nommage des widget******************
Nom du widget : (STATUS)_(INTERFACE)_(FONCTION WIDGET)_(WIDGET)

Avec STATUS:
- LOGIN (ecran de connexion + dialogue de status de la connexion)
- CHAR (selection de personnage)
- INGAME (interface du jeu)

Exemple -> Bouton inviter de l'interface de guilde

INGAME_GUILD_INVITE_BUTTON

Bouton connexion de l'ecran de connexion:

LOGIN_LOGIN_CONNECT_BUTTON
*********************************************************************/

class GuiManager
{
    friend class Singleton<GuiManager>;

    public:

    GuiManager(); //NE JAMAIS INSTANCIER CETTE CLASSE DIRECTEMENT !!! TOUJOUS UTILISÉ LE SINGLETON sGuiManager
    ~GuiManager();

    bool Initialize(sf::RenderWindow *window);

    void RenderGui();

    void HandleGuiEvent(sf::Event &event);

    CEGUI::Key::Scan ConvertKeyCode(sf::Keyboard::Key scanCode);
    CEGUI::MouseButton ConvertMouseButton(sf::Mouse::Button button);
    void InitConversionTables();

    private:

    sf::RenderWindow *m_window;

    std::map<sf::Keyboard::Key, CEGUI::Key::Scan> mKeyMap; //Les code de CEGUI et de la SFML sont différents
    std::map<sf::Mouse::Button, CEGUI::MouseButton> mMouseButtonMap;
};

#define sGuiManager Singleton<GuiManager>::GetInstance()
#endif
