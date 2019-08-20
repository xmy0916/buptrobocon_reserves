#ifndef INFORMUI_H
#define INFORMUI_H

#include <QWidget>

namespace Ui {
class Informui;
}

class Informui : public QWidget
{
    Q_OBJECT

public:
    explicit Informui(QWidget *parent = 0);
    ~Informui();

private:
    Ui::Informui *ui;
};

#endif // INFORMUI_H
