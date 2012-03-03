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

#include "Gui/GuiManager.h"
#include "Log/Log.h"

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager()
{

}

bool GuiManager::Initialize(sf::RenderWindow *window)
{
    if(!m_window)
        return false;

    m_window = window;

    try
    {
        CEGUI::OpenGLRenderer &renderer = CEGUI::OpenGLRenderer::bootstrapSystem(CEGUI::Size(800, 600));
        //CEGUI::System::create(renderer);
        sLogMgr->Debug("System créer");
        CEGUI::SchemeManager::getSingleton().create("WindowsLook.scheme");
        sLogMgr->Debug("Scheme chargé");
        CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");
        sLogMgr->Debug("Font chargé");
    }
    catch(CEGUI::Exception &e)
    {
        sLogMgr->Error("Exception CEGUI : %s", e.getMessage().c_str());
        exit(1);
    }

    InitConversionTables();

    return true;
}

void GuiManager::RenderGui()
{
    CEGUI::System::getSingleton().renderGUI();
}

void GuiManager::HandleGuiEvent(sf::Event &event)
{
    bool handled = false;
    switch(event.Type)
    {
        case sf::Event::TextEntered:
        handled = CEGUI::System::getSingleton().injectChar(event.Text.Unicode);
        break;

        case sf::Event::KeyPressed:
        handled = CEGUI::System::getSingleton().injectKeyDown(ConvertKeyCode(event.Key.Code));
        break;

        case sf::Event::KeyReleased:
        handled = CEGUI::System::getSingleton().injectKeyUp(ConvertKeyCode(event.Key.Code));
        break;

        case sf::Event::MouseMoved:
        handled = CEGUI::System::getSingleton().injectMousePosition(event.MouseMove.X, event.MouseMove.Y);
        break;

        case sf::Event::MouseButtonPressed:
        handled = CEGUI::System::getSingleton().injectMouseButtonDown(ConvertMouseButton(event.MouseButton.Button));
        break;

        case sf::Event::MouseButtonReleased:
        handled = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MouseButton(event.MouseButton.Button));
        break;
    }
}

