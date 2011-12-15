#include <Gui/GuiManager.h>

GuiManager::GuiManager()
{
    m_widgetMap.clear();
}

GuiManager::~GuiManager()
{

}

void GuiManager::AddWidget(std::string name, sfg::Widget::Ptr widget)
{
    m_widgetMap[name] = widget;
}

sfg::Widget::Ptr GuiManager::GetWidget(std::string name)
{
    return m_widgetMap[name];
}

bool GuiManager::FindWidget(std::string name)
{
    if(m_widgetMap.find(name) == m_widgetMap.end())
        return false;
    else
        return true;
}

void GuiManager::SetTopLevelWidget(std::string name)
{
    if(sfg::Widget::Ptr widget = GetWidget(name))
    {
        m_topLevelWidget = widget;
    }
}

void GuiManager::RenderGui(sf::RenderWindow &window)
{
    if(m_topLevelWidget)
        m_topLevelWidget->Expose(window);
}

void GuiManager::HandleGuiEvent(sf::Event &event)
{
    if(m_topLevelWidget)
        m_topLevelWidget->HandleEvent(event);
}
