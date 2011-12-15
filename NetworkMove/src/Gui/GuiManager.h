#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <map>
#include <SFGUI/Widget.hpp>
#include <Util/Singleton.h>
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

    void AddWidget(std::string name, sfg::Widget::Ptr widget);
    sfg::Widget::Ptr GetWidget(std::string name);

    bool FindWidget(std::string name);

    void SetTopLevelWidget(std::string name);
    sfg::Widget::Ptr GetTopLevelWidget() {return m_topLevelWidget;}

    void RenderGui(sf::RenderWindow &window);

    void HandleGuiEvent(sf::Event &event);

    private:

    std::map<std::string, sfg::Widget::Ptr> m_widgetMap;
    sfg::Widget::Ptr m_topLevelWidget;
};

#define sGuiManager Singleton<GuiManager>::GetInstance()
#endif
