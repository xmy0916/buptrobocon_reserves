#include "game_ui.h"
#include "ui_game_ui.h"
#include "choose_ui.h"
#include <QTimer>
#include <QTime>
#include "mainwindow.h"
#include "score_ui.h"
#include "qmessagebox.h"

QString game_name_blue,game_name_red;
int name_index_red = 0,name_index_blue = 0;
int whole_time = 300;
int add_time = 180;
int score[4] = {0,0,0,0};
int end_game_blood_blue = 0;
int end_game_blood_red = 0;
int victory_flag = 0;
QMediaPlayer *victory= new QMediaPlayer;


SCORE Score;


game_ui::game_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_ui),
    timer(new QTimer),
    timer2(new QTimer)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(onTimeout2()));
    ui->label_blue_team_name->setText(game_name_blue);
    ui->label_red_team_name->setText(game_name_red);
    //绝对路径
    //设置媒体文件源
    myPlayer->setMedia(QUrl::fromLocalFile("E:\\qt_code\\Bupt_Reserves_Score_indicator\\music\\bgmusic.mp3"));
    //设置音量
    myPlayer->setVolume(80);
    //播放音乐
    //myPlayer->play();

    QString status = QString("%1 ")
                    .arg(whole_time);
    ui->lcdNumber->display(status);

    ui->progressBar_blue->setValue(100);
    ui->progressBar_blue->setFormat(QString::fromLocal8Bit(""));
    ui->progressBar_red->setValue(100);
    ui->progressBar_red->setFormat(QString::fromLocal8Bit(""));
    ui->progressBar->setMaximum(whole_time);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(whole_time);

    char strblue[50];
    sprintf(strblue,"蓝方血量：%.0f",Blood_Blue);
    ui->label_lastblood_blue->setText(strblue);
    char strred[50];
    sprintf(strred,"红方血量：%.0f",Blood_Red);
    ui->label_lastblood_red->setText(strred);

    ui->progressBar->setFormat(QString::fromLocal8Bit("Time:%1s").arg(QString::number(whole_time, 'f', 0)));
    //pProgressBar->setFormat(QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(dProgress, 'f', 1)));

    QCursor *myCursor=new QCursor(QPixmap(":/mysource/picture/curse.png"),-1,-1);    //-1,-1表示热点位于图片中心
    this->setCursor(*myCursor);

    ui->button_clear->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_end_game->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_return_menu->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_start_time->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_stop_time->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->progressBar->hide();
}

game_ui::~game_ui()
{
    delete ui;
}


void game_ui::on_button_return_menu_clicked()
{
    choosed_flag = 0;
    usedTime = 0;
    victory_flag = 0;
    myPlayer->stop();
    victory->stop();
    this->close();
    timer->stop();
    timer2->stop();
}


void game_ui::onTimeout()
{
    if(victory_flag == 0)
    {
    usedTime++;
    int temp = whole_time-usedTime;
    if(temp <= 0)
    {
        timer->stop();
        temp = 0;
    }
    if(temp >= 100)
    {
        QString status = QString("%1 ")
                    .arg(temp);
        ui->lcdNumber->display(status);

    }else if(temp < 10)
    {
        QString status = QString("00%1 ")
                    .arg(temp);
        ui->lcdNumber->display(status);
    }
    else
    {
        QString status = QString("0%1 ")
                    .arg(temp);
        ui->lcdNumber->display(status);
    }
    ui->progressBar->setValue(temp);  // 当前进度
    ui->progressBar->setFormat(QString::fromLocal8Bit("Time:%1s").arg(QString::number(temp, 'f', 0)));
    }
}


