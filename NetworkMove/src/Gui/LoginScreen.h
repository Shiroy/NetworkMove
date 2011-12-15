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

    void ConnectClicked();

    //Widget
    sfg::Entry::Ptr pseudoBox;
    sfg::Entry::Ptr passBox;
    sfg::Button::Ptr connectButton;
    sfg::Box::Ptr box;

    sfg::Window::Ptr m_status_window;
    sfg::Label::Ptr m_status_label;
    sfg::Button::Ptr m_status_cancel;
    sfg::Box::Ptr m_status_box;
};

#endif
