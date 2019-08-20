#include "choose_ui.h"
#include "ui_choose_ui.h"
#include <qdebug.h>
#include <qmessagebox.h>


int choosed_flag = 0;

Choose_ui::Choose_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Choose_ui)
{

    ui->setupUi(this);
    ui->button_select_sure->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/vs.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/vs_choosed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/vs.png);}");
    QCursor *myCursor=new QCursor(QPixmap(":/mysource/picture/curse.png"),-1,-1);    //-1,-1表示热点位于图片中心
    this->setCursor(*myCursor);
    ui->button_select_return->hide();
}

Choose_ui::~Choose_ui()
{
    delete ui;
}

void Choose_ui::on_button_select_sure_clicked()
{
    if(ui->comboBox_select_red->currentIndex() == ui->comboBox_select_blue->currentIndex())
    {
        QMessageBox::about(NULL,"提示","不可以选择相同的组别参赛！");
        return;
    }

    choosed_flag = 1;
    game_name_red = ui->comboBox_select_red->currentText();
    name_index_red = ui->comboBox_select_red->currentIndex();
    game_name_blue = ui->comboBox_select_blue->currentText();
    name_index_blue = ui->comboBox_select_blue->currentIndex();
    this->close();
}

void Choose_ui::on_button_select_return_clicked()
{
    this->close();
}
