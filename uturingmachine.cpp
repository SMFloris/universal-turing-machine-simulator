#include "uturingmachine.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QTextStream>
#include <QMessageBox>

uturingmachine::uturingmachine()
{

    reset();

    //meniu
    QAction* action = new QAction(this);
    action->setText( "Quit" );
    connect(action, SIGNAL(triggered()), SLOT(close()) );
    menuBar()->addMenu( "File" )->addAction( action );
}

uturingmachine::~uturingmachine()
{}

void clearLayout(QFormLayout *layout) 
{
    if (layout) {
        while(layout->count() > 0){
            QLayoutItem *item = layout->takeAt(0);
            delete item->widget();
            delete item;
        }
    }
}

void uturingmachine::on_nrBenzi_changed(QString nr)
{
    if(running){
            reset();
            m_nrBenzi->setText(nr);
    }
    int no = nr.toUInt();
    clearLayout(m_binput);
    qDebug()<<"  "<<m_binput->count();
    m_layout->removeItem(m_binput);
    m_binput = new QFormLayout();
    
    //ia numai fisierele .txt
    QDir currentDir = QDir::currentPath();
    QStringList files;
    QStringList filters;
    filters << "*.txt";
    files = currentDir.entryList(filters,
                                  QDir::Files | QDir::NoSymLinks);
    
    for(int i=0;i<no;i++)
    {
      QComboBox *mtu_fisiere = new QComboBox( this );
      for (int i = 0; i < files.size(); ++i) {
	  mtu_fisiere->addItem(files.at(i));
      }
      QLineEdit *aux = new QLineEdit(this);
      m_binput->addRow(QString("Banda ").append(QChar(char('0'+i+1))),mtu_fisiere);
    }
    m_layout->addItem(m_binput);
    if(no>0)
    {
      m_layout->addWidget(m_porneste);
      m_porneste->show();

    } else {
      m_layout->removeWidget(m_porneste);
      m_porneste->hide();
    }
    qDebug()<<"  "<<m_binput->count();
    QWidget *window = new QWidget();
    window->setLayout(m_layout);
    setCentralWidget(window);

}

void uturingmachine::on_porneste()
{
    qDebug()<<"click pe buton!";
    int no = m_nrBenzi->text().toUInt();
    m_mtu->setNrBenzi(no);
    
    //incarca masina
    QString continut = getFromFile(m_mtu_fisiere->currentText());
    if(continut.isEmpty()){
	    return;
    }
    
    m_mtu->setContinut(continut);
    running = true;
    
    qDebug()<<"Am citit: "<<continut;
    
    QList<Banda*> listaBenzi;
    m_output = new QFormLayout();
    
    //incarca benzile de intrare/iesire
    clearLayout(m_output);
    qDebug()<<"Countul binputurilor = "<<m_binput->count();
    for(int i=0;i<m_binput->count();i++){
	    if(i%2==0){
                    continue;
	    }
	    QComboBox* banda = (QComboBox*) m_binput->takeAt(i)->widget();
	    if(banda)
	    {
		    qDebug()<<"Introduc in lista de benzi a masinii: "<<banda->currentText();
		    Banda* newBanda = new Banda();
		    newBanda->setContinut(getFromFile(banda->currentText()));
                    QLabel *newLabel = (QLabel*) m_binput->takeAt(i-1)->widget();
                    newLabel->setText(newBanda->continut());
                    m_output->addRow(QString("Banda ").append('1'+i/2).append(":"),newLabel);
		    listaBenzi<<newBanda;
	}
    }
    
    m_mtu->setBenzi(listaBenzi);
    m_mtu->decodare();
    
    QPushButton *stepButton = new QPushButton(this);
    QPushButton *startButton = new QPushButton(this);
    
    stepButton->setText(QString("Step"));
    startButton->setText(QString("Run"));
    
    connect(stepButton,SIGNAL(clicked(bool)),startButton,SLOT(hide()));
    connect(startButton,SIGNAL(clicked(bool)),stepButton,SLOT(hide()));
    connect(startButton,SIGNAL(clicked(bool)),m_mtu,SLOT(porneste()));
    connect(stepButton,SIGNAL(clicked(bool)),m_mtu,SLOT(stepByStep()));
    connect(m_mtu,SIGNAL(terminat()),startButton,SLOT(hide()));
    connect(m_mtu,SIGNAL(terminat()),stepButton,SLOT(hide()));
    connect(m_mtu,SIGNAL(terminat()),startButton,SLOT(deleteLater()));
    connect(m_mtu,SIGNAL(terminat()),stepButton,SLOT(deleteLater()));
    connect(m_mtu,SIGNAL(terminat()),this,SLOT(on_finish()));
    connect(m_mtu,SIGNAL(step(int,int)),this,SLOT(on_step(int,int)));
    m_binput->addWidget(stepButton);
    m_binput->addWidget(startButton);
    m_layout->addItem(m_output);
    m_layout->addWidget(m_stareCurenta);
    
    m_porneste->hide();
    QWidget *window = new QWidget();
    window->setLayout(m_layout);
    setCentralWidget(window);
    
    //m_mtu->porneste();
}

