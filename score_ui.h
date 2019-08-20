#ifndef SCORE_UI_H
#define SCORE_UI_H

#include <QWidget>

namespace Ui {
class score_ui;
}

class score_ui : public QWidget
{
    Q_OBJECT

public:
    explicit score_ui(QWidget *parent = 0);
    ~score_ui();

private:
    Ui::score_ui *ui;

private slots:
    void ui_lineedit_init();
    void on_read_data_clicked();
    void on_save_data_clicked();
};

#endif // SCORE_UI_H
