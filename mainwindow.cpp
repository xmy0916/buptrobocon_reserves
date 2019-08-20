#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <Qdebug>
#include <qmovie.h>
#include "informui.h"
#include "QtMultimedia/qsound.h"
#include "com_ui.h"
#include "score_ui.h"
#include <QFile>


#define Frame QList<float>
float Blood_Red = 100.0;
float Blood_Blue = 100.0;
float Blood[4] = {100.0,100.0,100.0,100.0};

enum device_state
{
    _CLOSE,
    _OPEN
};

void MainWindow::ui_button_init()
{
    ui->button_connect_device->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_play_groups->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_rules->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_software_note->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_start_game->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");
    ui->button_close->setStyleSheet("QPushButton{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton:hover{border-image: url(:/mysource/picture/button_background_pressed.png);}"
                                  "QPushButton:pressed{border-image: url(:/mysource/picture/button_background.png);}"
                                  "QPushButton{color:white;}"
                                  "QPushButton{font:20pt;}");

}

void MainWindow::ui_mouse_init()
{
    QCursor *myCursor=new QCursor(QPixmap(":/mysource/picture/curse.png"),-1,-1);    //-1,-1表示热点位于图片中心
    this->setCursor(*myCursor);
}

void MainWindow::score_init()
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
                Score.win[0] = line.toInt();
                break;
            case 2:
                Score.loss[0] = line.toInt();
                break;
            case 3:
                Score.integral[0] = line.toInt();
                break;
            case 4:
                Score.win[1] = line.toInt();
                break;
            case 5:
                Score.loss[1]= line.toInt();
                break;
            case 6:
                Score.integral[1] = line.toInt();
                break;
            case 7:
                Score.win[2] = line.toInt();
                break;
            case 8:
                Score.loss[2] = line.toInt();
                break;
            case 9:
                Score.integral[2] = line.toInt();
                break;
            case 10:
                Score.win[3] = line.toInt();
                break;
            case 11:
                Score.loss[3] = line.toInt();
                break;
            case 12:
                Score.integral[3] = line.toInt();
                i = 0;
                break;
            }
        }
        qDebug()<<Score.integral[3];
        //QMessageBox::about(NULL,"提示","队伍积分初始化成功！");
        f.destroyed();
    }else
    {
        f.destroyed();
        QMessageBox::about(NULL,"提示","队伍积分初始化失败！");
    }
}

void MainWindow::ui_label_init()
{
    /*
    QLabel* label_robot_gif = new QLabel(this);
    label_robot_gif->raise();
    QSize *sizetemp = new QSize(200,200);
    label_robot_gif->resize(*sizetemp);
    QMovie *movie = new QMovie();
    movie->setFileName("robot.gif");
    QSize size = label_robot_gif->size();
    movie->setScaledSize(size);
    label_robot_gif->setMovie(movie);
    movie->start();
    label_robot_gif->move(1700, 870);*/

    QPixmap team_logo(":/mysource/picture/logo.png");             //读取logo
    team_logo = team_logo.scaled(ui->label_logo->width(),ui->label_logo->height());     //设置logo长宽
    ui->label_logo->setGeometry(rect().x()+700, rect().y(),
                                    ui->label_logo->width(),ui->label_logo->height());
    ui->label_logo->setPixmap(team_logo);
}

void MainWindow::ui_edit_init()
{
    ui->mainToolBar->hide();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_button_init();
    ui_mouse_init();
    ui_label_init();
    ui_edit_init();
    score_init();



}

MainWindow::~MainWindow()
{
    delete ui;
}

int flag_device_open = _CLOSE;
void MainWindow::on_button_connect_device_clicked()
{

    if(flag_device_open == _CLOSE)
    {
        Device_SerialPort=new QSerialPort(this);
        Device_SerialPort->setPortName("COM4");
        Device_SerialPort->setBaudRate(115200);
        Device_SerialPort->setDataBits(QSerialPort::Data8);
        //设置校验位
        Device_SerialPort->setParity(QSerialPort::NoParity);
        //设置流控制
        Device_SerialPort->setFlowControl(QSerialPort::NoFlowControl);
        //设置停止位
        Device_SerialPort->setStopBits(QSerialPort::OneStop);
        Device_SerialPort->setReadBufferSize(200000);

        if(Device_SerialPort->isOpen())
            {
                QMessageBox msgBox;
                  msgBox.setText("打开成功");
                  msgBox.exec();


            }
        if(Device_SerialPort->open(QIODevice::ReadWrite)){

            ui->button_connect_device->setText("断开设备");
            flag_device_open = _OPEN;
            QObject::connect(Device_SerialPort, &QSerialPort::readyRead, this, &MainWindow::Device_SerialPort_RecvMsgEvent);
        }else{
            QMessageBox::about(NULL,"提示","打开串口失败！");
                return ;
        }
    }else
    {
        flag_device_open = _CLOSE;
        Device_SerialPort->close();
        ui->button_connect_device->setText("连接设备");

    }
}

