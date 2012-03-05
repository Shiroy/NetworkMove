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

#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <string>
#include "Gui/GuiManager.h"

class App;

class LoginScreen
{
    public:

    /*!
     *\brief Constructeur
     *\param *app Pointeur ver l'instance de App pour la gestion des événements
     */
    LoginScreen(App *app);
    ~LoginScreen();

    /*!
     *\brief Créer la GUI pour afficher l'écran de connexion et la passe en en tant que GUI actuellement à l'écran.
     *\warn A n'appeler qu'une fois dans le programme !
     */
    void CreateGui();

    /*!
     *\brief Affiche le message de status.
     *\details Affiche le message de status dans la boite de dialogue. Si la boite de dialogue n'est pas affiché elle est affiché. Si le message est vide, la boite de dialogue est cachée.
     */
    void SetStatutMessage(std::string msg = std::string());

    private:

    bool on_EventCharacterKey(CEGUI::EventArgs const &args);
    App *m_app; //Pointeur sur l'instance de app
};

#endif