void game_ui::onTimeout2()
{
    if((Blood_Blue <= 0||Blood_Red <= 0)&&victory_flag == 0)
    {
        ui->progressBar_blue->setValue(Blood_Blue);
        ui->progressBar_red->setValue(Blood_Red);
        char strblue[50];
        sprintf(strblue,"蓝方血量：%.0f",Blood_Blue);
        ui->label_lastblood_blue->setText(strblue);
        char strred[50];
        sprintf(strred,"红方血量：%.0f",Blood_Red);
        ui->label_lastblood_red->setText(strred);

        end_game_blood_blue = Blood_Blue;
        end_game_blood_red = Blood_Red;
        if(Blood_Blue <= 0)
        {
            //score[name_index_red]++;
            Score.win[name_index_red]++;
            Score.loss[name_index_blue]++;
            Score.integral[name_index_red]+=Blood_Red;
        }
        if(Blood_Red <= 0)
        {
            Score.win[name_index_blue]++;
            Score.loss[name_index_red]++;
            Score.integral[name_index_blue]+=Blood_Blue;
        }
        myPlayer->stop();
        victory_flag = 1;
        usedTime = 0;
        myPlayer->stop();

        //设置媒体文件源
        victory->setMedia(QUrl::fromLocalFile("E:\\qt_code\\Bupt_Reserves_Score_indicator\\music\\victory.wav"));
        //设置音量
        victory->setVolume(80);
        //播放音乐
        victory->play();
        on_button_end_game_clicked();
    }
    if(usedTime>=whole_time&&victory_flag == 0)
    {
        end_game_blood_blue = Blood_Blue;
        end_game_blood_red = Blood_Red;
        if(Blood_Blue > Blood_Red)
        {
            //score[name_index_blue]++;
            Score.win[name_index_blue]++;
            Score.loss[name_index_red]++;
            Score.integral[name_index_blue]+=Blood_Blue;
        }else if(Blood_Blue < Blood_Red)
        {
            //score[name_index_red]++;
            Score.win[name_index_red]++;
            Score.loss[name_index_blue]++;
            Score.integral[name_index_red]+=Blood_Red;
        }
        myPlayer->stop();
        victory_flag = 1;
        usedTime = 0;
        //QMediaPlayer *victory= new QMediaPlayer;
        //设置媒体文件源
        victory->setMedia(QUrl::fromLocalFile("E:\\qt_code\\Bupt_Reserves_Score_indicator\\music\\victory.wav"));
        //设置音量
        victory->setVolume(80);
        //播放音乐
        victory->play();
        on_button_end_game_clicked();
    }
    if(end_game_blood_blue != 0||end_game_blood_red!=0)
    {
        ui->progressBar_blue->setValue(end_game_blood_blue);
        ui->progressBar_red->setValue(end_game_blood_red);
    }else
    {
        char strblue[50];
        sprintf(strblue,"蓝方血量：%.0f",Blood_Blue);
        ui->label_lastblood_blue->setText(strblue);
        char strred[50];
        sprintf(strred,"红方血量：%.0f",Blood_Red);
        ui->label_lastblood_red->setText(strred);

        if(Blood_Blue >= 100)
            ui->progressBar_blue->setValue(100);
        else
            ui->progressBar_blue->setValue(Blood_Blue);

        if(Blood_Red >= 100)
            ui->progressBar_red->setValue(100);
        else
            ui->progressBar_red->setValue(Blood_Red);
    }
}

void game_ui::on_button_start_time_clicked()
{
    myPlayer->play();
    end_game_blood_blue = 0;
    end_game_blood_red = 0;
    victory_flag = 0;
    timer->start(1000);
    timer2->start(1);
}

void game_ui::on_button_stop_time_clicked()
{
    myPlayer->stop();
    timer->stop();
}

void game_ui::on_button_end_game_clicked()
{
    whole_time = 300;
    usedTime = 0;
    //victory_flag = 0;
    QString status = QString("%1 ")
                .arg(whole_time);
    ui->lcdNumber->display(status);
    timer->stop();
    score_ui *s;
    s = new score_ui();
    //s->setWindowTitle("2019北邮机器人预备队校内赛");
    QPalette palette;
    QPixmap pixmap(":/mysource/picture/score.jpg");      //读取背景图片
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    s->setPalette(palette);
    s->resize(1024,472);
    s->show();


}

void game_ui::on_button_clear_clicked()
{
    if(whole_time - usedTime > 0)
    {
        int choose;
        choose= QMessageBox::question(this, tr("警告"),
                                       QString(tr("比赛时间未结束确认加时?")),
                                       QMessageBox::Yes | QMessageBox::No);

        if (choose== QMessageBox::No)
        {
             return;  //忽略//程序继续运行
        }
    }
    whole_time = add_time;
    usedTime = 0;
    victory_flag = 0;
    QString status = QString("%1 ")
                .arg(whole_time);
    ui->lcdNumber->display(status);
    timer->stop();
}
