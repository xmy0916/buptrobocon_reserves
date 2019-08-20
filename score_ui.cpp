#include "score_ui.h"
#include "ui_score_ui.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include "game_ui.h"
#include "qstring.h"

score_ui::score_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::score_ui)
{
    ui->setupUi(this);
    QCursor *myCursor=new QCursor(QPixmap(":/mysource/picture/curse.png"),-1,-1);    //-1,-1表示热点位于图片中心
    this->setCursor(*myCursor);

    ui_lineedit_init();
    ui->read_data->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:red;}"
                                  "QPushButton{font:20pt;}");
    ui->save_data->hide();
    ui->read_data->hide();


}

score_ui::~score_ui()
{
    delete ui;
}

void score_ui::ui_lineedit_init()
{
        QString status = QString("%1").arg(Score.win[0]);
        ui->lineedit_1_group_win->setText(status);
        status = QString("%1").arg(Score.loss[0]);
        ui->lineedit_1_group_loss->setText(status);
        status = QString("%1").arg(Score.integral[0]);
        ui->lineedit_1_group_score->setText(status);

        status = QString("%1").arg(Score.win[1]);
        ui->lineedit_2_group_win->setText(status);
        status = QString("%1").arg(Score.loss[1]);
        ui->lineedit_2_group_loss->setText(status);
        status = QString("%1").arg(Score.integral[1]);
        ui->lineedit_2_group_score->setText(status);

        status = QString("%1").arg(Score.win[2]);
        ui->lineedit_3_group_win->setText(status);
        status = QString("%1").arg(Score.loss[2]);
        ui->lineedit_3_group_loss->setText(status);
        status = QString("%1").arg(Score.integral[2]);
        ui->lineedit_3_group_score->setText(status);

        status = QString("%1").arg(Score.win[3]);
        ui->lineedit_4_group_win->setText(status);
        status = QString("%1").arg(Score.loss[3]);
        ui->lineedit_4_group_loss->setText(status);
        status = QString("%1").arg(Score.integral[3]);
        ui->lineedit_4_group_score->setText(status);

}

void score_ui::on_read_data_clicked()
{
    QString file="E:\\qt_code\\Bupt_Reserves_Score_indicator\\save.data";  //QFileDialog::getSaveFileName(NULL,tr("Save"),"",tr("Data file (*.data)"));		//确定保存位置
    QFile f(file);
    if(f.open(QIODevice::ReadOnly))
    {
        QTextStream in(&f);
        while (!in.atEnd())
        {
            static int i = 0;
            i++;
            QString line = in.readLine();
            switch (i)
            {
            case 1:
                ui->lineedit_1_group_win->setText(line);
                break;
            case 2:
                ui->lineedit_1_group_loss->setText(line);
                break;
            case 3:
                ui->lineedit_1_group_score->setText(line);
                break;
            case 4:
                ui->lineedit_2_group_win->setText(line);
                break;
            case 5:
                ui->lineedit_2_group_loss->setText(line);
                break;
            case 6:
                ui->lineedit_2_group_score->setText(line);
                break;
            case 7:
                ui->lineedit_3_group_win->setText(line);
                break;
            case 8:
                ui->lineedit_3_group_loss->setText(line);
                break;
            case 9:
                ui->lineedit_3_group_score->setText(line);
                break;
            case 10:
                ui->lineedit_4_group_win->setText(line);
                break;
            case 11:
                ui->lineedit_4_group_loss->setText(line);
                break;
            case 12:
                ui->lineedit_4_group_score->setText(line);
                i = 0;
                break;
            }
        }
        f.destroyed();
    }else
    {
        f.destroyed();
        QMessageBox::about(NULL,"提示","队伍积分初始化失败！");
    }
}

void score_ui::on_save_data_clicked()
{
    QString file="E:\\qt_code\\Bupt_Reserves_Score_indicator\\save.data";  //QFileDialog::getSaveFileName(NULL,tr("Save"),"",tr("Data file (*.data)"));		//确定保存位置
    QFile f(file);
        if( f.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream out(&f);

            out << QString("%1").arg(Score.win[0]) << endl;
            out << QString("%1").arg(Score.loss[0]) << endl;
            out << QString("%1").arg(Score.integral[0]) << endl;

            out << QString("%1").arg(Score.win[1]) << endl;
            out << QString("%1").arg(Score.loss[1]) << endl;
            out << QString("%1").arg(Score.integral[1]) << endl;

            out << QString("%1").arg(Score.win[2]) << endl;
            out << QString("%1").arg(Score.loss[2]) << endl;
            out << QString("%1").arg(Score.integral[2]) << endl;

            out << QString("%1").arg(Score.win[3]) << endl;
            out << QString("%1").arg(Score.loss[3]) << endl;
            out << QString("%1").arg(Score.integral[3]) << endl;


            f.close();
        }
        QMessageBox::about(NULL,"提示","保存成功！");

}