void GuiManager::InitConversionTables()
{
    mKeyMap[sf::Keyboard::Escape]          = CEGUI::Key::Escape       ;
	mKeyMap[sf::Keyboard::Num1]            = CEGUI::Key::One          ;
	mKeyMap[sf::Keyboard::Num2]            = CEGUI::Key::Two          ;
	mKeyMap[sf::Keyboard::Num3]            = CEGUI::Key::Three        ;
	mKeyMap[sf::Keyboard::Num4]            = CEGUI::Key::Four         ;
	mKeyMap[sf::Keyboard::Num5]            = CEGUI::Key::Five         ;
	mKeyMap[sf::Keyboard::Num6]            = CEGUI::Key::Six          ;
	mKeyMap[sf::Keyboard::Num7]            = CEGUI::Key::Seven        ;
	mKeyMap[sf::Keyboard::Num8]            = CEGUI::Key::Eight        ;
	mKeyMap[sf::Keyboard::Num9]            = CEGUI::Key::Nine         ;
	mKeyMap[sf::Keyboard::Num0]            = CEGUI::Key::Zero         ;
	mKeyMap[sf::Keyboard::Dash]            = CEGUI::Key::Minus        ;
	mKeyMap[sf::Keyboard::Equal]           = CEGUI::Key::Equals       ;
	mKeyMap[sf::Keyboard::Back]            = CEGUI::Key::Backspace    ;
	mKeyMap[sf::Keyboard::Tab]             = CEGUI::Key::Tab          ;
	mKeyMap[sf::Keyboard::Q]               = CEGUI::Key::Q            ;
	mKeyMap[sf::Keyboard::W]               = CEGUI::Key::W            ;
	mKeyMap[sf::Keyboard::E]               = CEGUI::Key::E            ;
	mKeyMap[sf::Keyboard::R]               = CEGUI::Key::R            ;
	mKeyMap[sf::Keyboard::T]               = CEGUI::Key::T            ;
	mKeyMap[sf::Keyboard::Y]               = CEGUI::Key::Y            ;
	mKeyMap[sf::Keyboard::U]               = CEGUI::Key::U            ;
	mKeyMap[sf::Keyboard::I]               = CEGUI::Key::I            ;
	mKeyMap[sf::Keyboard::O]               = CEGUI::Key::O            ;
	mKeyMap[sf::Keyboard::P]               = CEGUI::Key::P            ;
	mKeyMap[sf::Keyboard::LBracket]        = CEGUI::Key::LeftBracket  ;
	mKeyMap[sf::Keyboard::RBracket]        = CEGUI::Key::RightBracket ;
	mKeyMap[sf::Keyboard::Return]          = CEGUI::Key::Return       ;
	mKeyMap[sf::Keyboard::LControl]        = CEGUI::Key::LeftControl  ;
	mKeyMap[sf::Keyboard::A]               = CEGUI::Key::A            ;
	mKeyMap[sf::Keyboard::S]               = CEGUI::Key::S            ;
	mKeyMap[sf::Keyboard::D]               = CEGUI::Key::D            ;
	mKeyMap[sf::Keyboard::F]               = CEGUI::Key::F            ;
	mKeyMap[sf::Keyboard::G]               = CEGUI::Key::G            ;
	mKeyMap[sf::Keyboard::H]               = CEGUI::Key::H            ;
	mKeyMap[sf::Keyboard::J]               = CEGUI::Key::J            ;
	mKeyMap[sf::Keyboard::K]               = CEGUI::Key::K            ;
	mKeyMap[sf::Keyboard::L]               = CEGUI::Key::L            ;
	mKeyMap[sf::Keyboard::SemiColon]       = CEGUI::Key::Semicolon    ;
	mKeyMap[sf::Keyboard::LShift]          = CEGUI::Key::LeftShift    ;
	mKeyMap[sf::Keyboard::BackSlash]       = CEGUI::Key::Backslash    ;
	mKeyMap[sf::Keyboard::Z]               = CEGUI::Key::Z            ;
	mKeyMap[sf::Keyboard::X]               = CEGUI::Key::X            ;
	mKeyMap[sf::Keyboard::C]               = CEGUI::Key::C            ;
	mKeyMap[sf::Keyboard::V]               = CEGUI::Key::V            ;
	mKeyMap[sf::Keyboard::B]               = CEGUI::Key::B            ;
	mKeyMap[sf::Keyboard::N]               = CEGUI::Key::N            ;
	mKeyMap[sf::Keyboard::M]               = CEGUI::Key::M            ;
	mKeyMap[sf::Keyboard::Comma]           = CEGUI::Key::Comma        ;
	mKeyMap[sf::Keyboard::Period]          = CEGUI::Key::Period       ;
	mKeyMap[sf::Keyboard::Slash]           = CEGUI::Key::Slash        ;
	mKeyMap[sf::Keyboard::RShift]          = CEGUI::Key::RightShift   ;
	mKeyMap[sf::Keyboard::Multiply]        = CEGUI::Key::Multiply     ;
	mKeyMap[sf::Keyboard::LAlt]            = CEGUI::Key::LeftAlt      ;
	mKeyMap[sf::Keyboard::Space]           = CEGUI::Key::Space        ;
	mKeyMap[sf::Keyboard::F1]              = CEGUI::Key::F1           ;
	mKeyMap[sf::Keyboard::F2]              = CEGUI::Key::F2           ;
	mKeyMap[sf::Keyboard::F3]              = CEGUI::Key::F3           ;
	mKeyMap[sf::Keyboard::F4]              = CEGUI::Key::F4           ;
	mKeyMap[sf::Keyboard::F5]              = CEGUI::Key::F5           ;
	mKeyMap[sf::Keyboard::F6]              = CEGUI::Key::F6           ;
	mKeyMap[sf::Keyboard::F7]              = CEGUI::Key::F7           ;
	mKeyMap[sf::Keyboard::F8]              = CEGUI::Key::F8           ;
	mKeyMap[sf::Keyboard::F9]              = CEGUI::Key::F9           ;
	mKeyMap[sf::Keyboard::F10]             = CEGUI::Key::F10          ;
	mKeyMap[sf::Keyboard::Numpad7]         = CEGUI::Key::Numpad7      ;
	mKeyMap[sf::Keyboard::Numpad8]         = CEGUI::Key::Numpad8      ;
	mKeyMap[sf::Keyboard::Numpad9]         = CEGUI::Key::Numpad9      ;
	mKeyMap[sf::Keyboard::Subtract]        = CEGUI::Key::Subtract     ;
	mKeyMap[sf::Keyboard::Numpad4]         = CEGUI::Key::Numpad4      ;
	mKeyMap[sf::Keyboard::Numpad5]         = CEGUI::Key::Numpad5      ;
	mKeyMap[sf::Keyboard::Numpad6]         = CEGUI::Key::Numpad6      ;
	mKeyMap[sf::Keyboard::Add]             = CEGUI::Key::Add          ;
	mKeyMap[sf::Keyboard::Numpad1]         = CEGUI::Key::Numpad1      ;
	mKeyMap[sf::Keyboard::Numpad2]         = CEGUI::Key::Numpad2      ;
	mKeyMap[sf::Keyboard::Numpad3]         = CEGUI::Key::Numpad3      ;
	mKeyMap[sf::Keyboard::Numpad0]         = CEGUI::Key::Numpad0      ;
	mKeyMap[sf::Keyboard::F11]             = CEGUI::Key::F11          ;
	mKeyMap[sf::Keyboard::F12]             = CEGUI::Key::F12          ;
	mKeyMap[sf::Keyboard::F13]             = CEGUI::Key::F13          ;
	mKeyMap[sf::Keyboard::F14]             = CEGUI::Key::F14          ;
	mKeyMap[sf::Keyboard::F15]             = CEGUI::Key::F15          ;
	mKeyMap[sf::Keyboard::RControl]        = CEGUI::Key::RightControl ;
	mKeyMap[sf::Keyboard::Divide]          = CEGUI::Key::Divide       ;
	mKeyMap[sf::Keyboard::RAlt]            = CEGUI::Key::RightAlt     ;
	mKeyMap[sf::Keyboard::Pause]           = CEGUI::Key::Pause        ;
	mKeyMap[sf::Keyboard::Home]            = CEGUI::Key::Home         ;
	mKeyMap[sf::Keyboard::Up]              = CEGUI::Key::ArrowUp      ;
	mKeyMap[sf::Keyboard::PageUp]          = CEGUI::Key::PageUp       ;
	mKeyMap[sf::Keyboard::Left]            = CEGUI::Key::ArrowLeft    ;
	mKeyMap[sf::Keyboard::Right]           = CEGUI::Key::ArrowRight   ;
	mKeyMap[sf::Keyboard::End]             = CEGUI::Key::End          ;
	mKeyMap[sf::Keyboard::Down]            = CEGUI::Key::ArrowDown    ;
	mKeyMap[sf::Keyboard::PageDown]        = CEGUI::Key::PageDown     ;
	mKeyMap[sf::Keyboard::Insert]          = CEGUI::Key::Insert       ;
	mKeyMap[sf::Keyboard::Delete]          = CEGUI::Key::Delete       ;

	mMouseButtonMap[sf::Mouse::Left]		= CEGUI::LeftButton;
	mMouseButtonMap[sf::Mouse::Middle]		= CEGUI::MiddleButton;
	mMouseButtonMap[sf::Mouse::Right]		= CEGUI::RightButton;
	mMouseButtonMap[sf::Mouse::XButton1]	= CEGUI::X1Button;
	mMouseButtonMap[sf::Mouse::XButton2]	= CEGUI::X2Button;
}

CEGUI::Key::Scan GuiManager::ConvertKeyCode(sf::Keyboard::Key scanCode)
{
    if(mKeyMap.find(scanCode) == mKeyMap.end())
        return (CEGUI::Key::Scan)0;
    return mKeyMap[scanCode];
}

CEGUI::MouseButton GuiManager::ConvertMouseButton(sf::Mouse::Button bt)
{
    if(mMouseButtonMap.find(bt) == mMouseButtonMap.end())
        return (CEGUI::MouseButton)0;
    return mMouseButtonMap[bt];
}
