#include "informui.h"
#include "ui_informui.h"
#include "qlabel.h"
#include "qmovie.h"

Informui::Informui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Informui)
{
    ui->setupUi(this);
    QCursor *myCursor=new QCursor(QPixmap(":/mysource/picture/curse.png"),-1,-1);    //-1,-1表示热点位于图片中心
    this->setCursor(*myCursor);
        QLabel* pBack = new QLabel(this);
        pBack->lower();
        QSize *sizetemp = new QSize(600,337);
        pBack->resize(*sizetemp);
        QMovie *movie = new QMovie();
        movie->setFileName(":/mysource/picture/123.gif");
        QSize size = pBack->size();
        movie->setScaledSize(size);
        pBack->setMovie(movie);
        movie->start();
        movie->setSpeed(50);
        pBack->move(0, 0);
}

Informui::~Informui()
{
    delete ui;
}
