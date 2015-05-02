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

#include "banda.h"

Banda::Banda()
{
        m_continut = QString();
        m_pozitie = 0;
}

QString Banda::continut() const
{
    return m_continut;
}

void Banda::setContinut(const QString& continut)
{
    m_continut = continut;
}

int Banda::pozitie() const
{
    return m_pozitie;
}

void Banda::setPozitie(int pozitie)
{
    m_pozitie = pozitie;
}

int Banda::trecere(Trecere* a)
{
    if(m_continut.at(m_pozitie) == a->simbolOrig())
    {
      m_continut[m_pozitie] = a->simbolDest();
      m_pozitie += a->directie();
      return a->stareDest()->numar;
    }
    return -1;
}

#include "banda.moc"
