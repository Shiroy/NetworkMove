#include <Unit/Unit.h>

Unit::Unit()
{
    m_Name = std::string();
    m_Position = sf::Vector2i();
}

Unit::Unit(std::string name, sf::Vector2i position) : m_Name(name), m_Position(position)
{
    //ctor
}

Unit::~Unit()
{
    //dtor
}
