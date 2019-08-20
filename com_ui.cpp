#include "com_ui.h"
#include "ui_com_ui.h"

Com_ui::Com_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Com_ui)
{
    ui->setupUi(this);
}

Com_ui::~Com_ui()
{
    delete ui;
}
