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

#include "masinaturinguniversala.h"
#include <QDebug>
#include <QStringList>

MasinaTuringUniversala::MasinaTuringUniversala()
{
        stepI = 0;
        stepJ = 0;
        stepK = 0;
}

QList<Stare*> MasinaTuringUniversala::Stari() const
{
    return m_Stari;
}

void MasinaTuringUniversala::setStari(QList<Stare*> Stari)
{
    m_Stari = Stari;
}

QList<Banda*> MasinaTuringUniversala::Benzi() const
{
    return m_Benzi;
}

void MasinaTuringUniversala::setBenzi(QList<Banda*> Benzi)
{
    m_Benzi = Benzi;
}

int MasinaTuringUniversala::nrBenzi() const
{
    return m_nrBenzi;
}

void MasinaTuringUniversala::setNrBenzi(int nrBenzi)
{
    m_nrBenzi = nrBenzi;
}

void MasinaTuringUniversala::addBanda(Banda* banda)
{

}

void MasinaTuringUniversala::addStare(int stare1, int stare2, Trecere *aux)
{
        qDebug()<<"rulez: "<<stare1<<" "<<stare2;
        int stare1i=-1,stare2i=-1;
        for(int i=0;i<m_Stari.count();i++){
                if(m_Stari.at(i)->numar == stare1)
                {
                        stare1i = i;
                }
                if(m_Stari.at(i)->numar == stare2)
                {
                        stare2i = i;
                }
        }
        Stare *starea1;
        Stare *starea2;
        if(stare1i>=0){
                qDebug()<<"Stare existenta "<<stare1;
                starea1 = m_Stari.at(stare1i);
        } else {
                starea1 = new Stare();
                starea1->numar = stare1;
                m_Stari.append(starea1);

        }
        
        if(stare2i>=0){
                qDebug()<<"Stare existenta "<<stare1;
                starea2 = m_Stari.at(stare2i);
        } else {
                starea2 = new Stare();
                starea2->numar = stare2;
                m_Stari.append(starea2);
        }
        
        aux->setStareOrig(starea1);
        aux->setStareDest(starea2);
        starea1->addTrecere(aux);
}

//incarca starile din codare
void MasinaTuringUniversala::decodare()
{
	//iterare inteligenta
	QStringList real = m_continut.split(QString("000"));
	//este masina pusa intre 000 si are ceva in ea?
	if(real.count()==3 && !real.at(1).isEmpty()){
		qDebug()<<"Verificare preliminara a masinii ok.";
		//gasesc partile stringului intre separatorii de tip 00
		QStringList treceri = real.at(1).split(QString("00"));
		if(treceri.count())
			for(int j=0; j<treceri.count(); j++){
				qDebug()<<"Pentru indexul "<<j<<" : "<<treceri.at(j);
				QStringList partiTreceri = treceri.at(j).split(QString("0"));
				if(partiTreceri.count()){
					//stare1,s1,directie,s2,stare2
					int stare1 = partiTreceri.at(0).length()-1;
					if(stare1<0){
						qDebug()<<QString("Nu am gasit starea 1 la trecerea ").append('0'+j);
						return;
					}
					QChar s1 = decodareSimbol(partiTreceri.at(1).length());
					if(s1 == QChar('N')){
						qDebug()<<QString("Nu am gasit simbol 1 la trecerea ").append('0'+j);
						return;
					}
					int dir = decodareDirectie(partiTreceri.at(2).length());
					if(dir == -3){
						qDebug()<<QString("Nu am gasit directia la trecerea ").append('0'+j);
						qDebug()<<partiTreceri.at(2);
                                                return;
					}
					QChar s2 = decodareSimbol(partiTreceri.at(3).length());
					if(s2 == QChar('N')){
						qDebug()<<QString("Nu am gasit simbolul 2 la trecerea ").append('0'+j);
						return;
					}
					int stare2 = partiTreceri.at(4).length()-1;
					if(stare1<0){
						qDebug()<<QString("Nu am gasit starea 1 la trecerea ").append('0'+j);
						return;
					}
					Trecere *newTrecere = new Trecere(s1,dir,s2);
                                        addStare(stare1,stare2,newTrecere);
				}
			}
	} else {
		qDebug()<<"Lipsesc separatorii de tip 000, vezi manual.";
	}
}

