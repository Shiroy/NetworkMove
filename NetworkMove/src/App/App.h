/*
NetworkMove : un projet de MMORPG éducatif
Copyright (C) 2012  Antoine Wacheux (Eryldor) and the NetworkMove development team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef APP_H
#define APP_H

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "Util/SharedDefine.h"
#include <Unit/Unit.h>
#include <Network/WorldSocket.h>
#include <Gui/GuiManager.h>
#include <Gui/LoginScreen.h>

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
    void AuthResponseReceived(uint8 resp);

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
