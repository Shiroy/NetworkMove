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
    pseudoBox = sfg::Entry::Create("Nom d'utilisateur");
    pseudoBox->SetRequisition(sf::Vector2f(100.0f, .0f));

    passBox = sfg::Entry::Create("Mot de passe");
    passBox->HideText('*');
    passBox->SetRequisition(sf::Vector2f(100.0f, .0f));

    m_status_window = sfg::Window::Create();
    m_status_window->SetTitle("Connexion en cours");

    m_status_label = sfg::Label::Create("Connexion au serveur en cours.");

    m_status_window->Show(false);
    m_status_box = sfg::Box::Create(sfg::Box::VERTICAL);
    m_status_cancel = sfg::Button::Create("Annuler");
    m_status_box->Pack(m_status_label);
    m_status_box->Pack(m_status_cancel);
    m_status_window->Add(m_status_box);

    connectButton = sfg::Button::Create("Connexion");

    box = sfg::Box::Create(sfg::Box::VERTICAL);

    sGuiManager->AddWidget("LOGIN_LOGIN_PSEUDO_ENTRY", pseudoBox);
    sGuiManager->AddWidget("LOGIN_LOGIN_PASS_ENTRY", passBox);
    sGuiManager->AddWidget("LOGIN_LOGIN_CONNECT_BUTTON", connectButton);
    sGuiManager->AddWidget("LOGIN_LOGIN_MAIN_BOX", box);

    sGuiManager->AddWidget("LOGIN_STATUS_DIALOG_WINDOW", m_status_window);
    sGuiManager->AddWidget("LOGIN_STATUS_DIALOG_LABEL", m_status_label);
    sGuiManager->AddWidget("LOGIN_STATUS_CANCEL_BUTTON", m_status_cancel);
    sGuiManager->AddWidget("LOGIN_STATUS_DIALOG_BOX", m_status_box);

    box->Pack(pseudoBox, true, false);
    box->Pack(passBox, true, false);
    box->Pack(connectButton, true, false);
    box->Pack(m_status_window, true, false);
    //box->SetPosition(sf::Vector2f(400.0f, 325.0f));
    box->SetAllocation(sf::FloatRect(300.0f, 300.0f, 200.0f, 200.0f));
}

void LoginScreen::SetStatutMessage(std::string msg)
{
    if(msg.empty())
        m_status_window->Show(false);
    else
    {
        m_status_window->Show(true);
        m_status_label->SetText(msg);
    }
}
