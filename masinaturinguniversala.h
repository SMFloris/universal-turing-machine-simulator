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

#ifndef MASINATURINGUNIVERSALA_H
#define MASINATURINGUNIVERSALA_H

#include <qt4/QtCore/qobject.h>

#include "stare.h"
#include "banda.h"

class MasinaTuringUniversala : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Stare*> Stari READ Stari WRITE setStari)
    Q_PROPERTY(QList<Banda*> Benzi READ Benzi WRITE setBenzi)
    Q_PROPERTY(int nrBenzi READ nrBenzi WRITE setNrBenzi)
    Q_PROPERTY(QString continut READ continut WRITE setContinut)

public:
    MasinaTuringUniversala();

    QList<Stare*> Stari() const;
    QList<Banda*> Benzi() const;
    
    int nrBenzi() const;
    QString continut() const;
    
    void decodare();

    void addBanda(Banda* banda);
    void addStare(int stare1, int stare2, Trecere *aux);
    
    QChar decodareSimbol(int a);
    int decodareDirectie(int a);
    
    Stare* getStare(int numar);
    
public Q_SLOTS:
    void setStari(QList<Stare*> Stari);
    void setBenzi(QList<Banda*> Benzi);
    void setContinut(QString continut);
    void setNrBenzi(int nrBenzi);
    void porneste();
    void stepByStep();

signals:
        void terminat();
        void step(int banda_modif, int stare);

private:
    QList<Stare*> m_Stari;
    QList<Banda*> m_Benzi;
    int m_nrBenzi;
    QString m_continut;
    
    int stepI, stepJ, stepK;
};

#endif // MASINATURINGUNIVERSALA_H
