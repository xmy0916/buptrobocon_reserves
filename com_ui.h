#ifndef COM_UI_H
#define COM_UI_H

#include <QWidget>

namespace Ui {
class Com_ui;
}

class Com_ui : public QWidget
{
    Q_OBJECT

public:
    explicit Com_ui(QWidget *parent = 0);
    ~Com_ui();

private:
    Ui::Com_ui *ui;
};

#endif // COM_UI_H
