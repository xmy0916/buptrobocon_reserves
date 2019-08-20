#ifndef GAME_UI_H
#define GAME_UI_H

#include <QWidget>
#include <QMediaPlayer>

extern QString game_name_blue,game_name_red;
extern int name_index_red,name_index_blue;
typedef struct SCORE
{
    int win[4];
    int loss[4];
    int integral[4];
}SCORE;
extern SCORE Score;

namespace Ui {
class game_ui;
}

class game_ui : public QWidget
{
    Q_OBJECT

public:
    explicit game_ui(QWidget *parent = 0);
    ~game_ui();

private slots:
    void on_button_return_menu_clicked();

    void on_button_start_time_clicked();

    void on_button_stop_time_clicked();

    void on_button_end_game_clicked();

    void on_button_clear_clicked();

private:
    Ui::game_ui *ui;
    QMediaPlayer *myPlayer= new QMediaPlayer;
    QTimer* timer;
    QTimer* timer2;
    int usedTime=0,usedTime2=0;

public slots:
    void onTimeout();
    void onTimeout2();
};

#endif // GAME_UI_H
