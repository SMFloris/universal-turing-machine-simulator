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

#ifndef TRECERE_H
#define TRECERE_H

#include <qt4/QtCore/qobject.h>

class Stare;

class Trecere : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QChar simbolOrig READ simbolOrig WRITE setSimbolOrig)
    Q_PROPERTY(QChar simbolDest READ simbolDest WRITE setSimbolDest)
    Q_PROPERTY(int directie READ directie WRITE setDirectie)
    Q_PROPERTY(Stare *stareDest READ stareDest WRITE setStareDest)
    Q_PROPERTY(Stare *stareOrig READ stareOrig WRITE setStareOrig)

public:

    Trecere();
    Trecere(QChar s1,int dir,QChar s2);

    QChar simbolOrig() const;
    QChar simbolDest() const;
    int directie() const;
    Stare *stareDest() const;
    Stare *stareOrig() const;

public Q_SLOTS:
    void setSimbolOrig(QChar simbolOrig);
    void setSimbolDest(QChar simbolDest);
    void setDirectie(int directie);
    void setStareDest(Stare *stareDest);
    void setStareOrig(Stare *stareOrig);

private:
    QChar m_simbolOrig;
    QChar m_simbolDest;
    int m_directie;
    Stare *m_stareDest;
    Stare *m_stareOrig;
};

#endif // TRECERE_H
