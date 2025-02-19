#include "MainUi.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication a(argc, argv);
    MainUi w;
    w.setFixedSize(w.width(), w.height());
    w.show();
    return a.exec();
}
