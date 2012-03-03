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

#include "Gui/LoginScreen.h"
#include "App/App.h"
#include "Log/Log.h"

LoginScreen::LoginScreen()
{

}

LoginScreen::~LoginScreen()
{

}

void LoginScreen::CreateGui()
{
    CEGUI::WindowManager &winMgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Editbox *pseudoBox = static_cast<CEGUI::Editbox*>(winMgr.createWindow("WindowsLook/Editbox", "LOGIN_LOGIN_PSEUDO_EDITBOX"));
    pseudoBox->setText("Nom d'utilisateur");
    pseudoBox->setSize(CEGUI::UVector2(CEGUI::UDim(0.0f, 200), CEGUI::UDim(0.0f, 25)));
    pseudoBox->setSelection(0, pseudoBox->getText().size());
    pseudoBox->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&LoginScreen::on_EventCharacterKey, this));

    CEGUI::Editbox *passBox = static_cast<CEGUI::Editbox*>(winMgr.createWindow("WindowsLook/Editbox", "LOGIN_LOGIN_PASSWORD_EDITBOX"));
    passBox->setMaskCodePoint('*');
    passBox->setTextMasked(true);
    passBox->setText("Mot de passe");
    passBox->setSize(CEGUI::UVector2(CEGUI::UDim(0.0f, 200), CEGUI::UDim(0.0f, 25)));
    passBox->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&LoginScreen::on_EventCharacterKey, this));

    CEGUI::PushButton *connectButton = static_cast<CEGUI::PushButton*>(winMgr.createWindow("WindowsLook/Button", "LOGIN_LOGIN_CONNECT_BUTTON"));
    connectButton->setText("Connexion");
    connectButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.0f, 200), CEGUI::UDim(0.0f, 25)));

    CEGUI::Window *bg = winMgr.createWindow("VerticalLayoutContainer", "LOGIN_LOGIN_BACKGROUND_LAYOUT");
    bg->addChildWindow(pseudoBox);
    bg->addChildWindow(passBox);
    bg->addChildWindow(connectButton);

    pseudoBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0), CEGUI::UDim(0.5f, 0)));
    passBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0), CEGUI::UDim(0.6f, 0)));
    connectButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0), CEGUI::UDim(0.7f, 0)));
    CEGUI::System::getSingleton().setGUISheet(bg);
    pseudoBox->activate();
}

void LoginScreen::SetStatutMessage(std::string msg)
{
    /*if(msg.empty())
        m_status_window->Show(false);
    else
    {
        m_status_window->Show(true);
        m_status_label->SetText(msg);
    }*/
}

bool LoginScreen::on_EventCharacterKey(CEGUI::EventArgs const &args)
{
    CEGUI::KeyEventArgs const &e = static_cast<CEGUI::KeyEventArgs const&>(args);
    CEGUI::WindowManager &winMgr = ::CEGUI::WindowManager::getSingleton();
    if(e.window)
    {
        if(e.window->getName() == "LOGIN_LOGIN_PSEUDO_EDITBOX" && e.scancode == CEGUI::Key::Tab) //Tabulation ? Passage du focus au champ de mot de passe
        {
            CEGUI::Editbox *pass = static_cast<CEGUI::Editbox*>(winMgr.getWindow("LOGIN_LOGIN_PASSWORD_EDITBOX"));
            if(pass)
            {
                pass->setSelection(0, pass->getText().size());
                pass->activate();
                return true;
            }
        }

        if(e.window->getName() == "LOGIN_LOGIN_PASSWORD_EDITBOX" && e.scancode == CEGUI::Key::Tab) //Tabulation ? Passage du focus au champ de mot de pseudo
        {
            CEGUI::Editbox *pseudo = static_cast<CEGUI::Editbox*>(winMgr.getWindow("LOGIN_LOGIN_PSEUDO_EDITBOX"));
            if(pseudo)
            {
                pseudo->setSelection(0, pseudo->getText().size());
                pseudo->activate();
                return true;
            }
        }
    }

    return false;
}
