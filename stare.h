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

#ifndef STARE_H
#define STARE_H

#include <qt4/QtCore/qobject.h>
#include <qt4/QtCore/qlist.h>

#include "trecere.h"

class Stare : public QObject
{
    Q_OBJECT

public:

  Stare();
  
  int numar;
  
  void addTrecere(Trecere *);
  QList<Trecere*> getTreceri();

private:

        QList<Trecere*> m_treceri;
};

#endif // STARE_H
