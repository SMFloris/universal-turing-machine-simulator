/*
 * Copyright (C) 2015  Floris Andrei Stoica Marcu <floris.sm@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include "trecere.h"

Trecere::Trecere()
{
}

Trecere::Trecere(QChar s1, int dir, QChar s2): QObject()
{
        m_simbolOrig = s1;
        m_directie = dir;
        m_simbolDest = s2;
}

QChar Trecere::simbolOrig() const
{
    return m_simbolOrig;
}

void Trecere::setSimbolOrig(QChar simbolOrig)
{
    m_simbolOrig = simbolOrig;
}

QChar Trecere::simbolDest() const
{
    return m_simbolDest;
}

void Trecere::setSimbolDest(QChar simbolDest)
{
    m_simbolDest = simbolDest;
}

Stare* Trecere::stareDest() const
{
    return m_stareDest;
}

void Trecere::setStareDest(Stare *stareDest)
{
    m_stareDest = stareDest;
}

Stare* Trecere::stareOrig() const
{
    return m_stareOrig;
}

void Trecere::setStareOrig(Stare *stareOrig)
{
    m_stareOrig = stareOrig;
}

int Trecere::directie() const
{
  return m_directie;
}

void Trecere::setDirectie(int directie)
{
  m_directie = directie;
}

#include "trecere.moc"