QString uturingmachine::getFromFile(QString filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<<"Nu am reusit sa deschid fisierul "<<filename;
		QMessageBox msgBox;
		msgBox.setText(QString("Nu am reusit sa deschid fisierul ").append(filename));
		msgBox.exec();
		return QString();
	}
	
	QTextStream in(&file);
	return in.readLine();
}

void uturingmachine::on_step(int banda_modif, int stare)
{
        for(int i=0;i<m_output->count();i++){
                if(i%2==0) continue;
                QLabel *bandaCurenta = (QLabel*) m_output->itemAt(i)->widget();
                bandaCurenta->setText(m_mtu->Benzi().at(banda_modif)->continut());
        }
        if(stare==-1){
                m_stareCurenta->setText("");
        } else {
                m_stareCurenta->setText(QString("Starea curenta: q").append(QString::number(stare)));
        }
}

void uturingmachine::on_finish()
{
        for(int i=0;i<m_mtu->Benzi().count();i++){
                on_step(i,-1);
        }
        QPushButton* resetButton=new QPushButton(this);
        resetButton->setText(QString("Reset"));
        
        connect(resetButton,SIGNAL(clicked(bool)),this,SLOT(reset()));
        connect(this,SIGNAL(resetFinished()),resetButton,SLOT(deleteLater()));
        
        m_layout->addWidget(resetButton);
        
}

void uturingmachine::reset()
{

    m_mtu = new MasinaTuringUniversala();
    running = false;
    m_stareCurenta = new QLabel( this );
    m_nrBenzi = new QLineEdit( this );
    m_mtu_fisiere = new QComboBox( this );
    m_porneste = new QPushButton(this);
    m_porneste->setText("Ok.");
    m_porneste->hide();
    connect(m_porneste, SIGNAL(clicked(bool)), SLOT(on_porneste()));
    
    //ia numai fisierele .utm
    QDir currentDir = QDir::currentPath();
    QStringList files;
    QStringList filters;
    filters << "*.utm";
    files = currentDir.entryList(filters,
                                  QDir::Files | QDir::NoSymLinks);
    
    for (int i = 0; i < files.size(); ++i) {
        m_mtu_fisiere->addItem(files.at(i));
        qDebug()<<files.at(i);
    }
    
    m_layout = new QFormLayout();
    m_binput = new QFormLayout();
    m_layout->addRow(tr("&Alege fisier masina:"), m_mtu_fisiere);
    m_layout->addRow(tr("&Numar benzi intrare:"), m_nrBenzi);

    m_layout->addItem(m_binput);
    
    QWidget *window = new QWidget();
    window->setLayout(m_layout);
    
    connect(m_nrBenzi, SIGNAL(textChanged(QString)), SLOT(on_nrBenzi_changed(QString)));
    
    
    setCentralWidget(window);

    emit resetFinished();
}


#include "uturingmachine.moc"
