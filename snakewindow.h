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
    void updateTime();

private:
    QTimer *timer;
    char *gameGrid;
    QGridLayout *grid;
    SnakeGame *snake;
    QLabel *scoreLabel;

protected:
    void keyPressEvent(QKeyEvent *event) override {
        snake->keyPressEvent(event);
        QWidget::keyPressEvent(event);
    }
};

#endif // SNAKEWINDOW_H
