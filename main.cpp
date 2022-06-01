#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForTr(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForLocale(codec);

    Widget w;
    w.setWindowTitle("Эпидемические модели неоднородных сетей");
    w.showMaximized();

    return a.exec();
}
