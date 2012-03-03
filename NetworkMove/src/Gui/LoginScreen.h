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


    void CreateGui();

    void SetStatutMessage(std::string msg = std::string());

    private:

    bool on_EventCharacterKey(CEGUI::EventArgs const &args);
};

#endif
