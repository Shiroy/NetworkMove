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

App::App() : m_mainSocket(this)
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
    //m_window.ShowMouseCursor(false);

    sGuiManager->Initialize(&m_window);

    m_login.CreateGui();
    /*sfg::Widget::Ptr result = sGuiManager->GetWidget("LOGIN_LOGIN_CONNECT_BUTTON");

    sfg::Button::Ptr connect = sfg::DynamicPointerCast<sfg::Button>(result);
    if(connect)
    {
        connect->OnClick.Connect(&App::ConnectHandler, this);
    }

    sfg::Button::Ptr cancel = sfg::DynamicPointerCast<sfg::Button>(sGuiManager->GetWidget("LOGIN_STATUS_CANCEL_BUTTON"));
    if(cancel)
    {
        cancel->OnClick.Connect(&App::CancelClicked, this);
    }

    sGuiManager->SetTopLevelWidget("LOGIN_LOGIN_MAIN_BOX");*/
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

void App::ConnectHandler()
{
    /*sf::Packet data;

    sfg::Entry::Ptr pseudoBox, passBox;
    pseudoBox = sfg::DynamicPointerCast<sfg::Entry>(sGuiManager->GetWidget("LOGIN_LOGIN_PSEUDO_ENTRY"));
    passBox = sfg::DynamicPointerCast<sfg::Entry>(sGuiManager->GetWidget("LOGIN_LOGIN_PASS_ENTRY"));

    m_login.SetStatutMessage("Connexion en cours");

    if(pseudoBox && passBox)
    {
        std::string pseudo, password;
        pseudo = pseudoBox->GetText();
        password = passBox->GetText();
        data << uint16(CMSG_AUTH_TRY);
        data << std::string("0.0.1a");
        data << pseudo;
        data << password;

        if(!m_mainSocket.ConnectTo(sf::IpAddress("127.0.0.1")))
        {
            m_login.SetStatutMessage("Impossible de se connecter. Veuillez rééssayer plus tard.");
        }

        m_mainSocket.SendPacket(data);
    }*/
}

void App::CancelClicked()
{
    /*sfg::Window::Ptr statusWindow = sfg::DynamicPointerCast<sfg::Window>(sGuiManager->GetWidget("LOGIN_STATUS_DIALOG_WINDOW"));
    if(statusWindow)
    {
        statusWindow->Show(false);
    }

    m_mainSocket.Close();*/
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

