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

#include "App/App.h"
#include "Network/Opcode.h"
#include <memory>
#include <iostream>

App::App() : m_mainSocket(this), m_login(this)
{
    //ctor
}

App::~App()
{
    //dtor
}

void App::Init()
{
    run = true;

    m_window.Create(sf::VideoMode(800, 600), "Network Move", sf::Style::Close | sf::Style::Titlebar);
    m_window.SetFramerateLimit(60);
    m_window.ShowMouseCursor(false);

    sGuiManager->Initialize(&m_window);

    m_login.CreateGui();
}

void App::Run()
{
    while(run)
    {
        uint32 uiDiff = m_clock.GetElapsedTime().AsMilliseconds();
        m_mainSocket.Update(uiDiff);
        Update(uiDiff);
        m_clock.Restart();

        sf::Event event;
        while(m_window.PollEvent(event))
        {
            if(event.Type == sf::Event::Closed)
            {
                m_window.Close();
                run = false;
            }

            sGuiManager->HandleGuiEvent(event);
        }

        m_window.Clear();

        sGuiManager->RenderGui();

        m_window.Display();
    }
}

void App::Update(uint32 uiDiff)
{

}

void App::Exit()
{

}

bool App::ConnectHandler(CEGUI::EventArgs const &e)
{
    sf::Packet data;

    m_login.SetStatutMessage("Connexion en cours");

    CEGUI::WindowManager &winMgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Editbox *pseudoBox = static_cast<CEGUI::Editbox*>(winMgr.getWindow("LOGIN_LOGIN_PSEUDO_EDITBOX"));
    CEGUI::Editbox *passBox = static_cast<CEGUI::Editbox*>(winMgr.getWindow("LOGIN_LOGIN_PASSWORD_EDITBOX"));

    if(pseudoBox && passBox)
    {
        std::string pseudo, password;
        pseudo = pseudoBox->getText().c_str();
        password = passBox->getText().c_str();;
        data << uint16(CMSG_AUTH_TRY);
        data << std::string("0.0.1a");
        data << pseudo;
        data << password;

        if(!m_mainSocket.ConnectTo(sf::IpAddress("127.0.0.1")))
        {
            m_login.SetStatutMessage("Impossible de se connecter. Veuillez rééssayer plus tard.");
            return true;
        }

        m_mainSocket.SendPacket(data);
    }
    return true;
}

bool App::CancelClicked(CEGUI::EventArgs const &e)
{
    m_login.SetStatutMessage();
    m_mainSocket.Close();
}

void App::AuthResponseReceived(uint8 resp)
{
    switch(resp)
    {
        case AUTH_OK:
        m_login.SetStatutMessage("Authentifié.");
        break;

        case AUTH_WRONG_PASSWORD:
        m_login.SetStatutMessage("Mauvais mot de passe.");
        break;

        case AUTH_BANNED:
        m_login.SetStatutMessage("Vôtre compte a été bannis.");
        break;
    }
}

