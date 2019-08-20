#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "choose_ui.h"

extern float Blood_Red;
extern float Blood_Blue;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_connect_device_clicked();
    void Device_SerialPort_RecvMsgEvent();

    //void on_button_send_msg_clicked();
    QList<QList<float>> analize(QByteArray temp);

    void on_button_close_clicked();

    void on_button_rules_clicked();

    void on_button_play_groups_clicked();

    void ui_button_init();

    void ui_mouse_init();

    void ui_label_init();

    void ui_edit_init();

    void on_button_start_game_clicked();

    void on_button_software_note_clicked();

    void score_init();

private:
    Ui::MainWindow *ui;
    QSerialPort *Device_SerialPort;             //记得声明你的串口名字！！！！
    //建立QMediaPlayer 对象
    Choose_ui *g= new Choose_ui();

};

#endif // MAINWINDOW_H
