#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(" ");
    //w.setWindowFlags (Qt::FramelessWindowHint);
    QPalette palette;
    QPixmap pixmap(":/mysource/picture/background.jpg");      //读取背景图片
    QPixmap titleicon(":/mysource/picture/logo.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w.setPalette(palette);
    w.setWindowIcon(titleicon);
    //w.resize(1024,768);
    //w.show();
    w.showFullScreen();
    //w.showMaximized();
    return a.exec();
}
