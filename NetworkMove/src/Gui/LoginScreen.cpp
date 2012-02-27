#include <Gui/LoginScreen.h>
#include <App/App.h>

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

    CEGUI::Editbox *passBox = static_cast<CEGUI::Editbox*>(winMgr.createWindow("WindowsLook/Editbox", "LOGIN_LOGIN_PASSWORD_EDITBOX"));
    passBox->setMaskCodePoint('*');
    passBox->setTextMasked(true);
    passBox->setText("Mot de passe");
    passBox->setSize(CEGUI::UVector2(CEGUI::UDim(0.0f, 200), CEGUI::UDim(0.0f, 25)));

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
