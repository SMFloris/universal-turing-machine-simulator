#include <QtGui/QApplication>
#include "uturingmachine.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    uturingmachine uturingmachine;
    uturingmachine.show();
    return app.exec();
}
