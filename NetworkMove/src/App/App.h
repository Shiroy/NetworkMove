#ifndef APP_H
#define APP_H

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <Util/SharedDefine.h>
#include <Unit/Unit.h>
#include <Network/WorldSocket.h>
#include <Gui/GuiManager.h>
#include <Gui/LoginScreen.h>

enum Statut
{
    STATUT_NEVER,
    LOGIN_SCREEN,
    CHARACTER_SELECTION,
    INGAME
};

class App
{
    public:

    App();
    ~App();

    void Init();
    void Run();
    void Exit();

    void Update(uint32 uiDiff);

    /******************************
    *Gestion des signaux de la GUI*
    ******************************/

    void ConnectHandler();
    void CancelClicked();

    /********************************
    *Gestion des messages du serveur*
    ********************************/

    //

    private:

    sf::RenderWindow m_window;

    bool run;

    std::map<int, Unit> m_UnitMgr;

    WorldSocket m_mainSocket;
    sf::Clock m_clock;

    static int m_statue;

    //Les different composant du jeu

    LoginScreen m_login;
};

#endif // APP_H
