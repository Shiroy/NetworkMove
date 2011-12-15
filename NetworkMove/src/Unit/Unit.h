#ifndef UNIT_H
#define UNIT_H

#include <SFML/System.hpp>
#include <string>

class Unit
{
    public:
        Unit();
        Unit(std::string name, sf::Vector2i position);
        ~Unit();
        std::string GetName() { return m_Name; }
        void SetName(std::string val) { m_Name = val; }
        sf::Vector2i GetPosition() { return m_Position; }
        void SetPosition(sf::Vector2i val) { m_Position = val; }
    protected:
    private:
        std::string m_Name;
        sf::Vector2i m_Position;
};

#endif // UNIT_H
