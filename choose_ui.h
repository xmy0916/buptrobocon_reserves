#ifndef CHOOSE_UI_H
#define CHOOSE_UI_H

#include <QWidget>
#include "game_ui.h"

extern int choosed_flag;

namespace Ui {
class Choose_ui;
}

class Choose_ui : public QWidget
{
    Q_OBJECT

public:
    explicit Choose_ui(QWidget *parent = 0);
    ~Choose_ui();

private slots:
    void on_button_select_sure_clicked();

    void on_button_select_return_clicked();

private:
    Ui::Choose_ui *ui;

};

#endif // CHOOSE_UI_H