void MasinaTuringUniversala::stepByStep()
{
        QList<Trecere*> treceriCurente = m_Stari.at(stepI)->getTreceri();
        if(treceriCurente.count()%m_Benzi.count()!=0){
                qDebug()<<"La starea "<<stepI<<" nu aveti destule treceri pentru toate benzile.";
                return;
        }
        stepK=0;
        qDebug()<<"Treceri la starea curenta("<<stepI<<") :"<<treceriCurente.count();
        for(int z=stepJ;z<treceriCurente.count();z++){
                Trecere* trecereCurenta = treceriCurente.at(z);
                
                qDebug()<<"   "<<trecereCurenta->stareOrig()->numar<<" -> "<<trecereCurenta->stareDest()->numar;

                int stareUrm = m_Benzi.at(stepK)->trecere(trecereCurenta);

                if(stareUrm<0) continue;
                if(stareUrm == 0 && trecereCurenta->directie() == 0){
                        emit terminat();
                }
                
                emit step(stepK,stareUrm);
                
                if(stareUrm != stepI){
                        stepI = stareUrm;
                        qDebug()<<"Am trecut la starea: "<<stepI;
                        stepJ = 0;
                } else {
                        qDebug()<<"Am ramas la starea: "<<stepI;
                        stepJ++;
                        
                }
                
                stepK++;
                if(stepK>m_Benzi.count()-1){
                        stepK=0;
                }
                
                break;
                //qDebug()<<"   "<<trecereCurenta->stareOrig()->numar<<" -> "<<trecereCurenta->stareDest()->numar;
        }
        stepJ=0;
}

void MasinaTuringUniversala::porneste()
{
        bool ok = true;
        int i = 0;
        int k = 0;
        qDebug()<<"Countul de stari: "<<m_Stari.count();
        qDebug()<<"Continut: "<<m_Benzi.at(0)->continut();
        while(ok)
        {
                QList<Trecere*> treceriCurente = m_Stari.at(i)->getTreceri();
                if(treceriCurente.count()%m_Benzi.count()!=0){
                        qDebug()<<"La starea "<<i<<" nu aveti destule treceri pentru toate benzile.";
                        return;
                }
                k=0;
                qDebug()<<"Treceri la starea curenta("<<i<<") :"<<treceriCurente.count();
                for(int j=0;j<treceriCurente.count();j++){
                        Trecere* trecereCurenta = treceriCurente.at(j);
                        
                        qDebug()<<"   "<<trecereCurenta->stareOrig()->numar<<" -> "<<trecereCurenta->stareDest()->numar;

                        int stareUrm = m_Benzi.at(k)->trecere(trecereCurenta);
                        k++;
                        if(k>m_Benzi.count()-1){
                                k=0;
                        }
                        if(stareUrm<0) continue;
                        if(stareUrm == 0 && trecereCurenta->directie() == 0){
                                emit terminat();
                                ok=false;
                                break;
                        }
                        
                        if(stareUrm != i){
                                i = stareUrm;
                                qDebug()<<"Am trecut la starea: "<<i;
                        } else {
                                qDebug()<<"Am ramas la starea: "<<i;
                        }

                        //qDebug()<<"   "<<trecereCurenta->stareOrig()->numar<<" -> "<<trecereCurenta->stareDest()->numar;
                }
        }
        qDebug()<<"Continut: "<<m_Benzi.at(0)->continut();
}

QString MasinaTuringUniversala::continut() const
{
    return m_continut;
}

void MasinaTuringUniversala::setContinut(QString continut)
{
    m_continut = continut;
}

QChar MasinaTuringUniversala::decodareSimbol(int a)
{
	switch(a){
		case 1: return QChar('0');
		case 2: return QChar('1');
		case 3: return QChar(' ');
	}
	return QChar('N');
}

int MasinaTuringUniversala::decodareDirectie(int a)
{
	switch(a){
		case 1: return -1;
		case 2: return 1;
		case 3: return 0;
	}
	return -3;
}

Stare* MasinaTuringUniversala::getStare(int nr)
{
        for(int i=0;i<m_Stari.count();i++){
                if(m_Stari.at(i)->numar == nr){
                        return m_Stari.at(i);
                }
        }
        return new Stare();
}

#include "masinaturinguniversala.moc"
