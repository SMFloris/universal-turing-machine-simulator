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

#ifndef BANDA_H
#define BANDA_H

#include <qt4/QtCore/qobject.h>
#include <qt4/QtCore/qstring.h>

#include "stare.h"

class Banda : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString continut READ continut WRITE setContinut)
    Q_PROPERTY(int pozitie READ pozitie WRITE setPozitie)

public:
Banda();

    QString continut() const;
    int pozitie() const;

public Q_SLOTS:
    void setContinut(const QString& continut);
    void setPozitie(int pozitie);

    //returneaza numarul starii destinatie
    int trecere(Trecere *a);

private:
    QString m_continut;
    int m_pozitie;
};

#endif // BANDA_H
