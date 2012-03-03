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
