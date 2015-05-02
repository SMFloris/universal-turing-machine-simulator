#ifndef uturingmachine_H
#define uturingmachine_H

#include <QtGui/QMainWindow>
#include <QtGui/QFormLayout>
#include <QtGui/QPushButton>
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

#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>
#include <QtGui/QLabel>

#include "masinaturinguniversala.h"

class uturingmachine : public QMainWindow
{
    Q_OBJECT

public:
    uturingmachine();
    virtual ~uturingmachine();

private:
    bool running;
    QWidget *root;
    QLabel *m_stareCurenta;
    QFormLayout* m_layout;
    QFormLayout m_init;
    QFormLayout* m_binput;
    QPushButton* m_porneste;
    QFormLayout* m_output;
    QLineEdit* m_nrBenzi;
    QComboBox* m_mtu_fisiere;
    
    MasinaTuringUniversala* m_mtu;
    
    QString getFromFile(QString filename);
    
public slots:
  void on_nrBenzi_changed(QString nr);
  void on_porneste();
  void on_step(int banda_modif,int stare);
  void on_finish();
  void reset();
  
signals:
        void resetFinished();
};

#endif // uturingmachine_H
