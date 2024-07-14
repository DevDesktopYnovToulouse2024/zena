#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QDialog>

#include "snake.h"

namespace Ui {
    class Snakewindow;
}

class Snakewindow : public QMainWindow {
    Q_OBJECT

public:
    explicit Snakewindow(QWidget *parent = nullptr);

    ~Snakewindow() override = default;

private slots:
    void updateTime(SnakeGame *snake);

private:
    QTimer *timer;
    QGridLayout *grid;
};

#endif // SNAKEWINDOW_H
