#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QDialog>

namespace Ui {
    class Snakewindow;
}

class Snakewindow : public QMainWindow {
    Q_OBJECT

public:
    explicit Snakewindow(QWidget *parent = nullptr);
    ~Snakewindow() override = default;

private:
    QLineEdit *usernameLineEdit;
};

#endif // SNAKEWINDOW_H
