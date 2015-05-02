#ifndef uturingmachine_H
#define uturingmachine_H

#include <QtGui/QMainWindow>
#include <QtGui/QFormLayout>
#include <QtGui/QPushButton>
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