/**
 *************************************************
 *@brief  接收字符
 *@note   移植可以直接全选复制
 *************************************************
 */
QByteArray rx_buffer;
int rx_cnt=0;
void MainWindow::Device_SerialPort_RecvMsgEvent()
{
    QByteArray temp;
    QList<QList<float>> result;

    /*
     * 这个方法用来同时更新编辑框和波形
     * 但发现这样的话编辑框更新太慢，会有卡顿现象
     * 目前的解决方法是显示波形时就不更新编辑框
     *
     */
    temp=Device_SerialPort->readAll();
    rx_buffer.append(temp);
    rx_cnt+=temp.length();
    if(rx_cnt>100){
        result=analize(rx_buffer);
        rx_buffer.clear();
        Blood_Red = Blood[0];
        Blood_Blue = Blood[1];
        qDebug()<<Blood_Red<<"   "<<Blood_Blue<<endl;
        rx_cnt=0;
    }
}

/*
void MainWindow::on_button_send_msg_clicked()
{
    if(ui->button_connect_device->text()!="断开设备"){
        QMessageBox msgBox;
          msgBox.setText("请先打开串口!");
          msgBox.exec();
                return ;
    }

    QByteArray s ="50.0 60.0";//ui->lineEdit_send->text().toLatin1();
    if(ui->checkBox_send_newline->isChecked()){
        s.append('\r');
        s.append('\n');
    }
    Device_SerialPort->write(s);
}*/

QList<QList<float>> MainWindow::analize(QByteArray bytes){
    int data_length=0;
    int data_type=6;
    int data_num=0;
    QList<float> frame;
    QList<QList<float>> result;
    float temp=0;
    int len=bytes.length();

    for(int i=0;i<len-6;++i){
        if(bytes[i]=='b'){
            //找到了疑似帧头
            frame.clear();
            if(i+6+data_length>len){
                break; //长度不够了
            }
            if(bytes[i+1]!='y'){
                continue;
            }
            data_length=bytes[i+2];
            data_type=bytes[i+3];

            if(bytes[i+4+data_length]!='\r' || bytes[i+5+data_length]!='\n'){
                continue; //确认帧尾失败
            }
            switch(data_type){
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:break;
            case 4:break;
            case 5:break;
            case 11:break;
            case 7:break;
            case 6:
                data_num=data_length/4;
                for(int data_cnt=0;data_cnt<data_num;++data_cnt){
                    memcpy(&temp,bytes.data()+i + 4 + data_cnt * 4,4);
                    if(temp <= 0)
                        temp = 0;

                    Blood[data_cnt] = temp;
                    frame.append(temp);
                }
                result.append(frame);
                break;
            }


            i += 5 + data_length; //跳过本帧
        }
    }
    return result;
}

void MainWindow::on_button_close_clicked()
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
        //QMessageBox::about(NULL,"提示","已经自动为您保存比赛积分！");
    this->destroy();
    this->close();
    delete ui;
    exit(1);
}

void MainWindow::on_button_rules_clicked()
{

    Informui *r;
    r = new Informui();
    r->setWindowTitle("规则动图解释");
    r->resize(600,337);
    r->show();
    //this->hide();
}

void MainWindow::on_button_play_groups_clicked()
{
    g->setWindowFlags (Qt::FramelessWindowHint);
    QPalette palette;
    QPixmap pixmap(":/mysource/picture/blue_red_pk.jpg");      //读取背景图片
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    g->resize(pixmap.size());
    g->setPalette(palette);
    g->setWindowTitle("比赛组别");
    g->show();
}

void MainWindow::on_button_start_game_clicked()
{
    if(choosed_flag == 0)
    {
        QMessageBox msgBox;
          msgBox.setText("请先选择比赛组别！");
          msgBox.exec();
          return;
    }
    if(flag_device_open == _CLOSE)
    {
        QMessageBox msgBox;
          msgBox.setText("设备未连接！");
          msgBox.exec();
          return;
    }
    game_ui *game;
    game = new game_ui();
    game->setWindowTitle("2019北邮机器人预备队校内赛");
    QPalette palette;
    QPixmap pixmap(":/mysource/picture/game_background_2.jpg");      //读取背景图片
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    game->setPalette(palette);
    game->showFullScreen();
}

void MainWindow::on_button_software_note_clicked()
{
    score_ui *s;
    s = new score_ui();
    s->setWindowTitle("2019北邮机器人预备队校赛积分表");
    QPalette palette;
    QPixmap pixmap(":/mysource/picture/score.jpg");      //读取背景图片
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    s->setPalette(palette);
    s->resize(1024,472);
    s->show();
}
