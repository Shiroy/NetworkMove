#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <string>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Label.hpp>
#include <Gui/GuiManager.h>


class LoginScreen
{
    public:

    LoginScreen();
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
};

#endif
